// opencv_api.h
//
// Refer:
//   http://www.cnblogs.com/AndyJee/p/3805594.html
//   http://www.cnblogs.com/libing64/archive/2012/02/11/2878734.html
//   http://blog.csdn.net/morewindows/article/details/8239678
//   http://blog.csdn.net/xiaowei_cqu/article/details/7600666
//
#ifndef OPENCV_API_H
#define OPENCV_API_H

#include <Windows.h>
#include <tchar.h>
#include <assert.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "graphics.h"

#ifdef _DEBUG
    #pragma comment(lib, "IlmImfd.lib")
    #pragma comment(lib, "libjasperd.lib")
    #pragma comment(lib, "libjpegd.lib")
    #pragma comment(lib, "libpngd.lib")
    #pragma comment(lib, "libtiffd.lib")
    #pragma comment(lib, "opencv_calib3d2413d.lib")
    #pragma comment(lib, "opencv_contrib2413d.lib")
    #pragma comment(lib, "opencv_core2413d.lib")
    #pragma comment(lib, "opencv_features2d2413d.lib")
    #pragma comment(lib, "opencv_flann2413d.lib")
    #pragma comment(lib, "opencv_gpu2413d.lib")
    #pragma comment(lib, "opencv_highgui2413d.lib")
    #pragma comment(lib, "opencv_imgproc2413d.lib")
    #pragma comment(lib, "opencv_legacy2413d.lib")
    #pragma comment(lib, "opencv_ml2413d.lib")
    #pragma comment(lib, "opencv_nonfree2413d.lib")
    #pragma comment(lib, "opencv_objdetect2413d.lib")
    #pragma comment(lib, "opencv_ocl2413d.lib")
    #pragma comment(lib, "opencv_photo2413d.lib")
    #pragma comment(lib, "opencv_stitching2413d.lib")
    #pragma comment(lib, "opencv_superres2413d.lib")
    #pragma comment(lib, "opencv_ts2413d.lib")
    #pragma comment(lib, "opencv_video2413d.lib")
    #pragma comment(lib, "opencv_videostab2413d.lib")
    #pragma comment(lib, "zlibd.lib")
#else
    #pragma comment(lib, "IlmImf.lib")
    #pragma comment(lib, "libjasper.lib")
    #pragma comment(lib, "libjpeg.lib")
    #pragma comment(lib, "libpng.lib")
    #pragma comment(lib, "libtiff.lib")
    #pragma comment(lib, "opencv_calib3d2413.lib")
    #pragma comment(lib, "opencv_contrib2413.lib")
    #pragma comment(lib, "opencv_core2413.lib")
    #pragma comment(lib, "opencv_features2d2413.lib")
    #pragma comment(lib, "opencv_flann2413.lib")
    #pragma comment(lib, "opencv_gpu2413.lib")
    #pragma comment(lib, "opencv_highgui2413.lib")
    #pragma comment(lib, "opencv_imgproc2413.lib")
    #pragma comment(lib, "opencv_legacy2413.lib")
    #pragma comment(lib, "opencv_ml2413.lib")
    #pragma comment(lib, "opencv_nonfree2413.lib")
    #pragma comment(lib, "opencv_objdetect2413.lib")
    #pragma comment(lib, "opencv_ocl2413.lib")
    #pragma comment(lib, "opencv_photo2413.lib")
    #pragma comment(lib, "opencv_stitching2413.lib")
    #pragma comment(lib, "opencv_superres2413.lib")
    #pragma comment(lib, "opencv_ts2413.lib")
    #pragma comment(lib, "opencv_video2413.lib")
    #pragma comment(lib, "opencv_videostab2413.lib")
    #pragma comment(lib, "zlib.lib")
#endif
///////////////////////////////////////////////////////////////////////

typedef struct Color3b
{
    uchar red;
    uchar green;
    uchar blue;
} Color3b;


static double GrayMean(IplImage* grayImagIn)
{
    int i;
    double sum = 0;

    uchar * pixelData = (uchar*) grayImagIn->imageDataOrigin;

    for (i = 0; i < grayImagIn->imageSize; ++i) {
        sum += *pixelData++;
    }
    return sum / grayImagIn->imageSize;
}


