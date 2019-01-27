//
// omniocr_api.h
// 2017-01-03
//
#ifndef OMNIOCR_API_H_INCLUDED
#define OMNIOCR_API_H_INCLUDED

#include "opencv_api.h"
#include "tesseract_api.h"

#include <json/json.h>
#pragma comment(lib, "lib_json.lib")

///////////////////////////////////////////////////////////////////////

#pragma warning(push)
#pragma warning(disable:4996)


typedef  int  OO_RESULT;

#define OO_SUCCESS  0
#define OO_NOERROR  OO_SUCCESS

#define OO_ERROR   (-1)
#define OO_EPARAM  (-2)

#define FILE_MAXLEN  260


void SafeFreeMem(void ** ppv)
{
    void * pv = *ppv;

    *ppv = 0;

    if (pv) {
        free(pv);
    }
}


// 字节数组转为宽字符数据:
//   uCodePage  指明字节数组的字符编码格式
//
#define HEAP_MALLOC(x)  HeapAlloc(GetProcessHeap(), 0, (x))
#define HEAP_FREE(x)    HeapFree(GetProcessHeap(), 0, (x))
#define HEAP_REALLOC(x, cb) HeapReAlloc(GetProcessHeap(), 0, (x), (cb))


static void HeapFreeBSTR(BSTR bstr)
{
    LPSTR pstr = (LPSTR) bstr - sizeof(DWORD);
    HEAP_FREE(pstr);
}


static HRESULT Chars2BSTR (UINT uCodePage /*CP_UTF8, CP_ACP, CP_GBK*/,
    const char * pCharsIn, DWORD cbSizeIn, BSTR *pBstrOut)
{
    *pBstrOut = 0;

    int cchNeeded = ::MultiByteToWideChar(uCodePage, 0, (LPCSTR)pCharsIn, cbSizeIn, 0, 0);
    if (0 == cchNeeded) {
        return E_FAIL;
    }

    LPSTR pstr = (LPSTR) HEAP_MALLOC(sizeof(DWORD) + sizeof(WCHAR)*cchNeeded);
    if (! pstr) {
        return E_OUTOFMEMORY;
    }

    if (0 == ::MultiByteToWideChar(uCodePage, 0, (LPCSTR)pCharsIn, cbSizeIn, (LPWSTR)(pstr+sizeof(DWORD)), cchNeeded)){
        HEAP_FREE(pstr);
        return E_FAIL;
    }

    *((DWORD*)pstr) = sizeof(WCHAR)*(cchNeeded-1);
    *pBstrOut = (BSTR)(pstr + sizeof(DWORD));

    return S_OK;
}


// 无编码转换的宽字符数组转变成字符数组
//
static int Unicode2Chars (LPCWSTR  wstrIn, char **ppOut)
{
    *ppOut = 0;

    if (!wstrIn) {
        return  0;
    }

    int cbSize = ::WideCharToMultiByte(CP_ACP, 0, wstrIn, -1, 0, 0, 0, 0);

    char *psz = (char*) HEAP_MALLOC(cbSize);
    assert(psz);
    if (!psz) {
        return 0;
    }

    cbSize = ::WideCharToMultiByte(CP_ACP, 0, wstrIn, -1, psz, cbSize, 0, 0);
    assert(psz[cbSize-1]==0);

    *ppOut = psz;
    return cbSize;
}


bool Utf82Ansi(const char * utf8Str, int insize, char * buffer, int bufsize)
{
    bool bres = false;

    BSTR bstrOut = 0;

    if (S_OK == Chars2BSTR(CP_UTF8, utf8Str, insize, &bstrOut)) {
        char *pszOut = 0;
        int cbSize = Unicode2Chars((LPCWSTR) bstrOut, &pszOut);

        if (cbSize > 0 && cbSize < bufsize) {
            strncpy(buffer, pszOut, cbSize);
            buffer[cbSize] = 0;
            bres = true;
        }

        HEAP_FREE(pszOut);
        HeapFreeBSTR(bstrOut);
    }

    return bres;
}


static void GenImageNames(const char * ocrImageFile,
    char grayImgFile[FILE_MAXLEN],
    char monoImgFile[FILE_MAXLEN],
    char thinImgFile[FILE_MAXLEN],
    char lineImgFile[FILE_MAXLEN],
    char jsonTxtFile[FILE_MAXLEN])
{
    strcpy(grayImgFile, ocrImageFile);
    * strrchr(grayImgFile, '.') = 0;

    strcpy(monoImgFile, grayImgFile);
    strcpy(thinImgFile, grayImgFile);
    strcpy(lineImgFile, grayImgFile);
    strcpy(jsonTxtFile, grayImgFile);

    strcat(grayImgFile, "-gray.bmp");
    strcat(monoImgFile, "-mono.bmp");
    strcat(thinImgFile, "-thin.bmp");
    strcat(lineImgFile, "-line.bmp");
    strcat(jsonTxtFile, "-json.txt");
}


