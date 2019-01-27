# OmniOcr-v1
病例识别的 OCR Window 程序

此程序为商业程序，不可以在开源平台上发布和公开！！

## 需要的依赖包在：

  https://github.com/pepstack/ocr-win-deps


## 按照下面的目录结构复制文件:

  project_home/
    |
    +--------- opencv-2.4.13-win/
    |
    +--------- tesseract-build-vs2013/
    |
    +--------- tesseract-langdata/
    |
    +--------- workspace/
                    |
                    +---------- OmniOcr-v1/


使用 vs2013 打开 OmniOcrCli/OmniOcrCli.sln, 编译即可！

## 编译好，发布的程序目录结构：

    ocr-dist/
        |
        +-------- liblept171.dll
        |
        +-------- liblog4c.dll
        |
        +-------- libtesseract304.dll
        |
        +-------- OmniOcrCli.exe
        |
        +-------- README.txt
        |
        +--------- OcrBMPs/
        |              |
        |              +-------- PLA306-RPT_TNB33/
        |
        +--------- stencil/
        |              |
        |              +-------- PLA306-RPT_TNB33.stencil
        |
        +--------- tessdata/            (即: tesseract-build-vs2013/tessdata/)
                       |
                       +-------- configs/
                       |
                       +-------- tessconfigs/
 