static int Color2Gray(const char * rgbInFileBmp, const char * grayOutFileBmp, int fixWidth)
{
    int ret = 0;

    IplImage* rgbImagIn = cvLoadImage(rgbInFileBmp, CV_LOAD_IMAGE_UNCHANGED);

    if (! rgbImagIn) {
        return (-1); 
    }

    IplImage *grayImagTmp = cvCreateImage(cvGetSize(rgbImagIn), IPL_DEPTH_8U, 1);
    if (! grayImagTmp) {
        cvReleaseImage(&rgbImagIn);
        return (-1); 
    }

    CvSize size = cvGetSize(grayImagTmp);

    float factor = 1.0f;
    if (fixWidth > 0) {
        factor = fixWidth / ((float) size.width);
    } else {
        factor = 1.0f;
    }

    size.width = (int) ceil(size.width * factor);
    if (size.width % 4) {
        size.width = ((size.width + 3) / 4) * 4;
    }

    size.height = (int) ceil(size.height * factor);

    IplImage *grayImagOut = cvCreateImage(size, IPL_DEPTH_8U, 1);
    if (! grayImagOut) {
        cvReleaseImage(&rgbImagIn);
        cvReleaseImage(&grayImagTmp);
        return (-1);
    }

    if (rgbImagIn->nChannels > 1) {
        cvCvtColor(rgbImagIn, grayImagTmp, CV_BGR2GRAY);

        if (grayImagTmp->width != grayImagOut->width || grayImagTmp->height != grayImagOut->height) {
            cvResize(grayImagTmp, grayImagOut, CV_INTER_AREA);
            ret = cvSaveImage(grayOutFileBmp, grayImagOut);
        } else {
            ret = cvSaveImage(grayOutFileBmp, grayImagTmp);
        }
    } else {
        if (rgbImagIn->width != grayImagOut->width || rgbImagIn->height != grayImagOut->height) {
            cvResize(rgbImagIn, grayImagOut, CV_INTER_AREA);
            ret = cvSaveImage(grayOutFileBmp, grayImagOut);
        } else {
            ret = cvSaveImage(grayOutFileBmp, rgbImagIn);
        }
    }

    assert(ret == 1);

    cvReleaseImage(&rgbImagIn);
    cvReleaseImage(&grayImagTmp);
    cvReleaseImage(&grayImagOut);

    return ret;
}


static int Gray2Mono(const char * grayInFileBmp, const char * monoOutFileBmp,
    int thresholdType = CV_THRESH_OTSU|CV_THRESH_BINARY, int maxValue = 255)
{
    int ret = 0;

    IplImage* grayImagIn = cvLoadImage(grayInFileBmp, CV_LOAD_IMAGE_UNCHANGED);

    if (! grayImagIn) {
        return (-1); 
    }

    IplImage *monoImagOut = cvCreateImage(cvGetSize(grayImagIn), IPL_DEPTH_8U, 1);
    if (! monoImagOut) {
        cvReleaseImage(&grayImagIn);
        return (-1); 
    }

    double threshold = GrayMean(grayImagIn);

    cvThreshold(grayImagIn, monoImagOut, threshold, maxValue, thresholdType);

    ret = cvSaveImage(monoOutFileBmp, monoImagOut);
    assert(ret == 1);

    cvReleaseImage(&grayImagIn);
    cvReleaseImage(&monoImagOut);

    return ret;
}


static int BinarizeMono(const char * monoInOutFile, uchar zeroPixel)
{
    int ret = 0;
    IplImage * monoImage = cvLoadImage(monoInOutFile, CV_LOAD_IMAGE_UNCHANGED);
    int i = 0, j = 0;
    int width = monoImage->width;
    int height = monoImage->height;

    for (i = 0; i < height;  i++) {
        for (j = 0; j < width; j++) {
            if (CV_IMAGE_ELEM(monoImage, uchar, i, j) == zeroPixel) {
                CV_IMAGE_ELEM(monoImage, uchar, i, j) = 0;
            } else {
                CV_IMAGE_ELEM(monoImage, uchar, i, j) = 255;
            }
        }
    }

    ret = cvSaveImage(monoInOutFile, monoImage);
    assert(ret == 1);
    cvReleaseImage(&monoImage);
    return ret;
}