int FindTriPoints(const char * thinImgFile, const char * lineImgFile,
    float snapAngleDeg, double snapPixels,
    Point2f tripts[3], double * rot_degree)
{
    const int LINE_THREHOLD = 100;
    const double LINE_LENGTH = 60;
    const double LINE_GAP = 4;

    int i, num, numgrps, numpts;

    double d1, d2, d3;

    LineVector v_line;

    int v_line_set = 0,
        grp1_np = 0,
        grp2_np = 0,
        v_grpid = 0,
        n1 = 0,
        n2 = 0,
        n3 = 0;

    double ax[3] = {0, 0, 0};
    double ay[3] = {0, 0, 0};

    // need SafeFreeMem
    LineVector * lines = 0;
    Point2f * intersects = 0;
    int * groups = 0;   
    int * ptgroups = 0;

    CvScalar whiteclr = {255, 255, 255, 255};

    num = HoughLines(thinImgFile, lineImgFile, LINE_THREHOLD, LINE_LENGTH, LINE_GAP, &lines);
    if (num < 2) {
        goto onerr_exit;
    }

    groups = (int *) calloc(num, sizeof(int));
    numgrps = GroupLines(lines, num, groups, snapAngleDeg);
    if (numgrps != 2) {
        goto onerr_exit;
    }

    if (! IsVertical(lines[0].azimuth, lines[num-1].azimuth, snapAngleDeg)) {
        goto onerr_exit;
    }

    for (i = 1; i < num; ++i) {
        if (groups[i] == groups[0]) {
            ++grp1_np;
        } else {
            ++grp2_np;
        }
    }

    if (grp1_np > grp2_np) {
        v_grpid = groups[num - 1];
    } else {
        v_grpid = groups[0];
    }

    for (i = 0; i < num; ++i) {
        if (groups[i] == v_grpid) {
            if (! v_line_set) {
                v_line = lines[i];
                v_line_set = 1;
            } else {
                d1 = GetDistanceSq(&v_line.start, &lines[i].start);
                d2 = GetDistanceSq(&v_line.start, &lines[i].end);

                d3 = GetDistanceSq(&v_line.start, &v_line.end);

                if (d3 < d1 || d3 < d2) {
                    if (d1 > d2) {
                        d3 = GetDistanceSq(&v_line.end, &lines[i].start);
                        if (d3 > d1) {
                            v_line.start = lines[i].start;
                        } else {
                            v_line.end = lines[i].start;
                        }
                    } else {
                        d3 = GetDistanceSq(&v_line.end, &lines[i].end);
                        if (d3 > d2) {
                            v_line.start = lines[i].end;
                        } else {
                            v_line.end = lines[i].end;
                        }
                    }
                }
            }
        }
    }

    v_line.azimuth = GetAzimuth(&v_line.start, &v_line.end);
    for (i = 0; i < num; ++i) {
        if (groups[i] == v_grpid) {
            lines[i] = v_line;
        }
    }

    numpts = IntersectGroupLines(lines, num, groups, &intersects, &ptgroups, snapPixels);
    if (ptgroups[numpts] != 3) {
        goto onerr_exit;
    }

    for (i = 0; i < numpts; ++i) {
        if (ptgroups[i] == 1) {
            ax[0] += intersects[i].x;
            ay[0] += intersects[i].y;
            ++n1;
        } else if (ptgroups[i] == 2) {
            ax[1] += intersects[i].x;
            ay[1] += intersects[i].y;
            ++n2;
        } else if (ptgroups[i] == 3) {
            ax[2] += intersects[i].x;
            ay[2] += intersects[i].y;
            ++n3;
        }
    }

    if (n1 * n2 * n3 == 0) {
        goto onerr_exit;
    }

    tripts[0].x = (float) (ax[0] / n1);
    tripts[0].y = (float) (ay[0] / n1);

    tripts[1].x = (float) (ax[1] / n2);
    tripts[1].y = (float) (ay[1] / n2);

    tripts[2].x = (float) (ax[2] / n3);
    tripts[2].y = (float) (ay[2] / n3);

    SortPointsAscYX(tripts, 3);

    if (rot_degree) {
        d1 = GetDistance(&tripts[0], &tripts[1]);
        d2 = GetDistance(&tripts[1], &tripts[2]);

        if (d1 < d2) {
            *rot_degree = - (GetAzimuth(&tripts[0], &tripts[2]) - CV_PI/2) * 180.f / CV_PI;
        } else {
            *rot_degree = - (GetAzimuth(&tripts[2], &tripts[0]) - CV_PI/2) * 180.f / CV_PI;
        }
    }

    SafeFreeMem((void**) &lines);
    SafeFreeMem((void**) &intersects);
    SafeFreeMem((void**) &groups);
    SafeFreeMem((void**) &ptgroups);

    return OO_SUCCESS;

onerr_exit:
    SafeFreeMem((void**) &lines);
    SafeFreeMem((void**) &intersects);
    SafeFreeMem((void**) &groups);
    SafeFreeMem((void**) &ptgroups);

    return OO_ERROR;
}


