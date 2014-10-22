//
//  Bitmap.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-22.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_Bitmap_h
#define TestOpenglView_Bitmap_h

//
//  bitmap.c
//  TestOpenglView
//
//  Created by yafacex on 14-5-22.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <stdio.h>

typedef unsigned int DWORD;//4 byte
typedef unsigned short WORD;//2 byte
typedef unsigned int LONG;//4 byte
typedef unsigned char BYTE;

#pragma pack(1)

//14 byte
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;//位图文件的类型，必须为BM(1-2字节）
    DWORD bfSize;//位图文件的大小，以字节为单位（3-6字节，低位在前）
    WORD bfReserved1;//位图文件保留字，必须为0(7-8字节）
    WORD bfReserved2;//位图文件保留字，必须为0(9-10字节）
    DWORD bfOffBits;//位图数据的起始位置，以相对于位图（11-14字节，低位在前）
    //文件头的偏移量表示，以字节为单位
}BITMAPFILEHEADER ;


//40byte
typedef struct tagBITMAPINFOHEADER{
    DWORD biSize;//本结构所占用字节数（15-18字节）
    LONG biWidth;//位图的宽度，以像素为单位（19-22字节）
    LONG biHeight;//位图的高度，以像素为单位（23-26字节）
    WORD biPlanes;//目标设备的级别，必须为1(27-28字节）
    WORD biBitCount;//每个像素所需的位数，必须是1（双色），（29-30字节）
    //4(16色），8(256色）16(高彩色)或24（真彩色）之一
    DWORD biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
    //1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
    DWORD biSizeImage;//位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
    LONG biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
    LONG biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
    DWORD biClrUsed;//位图实际使用的颜色表中的颜色数（47-50字节）
    DWORD biClrImportant;//位图显示过程中重要的颜色数（51-54字节）
}BITMAPINFOHEADER ;

//4 byte
typedef struct tagRGBQUAD{
    BYTE rgbBlue;//蓝色的亮度（值范围为0-255)
    BYTE rgbGreen;//绿色的亮度（值范围为0-255)
    BYTE rgbRed;//红色的亮度（值范围为0-255)
    BYTE rgbReserved;//保留，必须为0
}RGBQUAD ;

//44byte
typedef struct tagBITMAPINFO{
    BITMAPINFOHEADER bmiHeader;//位图信息头
    RGBQUAD bmiColors[1];//颜色表
}BITMAPINFO ;



typedef struct rgb{
    BYTE b;
    BYTE g;
    BYTE r;
}RGB ;


class BmpImage{
public:
    BmpImage():pixels(NULL){};
    ~BmpImage(){
        delete pixels;
    };
    void readBMP(char * fileName)
    {
        int headerN = sizeof(BITMAPFILEHEADER);
        FILE* fp=fopen(fileName,"rb");
        //ReadtheBitmapfileheader;
        fread(&fileHeader,sizeof(BITMAPFILEHEADER),1,fp);
        //ReadtheBitmapinfoheader;
        fread(&infoHeader,sizeof(BITMAPINFOHEADER),1,fp);
        //为简化代码，只处理24位彩色
        if(infoHeader.biBitCount==24)
        {
            w = infoHeader.biWidth;
            h = infoHeader.biHeight;
            w = 255;h=154;
            int size = w*h;
            pixels = (RGB*)malloc(sizeof(RGB)*size);
            fread(pixels,sizeof(RGB),size,fp);
        }
        fclose(fp);
    }
    
    void writeBMP(char * fileName){
        FILE* fp=fopen(fileName,"wb");
        if (pixels) {
            fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
            fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
            fwrite(pixels, sizeof(RGB), w*h, fp);
        }
        fclose(fp);
    }
    
    void isSame(BmpImage* right){
        //file header
        char fHL[sizeof(BITMAPFILEHEADER)],fHR[sizeof(BITMAPFILEHEADER)];
        memcpy(fHL, &right->fileHeader, sizeof(BITMAPFILEHEADER));
        memcpy(fHR, &this->fileHeader, sizeof(BITMAPFILEHEADER));
        for (int i=0; i<sizeof(BITMAPFILEHEADER); ++i) {
            if (fHL[i]!=fHR[i]) {
                printf("diff in fileHeader byte %d\n",i);
            }
        }
        //info header
        char iHL[sizeof(BITMAPINFOHEADER)],iHR[sizeof(BITMAPINFOHEADER)];
        memcpy(iHL, &this->infoHeader, sizeof(BITMAPINFOHEADER));
        memcpy(iHR, &right->infoHeader, sizeof(BITMAPINFOHEADER));
        for (int i=0; i<sizeof(BITMAPINFOHEADER); ++i) {
            if (iHL[i]!=iHR[i]) {
                printf("diff in infoHeader byte %d\n",i);
            }
        }
        //rgb
        char iPL[w*h],iPR[right->w*right->h];
        memcpy(iPL, this->pixels, sizeof(iPL));
        memcpy(iPR, right->pixels, sizeof(iPR));
        if (sizeof(iPL) == sizeof(iPR)) {
            for (int i = 0; i<sizeof(iPL); ++i) {
                if (iPL[i]!=iPR[i]) {
                    printf("diff in RGB byte %d\n",i);
                }
            }
        }
        
    }
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGB* pixels;
    int w,h;
};



#endif