static int ThinMono(const char * srcMonoFile, const char * dstMonoFile, int iterations = 1)
{
    IplImage * srcImage;
    IplImage * dstImage;
    int width, height;

    int n = 0, i = 0, j = 0, ap, p2, p3, p4, p5, p6, p7, p8, p9;

    srcImage = cvLoadImage(srcMonoFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! srcImage) {
        return (-1);
    }

    if (srcMonoFile != dstMonoFile && strcmp(srcMonoFile, dstMonoFile)) {
        dstImage = cvCreateImage(cvGetSize(srcImage), srcImage->depth, srcImage->nChannels);
        if (! dstImage) {
            cvReleaseImage(&srcImage);
            return (-1);
        }
        cvCopy(srcImage, dstImage);
    } else {
        dstImage = srcImage;
    }

    width = dstImage->width;
    height = dstImage->height;

    for (n = 0; n < iterations; n++) {
        IplImage* tmpimg = cvCloneImage(dstImage);

        for (i = 0; i < height;  i++) {
            for (j = 0; j < width; j++) {
                if (CV_IMAGE_ELEM(tmpimg, byte, i, j) == 1) {
                    ap = 0;
                    p2 = (i == 0)? 0 : CV_IMAGE_ELEM(tmpimg, byte, i-1, j);
                    p3 = (i == 0 || j == width-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i-1, j+1);

                    if (p2 == 0 && p3 == 1) {
                        ap++;
                    }

                    p4 = (j == width-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i, j+1);
                    if (p3 == 0 && p4 == 1) {
                        ap++;
                    }

                    p5 = (i == height-1 || j == width-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j+1);
                    if (p4 == 0 && p5 == 1) {
                        ap++;
                    }

                    p6 = (i == height-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j);
                    if (p5 == 0 && p6 == 1) {
                        ap++;
                    }

                    p7 = (i == height-1 || j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j-1);
                    if (p6 == 0 && p7 == 1) {
                        ap++;
                    }

                    p8 = (j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i, j-1);
                    if (p7 == 0 && p8 == 1) {
                        ap++;
                    }

                    p9 = (i == 0 || j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i-1, j-1);
                    if (p8 == 0 && p9 == 1) {
                        ap++;
                    }

                    if (p9 == 0 && p2 == 1) {
                        ap++;
                    }

                    if ((p2+p3+p4+p5+p6+p7+p8+p9) > 1 && (p2+p3+p4+p5+p6+p7+p8+p9) < 7) {
                        if (ap == 1) {
                            if (!(p2 && p4 && p6)) {
                                if (!(p4 && p6 && p8)) {
                                    CV_IMAGE_ELEM(dstImage, byte, i, j) = 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        cvReleaseImage(&tmpimg);

        tmpimg = cvCloneImage(dstImage);

        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                if (CV_IMAGE_ELEM(tmpimg, byte, i, j) == 1) {
                    ap=0;
                    p2 = (i == 0) ? 0 : CV_IMAGE_ELEM(tmpimg,byte, i-1, j);
                    p3 = (i == 0 || j == width-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i-1, j+1);

                    if (p2 == 0 && p3 == 1) {
                        ap++;
                    }

                    p4 = (j == width-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i, j+1);
                    if (p3==0 && p4==1) {
                        ap++;
                    }
        
                    p5 = (i == height-1 || j == width-1)? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j+1);
                    if (p4 == 0 && p5 == 1) {
                        ap++;
                    }

                    p6 = (i == height-1) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j);
                    if (p5 == 0 && p6 == 1) {
                        ap++;
                    }

                    p7 = (i == height-1 || j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i+1, j-1);
                    if (p6 == 0 && p7 == 1) {
                        ap++;
                    }

                    p8 = (j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i, j-1);
                    if (p7 == 0 && p8 == 1) {
                        ap++;
                    }

                    p9 = (i == 0 || j == 0) ? 0 : CV_IMAGE_ELEM(tmpimg, byte, i-1, j-1);

                    if (p8==0 && p9==1) {
                        ap++;
                    }

                    if (p9==0 && p2==1) {
                        ap++;
                    }

                    if ((p2+p3+p4+p5+p6+p7+p8+p9) > 1 && (p2+p3+p4+p5+p6+p7+p8+p9) < 7) {
                        if (ap == 1) {
                            if (p2*p4*p8 == 0) {
                                if (p2*p6*p8 == 0) {
                                    CV_IMAGE_ELEM(dstImage, byte, i, j)=0;
                                }
                            }
                        }
                    }
                }
            }
        }           
        cvReleaseImage(&tmpimg);
    }

    ap = cvSaveImage(dstMonoFile, dstImage);
    assert(ap == 1);

    if (srcImage != dstImage) {
        cvReleaseImage(&srcImage);
    }
    cvReleaseImage(&dstImage);

    return ap;
}



static IplImage* RotateImageData(IplImage* img, double angle_degree, CvScalar backclr)
{
    double angle = angle_degree * CV_PI / 180.0f;
    double a = sin(angle);
    double b = cos(angle);

    double width = img->width;
    double height=img->height;  

    int width_rotate = (int) ceil(height * fabs(a) + width * fabs(b));
    int height_rotate = (int) ceil(width * fabs(a) + height * fabs(b));

    width_rotate = ((width_rotate + 3) / 4) * 4;

    IplImage * img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img->depth, img->nChannels);
    cvZero(img_rotate);

    int temp_width = (int) ceil(sqrt(width * width + height * height));
    temp_width = (((int) temp_width + 3) / 4) * 4;

    int tempX = (int) ceil((temp_width + 1) / 2 - width / 2);
    int tempY = (int) ceil((temp_width + 1) / 2 - height / 2);

    IplImage* temp = cvCreateImage(cvSize((int) temp_width, (int) temp_width), img->depth, img->nChannels);
    cvSet(temp, backclr);

    cvSetImageROI(temp, cvRect(tempX, tempY, (int) width, (int) height));    
    cvCopy(img, temp, 0);    
    cvResetImageROI(temp);    

    /* rot matrix:
     *   [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
     *   [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
     */
    float m[6];

    m[0] = (float) b;
    m[1] = (float) a;
    m[2] = temp->width * 0.5f;

    m[3] = -m[1];
    m[4] = m[0];
    m[5] = temp->height * 0.5f;

    CvMat M = cvMat(2, 3, CV_32F, m);

    cvGetQuadrangleSubPix(temp, img_rotate, &M);
    cvReleaseImage(&temp);

    return img_rotate;
}


static int RotateImage(const char * srcImageFile, const char * dstImageFile, double angle_degree, CvScalar backclr)
{
    int ret;
    IplImage * srcImage;
    IplImage * dstImage;

    srcImage = cvLoadImage(srcImageFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! srcImage) {
        return (-1);
    }

    dstImage = RotateImageData(srcImage, angle_degree, backclr);
    if (! dstImage) {
        cvReleaseImage(&srcImage);
        return (-1);
    }

    ret = cvSaveImage(dstImageFile, dstImage);

    cvReleaseImage(&srcImage);
    cvReleaseImage(&dstImage);

    return ret;
}


static int ResizeImage(const char * srcImageFile, const char * dstImageFile, float widthRatio, float heightRatio)
{
    IplImage * srcImag;
    IplImage * dstImag;

    int ret = 0;

    srcImag = cvLoadImage(srcImageFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! srcImag) {
        return (-1);
    }

    int newWidth = (((int) ceil(srcImag->width * widthRatio) + 3) / 4) * 4;
    int newHeight = (int) ceil(srcImag->height * heightRatio);

    dstImag = cvCreateImage(cvSize(newWidth, newHeight), srcImag->depth, srcImag->nChannels);
    if (! dstImag) {
        cvReleaseImage(&srcImag);
        return (-1);
    }

    if (widthRatio > 1.0f && heightRatio > 1.0f) {
        cvResize(srcImag, dstImag, CV_INTER_LINEAR);
    } else {
        cvResize(srcImag, dstImag, CV_INTER_AREA);
    }

    ret = cvSaveImage(dstImageFile, dstImag);

    cvReleaseImage(&dstImag);
    cvReleaseImage(&srcImag);

    return ret;
}


static int ClipImage(const char * srcImageFile, CvRect rect, const char * clipImageFile)
{
    IplImage * srcImag;
    IplImage * clipImag;

    int ret = 0;

    if (rect.x < 0) {
        return -2;
    }

    if (rect.y < 0) {
        return -3;
    }

    srcImag = cvLoadImage(srcImageFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! srcImag) {
        return (-1);
    }

    if (srcImag->width < rect.width + rect.x) {
        cvReleaseImage(&srcImag);
        return (-3);
    }

    if (srcImag->height < rect.height + rect.y) {
        cvReleaseImage(&srcImag);
        return (-4);
    }

    clipImag = cvCreateImage(cvSize(rect.width, rect.height), srcImag->depth, srcImag->nChannels);
    if (! clipImag) {
        cvReleaseImage(&srcImag);
        return (-1);
    }

    cvSetImageROI(srcImag, rect);

    cvCopy(srcImag, clipImag, 0);

    ret = cvSaveImage(clipImageFile, clipImag);

    cvResetImageROI(srcImag);

    cvReleaseImage(&clipImag);
    cvReleaseImage(&srcImag);

    return ret;
}


static int HoughLines(const char * thinImageFile, const char * outLineFile,
    int threshold, double line_len, double line_gap,
    LineVector ** ppOutLines)
{
    int i;

    IplImage * srcThinImg;
    IplImage * dstThinImg;

    IplImage * outLineClr;
    CvMemStorage * storage;

    CvSeq * lines = 0;
    int numLines = 0;

    *ppOutLines = 0;

    srcThinImg = cvLoadImage(thinImageFile, CV_LOAD_IMAGE_UNCHANGED);
    if (! srcThinImg) {
        return (-1);
    }

    storage = cvCreateMemStorage(0);
    if (! storage) {
        cvReleaseImage(&srcThinImg);
        return (-1);
    }

    dstThinImg = cvCreateImage(cvGetSize(srcThinImg), IPL_DEPTH_8U, 1);
    if (! dstThinImg) {
        cvReleaseImage(&srcThinImg);
        cvReleaseMemStorage(&storage);
        return (-1);
    }

    outLineClr = cvCreateImage(cvGetSize(srcThinImg), IPL_DEPTH_8U, 3);
    if (! outLineClr) {
        cvReleaseImage(&srcThinImg);
        cvReleaseImage(&dstThinImg);
        cvReleaseMemStorage(&storage);
        return (-1);
    }
 
    // DO NOT USE cvCanny! since srcThinImg has been binarized.
    //   cvCanny(srcThinImg, dstThinBmp, 50, 150, 3);
    cvCopy(srcThinImg, dstThinImg);
    cvCvtColor(dstThinImg, outLineClr, CV_GRAY2BGR);

    lines = cvHoughLines2(dstThinImg, // 输入 8-比特、单通道 (二值) 图像, 其内容会被函数改变
        storage,                 // 检测到的线段存储仓
        CV_HOUGH_PROBABILISTIC,  // 概率 Hough 变换
        1,                       // 与象素相关单位的距离精度
        CV_PI/180,               // 弧度测量的角度精度
        threshold,               // 如果相应的累计值大于 threshold， 则函数返回的这个线段
        line_len,                // 它是最小线段长度
        line_gap                 // 在同一条直线上进行碎线段连接的最大间隔值(gap),
                                 //   即当同一条直线上的两条碎线段之间的间隔小于param2时，将其合二为一
    );

    if (! lines) {
        cvReleaseImage(&srcThinImg);
        cvReleaseImage(&dstThinImg);
        cvReleaseImage(&outLineClr);
        cvReleaseMemStorage(&storage);
        return (-1);
    }
 
    numLines = lines->total;
    if (numLines > 0) {
        LineVector * outLines = (LineVector *) malloc(sizeof(LineVector) * lines->total);

        for (i = 0; i < numLines; i++) {
            CvPoint* line = (CvPoint*) cvGetSeqElem(lines, i);
            cvLine(outLineClr, line[0], line[1], CV_RGB(255, 0, 0), 1, 4, 0);

            outLines[i].start.x = (float) line[0].x;
            outLines[i].start.y = (float) line[0].y;

            outLines[i].end.x = (float) line[1].x;
            outLines[i].end.y = (float) line[1].y;

            outLines[i].azimuth = GetAzimuth(&outLines[i].start, &outLines[i].end);
        }

        *ppOutLines = outLines;
    }

    i = cvSaveImage(outLineFile, outLineClr);
    assert(i == 1);

    cvReleaseImage(&srcThinImg);
    cvReleaseImage(&dstThinImg);
    cvReleaseImage(&outLineClr);
    cvReleaseMemStorage(&storage);

    return (numLines);
}


#define MONO_BLACK   0
#define MONO_WHITE   1
#define FIND_DIST    3


static inline uchar GetMonoPixel(IplImage * grayImag, int x, int y)
{
    uchar v = (uchar) grayImag->imageData[y * grayImag->width + x];
    return (uchar) ((v + 254) / 255);
}


static inline int GetTotalMonoPixels(const char * monoFileBmp, int monoColor)
{
    int clrPixels = 0;

    IplImage * monoBmp = cvLoadImage(monoFileBmp, CV_LOAD_IMAGE_UNCHANGED);
    if (monoBmp) {
        uchar v;
        int i;
        char * p = monoBmp->imageDataOrigin;

        for (i = 0; i < monoBmp->imageSize; ++i) {
            v = (uchar) (*p++);
            v = (uchar) ((v + 254) / 255);

            if (v == monoColor) {
                ++clrPixels;
            }
        }

        cvReleaseImage(&monoBmp);
    }

    return clrPixels;
}


static int FindMonoTarget(const char * monoFileBmp, Point2f * pixels, int numpixs,
    const char * monoTgtFileBmp, int centerX, int centerY, Point2f *pixel)
{
    IplImage * monoBmp;
    IplImage * monoTgt;

    int i, x, y, tx, ty, diff, maxDiff;

    monoBmp = cvLoadImage(monoFileBmp, CV_LOAD_IMAGE_UNCHANGED);
    if (! monoBmp) {
        return (-1);
    }

    monoTgt = cvLoadImage(monoTgtFileBmp, CV_LOAD_IMAGE_UNCHANGED);
    if (! monoTgt) {
        cvReleaseImage(&monoBmp);
        return (-1);
    }

    maxDiff = 0;

    for (i = 0; i < numpixs; ++i) {
        int Xi = (int) pixels[i].x;
        int Yi = (int) pixels[i].y;

        for (x = Xi - FIND_DIST; x < Xi + FIND_DIST; ++x) {
            for (y = Yi - FIND_DIST; y < Yi + FIND_DIST; ++y) {
                diff = 0;
                for (tx = 0; tx < monoTgt->width; ++tx) {
                    for (ty = 0; ty < monoTgt->height; ++ty) {
                        if (GetMonoPixel(monoTgt, tx, ty)) {
                            if (! GetMonoPixel(monoBmp, x - centerX + tx, y - centerY + ty)) {
                                ++diff;
                            }
                        }
                    }
                }

                if (diff > maxDiff) {
                    maxDiff = diff;
                    pixel->x = (float) x;
                    pixel->y = (float) y;
                }
            }
        }
    }

    cvReleaseImage(&monoBmp);
    cvReleaseImage(&monoTgt);

    return maxDiff;
}

///////////////////////////////////////////////////////////////////////
#endif // OPENCV_API_H