static OO_RESULT OcrOSDFormat(const char * ocrImageFile, float fixDyPixels,
    Point2f triPoints[3], double * rotateDegree, float * scaleFactor)
{
    const int GARY_WIDTH = 1920;

    const float SNAP_ANGLE_DEG = 5.0f;
    const double SNAP_PIXELS = 20;

    const CvScalar WHITE_CLR = {255, 255, 255, 255};

    int x0, y0, w, h;
    CvRect clipRect;

    char grayImgFile[FILE_MAXLEN];
    char monoImgFile[FILE_MAXLEN];
    char thinImgFile[FILE_MAXLEN];
    char lineImgFile[FILE_MAXLEN];
    char jsonTxtFile[FILE_MAXLEN];

    int ret;
    Point2f tripts[3];
    double rot_degree;
    float scale_factor;

    GenImageNames(ocrImageFile, grayImgFile, monoImgFile, thinImgFile, lineImgFile, jsonTxtFile);

    ret = Color2Gray(ocrImageFile, grayImgFile, GARY_WIDTH);
    if (ret != 1) {
        return OO_ERROR;
    }

    // Step 1: Rotate by Orientation
    //
    ret = Gray2Mono(grayImgFile, monoImgFile, CV_THRESH_OTSU | CV_THRESH_BINARY_INV, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = ThinMono(monoImgFile, thinImgFile, 3);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(monoImgFile, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(thinImgFile, 0);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = FindTriPoints(thinImgFile, lineImgFile, SNAP_ANGLE_DEG, SNAP_PIXELS, tripts, &rot_degree);
    if (ret != OO_SUCCESS) {
        return OO_ERROR;
    }

    if (rotateDegree) {
        *rotateDegree = - rot_degree;
    }

    ret = RotateImage(grayImgFile, grayImgFile, rot_degree, WHITE_CLR);
    if (ret != 1) {
        return OO_ERROR;
    }

    // Step 2: Resize by fixSize
    //
    ret = Gray2Mono(grayImgFile, monoImgFile, CV_THRESH_OTSU | CV_THRESH_BINARY_INV, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = ThinMono(monoImgFile, thinImgFile, 3);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(monoImgFile, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(thinImgFile, 0);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = FindTriPoints(thinImgFile, lineImgFile, SNAP_ANGLE_DEG, SNAP_PIXELS, tripts, &rot_degree);
    if (ret != OO_SUCCESS) {
        return OO_ERROR;
    }

    if (tripts[2].y - tripts[1].y < fixDyPixels/2) {
        return OO_ERROR;
    }

    scale_factor = (float) (fixDyPixels / (tripts[2].y - tripts[1].y));
    ret = ResizeImage(grayImgFile, monoImgFile, scale_factor, scale_factor);
    if (ret != 1) {
        return OO_ERROR;
    }

    if (scaleFactor) {
        *scaleFactor = scale_factor;
    }

    for (ret = 0; ret < 3; ++ret) {
        tripts[ret].x *= scale_factor;
        tripts[ret].y *= scale_factor;
    }

    x0 = (int) floor(tripts[1].x - fixDyPixels);
    y0 = (int) floor(tripts[1].y - fixDyPixels*320.f/800.f);
    w = (((int) (fixDyPixels * 2) + 3) / 4) * 4;
    h = (((int) (fixDyPixels * 1280.f/800.f) + 3) / 4) * 4;

    clipRect = cvRect(x0, y0, w, h);

    ret = ClipImage(monoImgFile, clipRect, monoImgFile);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = Gray2Mono(monoImgFile, monoImgFile, CV_THRESH_OTSU | CV_THRESH_BINARY_INV, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = ThinMono(monoImgFile, thinImgFile, 3);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(monoImgFile, 1);
    if (ret != 1) {
        return OO_ERROR;
    }

    ret = BinarizeMono(thinImgFile, 0);
    if (ret != 1) {
        return OO_ERROR;
    }

    for (ret = 0; ret < 3; ++ret) {
        triPoints[ret].x = tripts[ret].x - x0;
        triPoints[ret].y = tripts[ret].y - y0;
    }

    return OO_SUCCESS;
}


char * ReadFile(const char * path, int *length)
{  
    FILE * pfile;
    char * data; 

    pfile = fopen(path, "rb");
    if (pfile == NULL) {
        return NULL;
    }

    fseek(pfile, 0, SEEK_END);
    *length = ftell(pfile);
    data = (char *)malloc((*length + 1) * sizeof(char));
    rewind(pfile);
    *length = (int) fread(data, 1, *length, pfile);
    data[*length] = 0;

    fclose(pfile);
    return data;
}


bool WriteFile(const char * path, std::string & content)
{  
    FILE * fp;

    fp = fopen(path, "wb");
    if (! fp) {
        return false;
    }

    fwrite(content.c_str(), sizeof(char), content.size(), fp);

    fclose(fp);

    return true;
}


void FilterNumb(char * buffer)
{
    char tmp[255];

    int i = 0;
    char *p = buffer;

    while (*p && i < 254) {
        uchar ch = (uchar) *p++;

        if (isdigit(ch) || ch == '.') {
            tmp[i++] = (char) ch;
        }
    }

    tmp[i++] = 0;

    strncpy(buffer, tmp, i);
}


void FilterDate(char * buffer)
{
    char tmp[255];

    int i = 0;
    char *p = buffer;

    while (*p && i < 254) {
        uchar ch = (uchar) *p++;

        if (isdigit(ch) || ch == ' ' || ch == ':' || ch == '-') {
            tmp[i++] = (char) ch;
        }
    }

    tmp[i++] = 0;

    strncpy(buffer, tmp, i);
}


void FilterEng(char * buffer)
{
    char tmp[255];

    int i = 0;
    char *p = buffer;

    while (*p && i < 254) {
        uchar ch = (uchar) *p++;

        if (ch != '\n') {
            tmp[i++] = (char) ch;
        }
    }

    tmp[i++] = 0;

    strncpy(buffer, tmp, i);
}


void FilterChi(char * buffer)
{
    char tmp[255];

    int i = 0;
    char *p = buffer;

    while (*p && i < 254) {
        uchar ch = (uchar) *p++;

        if (ch != '\n') {
            tmp[i++] = (char) ch;
        }
    }

    tmp[i++] = 0;

    strncpy(buffer, tmp, i);
}


void FilterSex(char * buffer)
{
    char tmp[255];

    int i = 0;
    char *p = buffer;

    while (*p && i < 254) {
        uchar ch = (uchar) *p++;

        if (ch != '\n') {
            tmp[i++] = (char) ch;
        }
    }

    tmp[i++] = 0;

    if (strncmp(tmp, "男", 2) || strncmp(tmp, "女", 2)) {
        if (! strncmp(tmp, "PF", 2)) {
            strcpy(buffer, "男");
        } else {
            strcpy(buffer, "女");
        }
    } else {
        strncpy(buffer, tmp, 2);
        buffer[2] = 0;
    }
}


/**
 * Refer:
 *   1) Orientation and script detection (OSD)
 *     http://stackoverflow.com/questions/36883530/orientation-and-script-detection-osd-using-tesseract-in-android
 *   2) Samples
 *     http://www.cnblogs.com/cappuccino/p/4650665.html
 */
bool DrillText(TessBaseAPI * apiHandle, IplImage * monoImage, CvRect rect, char buffer[255])
{
    char* utf8Txt = 0;

    TessBaseAPISetImage(apiHandle, (uchar*) monoImage->imageData, monoImage->width, monoImage->height, monoImage->nChannels, monoImage->widthStep);
    TessBaseAPISetRectangle(apiHandle, rect.x, rect.y, rect.width, rect.height);

    utf8Txt = TessBaseAPIGetUTF8Text(apiHandle);

    if (utf8Txt) {
        int confidence = TessBaseAPIMeanTextConf(apiHandle);

        if (confidence > 50) {
            *buffer = 0;
            if (Utf82Ansi(utf8Txt, (int) strlen(utf8Txt) + 1, buffer, 255)) {
                TessDeleteText(utf8Txt);
                return true;
            }
        }

        TessDeleteText(utf8Txt);
    }

    return false;
}


const char * DrillImageText(TessBaseAPI * apiHandle, IplImage * monoImage, const char *strValue, char buffer[255])
{
    char *p1, *p2, *p;

    CvRect rect;

    int i;
    int nums[10];

    *buffer = 0;

    if (strValue[0] != '?') {
        return strValue;
    }

    p1 = (char*) strchr(strValue, '(');
    p2 = (char*) strrchr(strValue, ')');
    if (!p1 || !p2 || p1 == p2) {
        return strValue;
    }

    memcpy(buffer, p1+1, p2 - p1 - 1);
    buffer[p2- p1 - 1] = 0;

    i = 0;
    p = strtok(buffer, ",");
    while (p && i < 10) {
        nums[i++] = atoi(p);
        p = strtok(0, ",");
    }

    if (i != 4) {
        return strValue;
    }

    rect.x = nums[0];
    rect.y = nums[1];
    rect.width = nums[2];
    rect.height = nums[3];

    *buffer = 0;

    if (DrillText(apiHandle, monoImage, rect, buffer)) {
        if (strValue[1] == 'N') {
            FilterNumb(buffer);
        } else if (strValue[1] == 'D') {
            FilterDate(buffer);
        } else if (strValue[1] == 'E') {
            FilterEng(buffer);
        } else if (strValue[1] == 'C') {
            FilterChi(buffer);
        } else if (strValue[1] == 'S') {
            FilterSex(buffer);
        }
    }

    return buffer;
}


void ProcessJsonObject(TessBaseAPI * apiHandle, IplImage * monoImage, Json::Value & inJsonObject, Json::Value & outJsonObject)
{
    Json::Value::Members items = inJsonObject.getMemberNames();

    char buffer[255];

    for (Json::Value::Members::iterator it = items.begin(); it != items.end(); ++it) {
        const char * strName = (*it).c_str();

        Json::Value object(inJsonObject[ strName ]);

        if (object.isString()) {
            const char * strValue = object.asCString();

            if (strValue) {
                const char * text = DrillImageText(apiHandle, monoImage, strValue, buffer);

                printf("    %s = %s\n", strName, text);

                outJsonObject[strName] = Json::Value(text);
            }
        } else if (object.isObject()) {
            printf("%s:\n", strName);

            Json::Value item_object(Json::ValueType::objectValue);

            ProcessJsonObject(apiHandle, monoImage, object, item_object);

            outJsonObject[strName] = item_object;

            printf("\n");
        } 
     }
}


static OO_RESULT OcrDrillText(TessBaseAPI * apiHandle, const char * ocrImageFile, Point2f triPoints[3], const char * stencilFile)
{
    bool bres;

    Json::Reader reader;
    Json::StyledWriter writer;

    Json::Value read_json_root;
    Json::Value write_json_root;

    int length = 0;
    char * stencil = 0;

    char grayImgFile[FILE_MAXLEN];
    char monoImgFile[FILE_MAXLEN];
    char thinImgFile[FILE_MAXLEN];
    char lineImgFile[FILE_MAXLEN];
    char jsonTxtFile[FILE_MAXLEN];

    GenImageNames(ocrImageFile, grayImgFile, monoImgFile, thinImgFile, lineImgFile, jsonTxtFile);

    IplImage * monoImage;
    monoImage = cvLoadImage(monoImgFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! monoImage) {
         return OO_ERROR;
    }

    stencil = ReadFile(stencilFile, &length);
    if (! stencil) {
        cvReleaseImage(&monoImage);
        return OO_ERROR;
    }

    bres = reader.parse(stencil, read_json_root);
    SafeFreeMem((void**) &stencil);

    if (! bres) {
        cvReleaseImage(&monoImage);
        return OO_ERROR;
    }

    ProcessJsonObject(apiHandle, monoImage, read_json_root, write_json_root);

    std::string out_json = writer.write(write_json_root);

    bres = WriteFile(jsonTxtFile, out_json);
    if (! bres) {
        cvReleaseImage(&monoImage);
        return OO_ERROR;
    }

    cvReleaseImage(&monoImage);
    return OO_SUCCESS;
}

#pragma warning(pop)
///////////////////////////////////////////////////////////////////////
#endif // OMNIOCR_API_H_INCLUDED