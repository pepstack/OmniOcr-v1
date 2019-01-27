// tesseract_api.h
//
// Refer:
//    http://www.cnblogs.com/cappuccino/p/4650665.html
//
#ifndef TESSERACT_API_H
#define TESSERACT_API_H

#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(disable:4099)
#pragma warning(disable:4305)

// liblept171.dll
#include <leptonica/allheaders.h>

// libtesseract304.dll
// DO NOT USE c++ since it will cause error!!
// #include <tesseract/baseapi.h>

// USE c api
#include <tesseract/capi.h>


#ifdef _DEBUG
#  pragma  comment(lib, "libtesseract304d.lib")
#  pragma  comment(lib, "liblept171d.lib")
#else
#  pragma  comment(lib, "libtesseract304.lib")
#  pragma  comment(lib, "liblept171.lib")
#endif


#pragma warning(pop)
///////////////////////////////////////////////////////////////////////
#endif // TESSERACT_API_H