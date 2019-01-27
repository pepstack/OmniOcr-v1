//
// omniocrcli.cpp
//
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>

#include "omniocr_api.h"

#define TESSDATA_PREFIX    "C:/DEVPACK/tesseract-build-vs2013"

#define FIX_DY_SIZE  800.0f


#pragma warning(push)
#pragma warning(disable:4996)


void GetModulePath(const char * pathfile, char * binPath, int size)
{
    if (!pathfile || strlen(pathfile) >= size) {
        exit(-1);
    }

    strncpy(binPath, pathfile, size);
    binPath[size - 1] = 0;

    if (strrchr(binPath, '\\')) {
        *strrchr(binPath, '\\') = 0;
    } else if (strrchr(binPath, '/')) {
        *strrchr(binPath, '/') = 0;
    } else {
        exit(-1);
    }
}


bool ListPathFiles(const char *workdir, const char *match, std::vector<std::string> &files)
{
    char pathFind[MAX_PATH];
    sprintf(pathFind, "%s%s", workdir, match);

    WIN32_FIND_DATAA FindFileData;        
    ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));

    HANDLE hFile = FindFirstFileA(pathFind, &FindFileData);
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    files.clear();

    files.push_back(FindFileData.cFileName);

    while (FindNextFileA(hFile, &FindFileData)) {
        files.push_back(FindFileData.cFileName);
    }

    FindClose(hFile);
    return true;
}


void run(TessBaseAPI * apiHandle, char * stencilDir, char * imageDir);


int main(int argc, const char ** argv)
{
    int stlen, wdlen, err;

    TessBaseAPI * apiHandle;

    char binPrefix[FILE_MAXLEN];
    char stencilDir[FILE_MAXLEN];
    char ocrWorkDir[FILE_MAXLEN];

    GetModulePath(argv[0], binPrefix, sizeof(binPrefix));
    sprintf(stencilDir, "%s\\stencil\\", binPrefix);

    if (argc == 2) {
        strncpy(ocrWorkDir, argv[1], sizeof(ocrWorkDir));
        ocrWorkDir[sizeof(ocrWorkDir) - 1] = 0;
    } else {
        sprintf(ocrWorkDir, "%s\\OcrBMPs\\", binPrefix);
    }
    wdlen = (int) strlen(ocrWorkDir);
    if (ocrWorkDir[wdlen - 1] != '\\' && ocrWorkDir[wdlen - 1] != '/') {
        ocrWorkDir[wdlen + 1] = 0;
        ocrWorkDir[wdlen] = '\\';
    }
    wdlen = (int) strlen(ocrWorkDir);

    printf("**** OmniOcrCli.exe v2017.01.06 beta.\n");
    printf("[INFO] Tesseract Prefix: %s\n", binPrefix);
    printf("[INFO] Ocr Stencil Dir: %s\n", stencilDir);
    printf("[INFO] Ocr Work Dir: %s\n", ocrWorkDir);

    apiHandle = TessBaseAPICreate();
    if (! apiHandle) {
        exit(-1);
    }

#ifdef _DEBUG
    err = TessBaseAPIInit3(apiHandle, TESSDATA_PREFIX, "eng+equ+chi_sim");
#else
    err = TessBaseAPIInit3(apiHandle, binPrefix, "eng+equ+chi_sim");
#endif

    if (err) {
        printf("[ERROR] TessBaseAPIInit3 failed: %d\n", err);
        TessBaseAPIDelete(apiHandle);
        exit(-1);
    } else {
        printf("[INFO] TessBaseAPIInit3 success\n");
    }

    std::vector<std::string> ocrStencilFiles;
    ListPathFiles(stencilDir, "*.stencil", ocrStencilFiles);
    stlen = (int) strlen(stencilDir);

    for (std::vector<std::string>::iterator it = ocrStencilFiles.begin();
        it != ocrStencilFiles.end(); ++it) {
        ocrWorkDir[wdlen] = 0;
        strcat(ocrWorkDir, (*it).c_str());
        *strstr(ocrWorkDir, ".stencil") = 0;
        strcat(ocrWorkDir, "\\");

        stencilDir[stlen] = 0;
        strcat(stencilDir, (*it).c_str());

        printf("[INFO] Stencil File: %s\n", stencilDir);
        printf("[INFO] Process BMPs in: %s\n", ocrWorkDir);

        run(apiHandle, stencilDir, ocrWorkDir);
    }
    
    TessBaseAPIEnd(apiHandle);
    TessBaseAPIDelete(apiHandle);

    printf("**** OmniOcrCli.exe exit.\n");
    system("pause");

    return 0;
}


void run(TessBaseAPI * apiHandle, char * stencilFile, char * ocrImageDir)
{
    int err;

    char tmpfile[FILE_MAXLEN];
    char tmpname[60];

    std::vector<std::string> ocrImageFiles;

    if (ListPathFiles(ocrImageDir, "*.bmp", ocrImageFiles)) {
        for (std::vector<std::string>::iterator it = ocrImageFiles.begin();
            it != ocrImageFiles.end(); ++it) {

            std::string strBmpName(*it);

            if (
                strBmpName.find("-gray.bmp") == std::string::npos &&
                strBmpName.find("-mono.bmp") == std::string::npos &&
                strBmpName.find("-thin.bmp") == std::string::npos &&
                strBmpName.find("-line.bmp") == std::string::npos ) {

                strcpy(tmpname, strBmpName.c_str());
                *strrchr(tmpname, '.') = 0;
                strcat(tmpname, "-json.txt");
                sprintf(tmpfile, "%s%s", ocrImageDir, tmpname);

                if ((_access(tmpfile, 0)) == -1) {
                    Point2f triPoints[3];
                    double rotateDegree;
                    float scaleFactor;

                    sprintf(tmpfile, "%s%s", ocrImageDir, strBmpName.c_str());

                    printf("[INFO] Processing %s ...\n", tmpfile);

                    err = OcrOSDFormat(tmpfile, FIX_DY_SIZE, triPoints, &rotateDegree, &scaleFactor);

                    if (! err) {
                        printf("[INFO] OcrOSDFormat success.\n");
        
                        err = OcrDrillText(apiHandle, tmpfile, triPoints, stencilFile);
                        if (! err) {
                            printf("[INFO] OcrDrillText success.\n");
                        } else {
                            printf("[ERROR] OcrDrillText failed!\n");
                        }
                    } else {
                        printf("[ERROR] OcrOSDFormat failed!\n");
                    }
                }
            }
        }
    }
}

#pragma warning(pop)
