//
//  glYF.h
//  TestOpenglView
//
//  Created by yafacex on 14-3-26.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_glYF_h
#define TestOpenglView_glYF_h

#include"OpenGL/gl3.h"
//#include"OpenGL/OpenGL.h"
#include <iostream>

//group
void glVertexG3f (int vertexNum,GLfloat *v){
    GLfloat x,y,z;
    for (int i = 0; i < vertexNum; ++i) {
        x = *(v + i * 3 + 0);
        y = *(v + i * 3 + 1);
        z = *(v + i * 3 + 2);
//        glVertex3f(x, y, z);
        printf("[%f\t%f\t%f]\n",x,y,z);
    }
}
//array
typedef GLfloat glV3f[3];
typedef GLfloat glV12f[12];
typedef GLfloat glV16f[16];
#define V3(v,n,i) *(v + 3 * n + i) 

glV12f* glLinkf3to12(glV12f* ret,glV3f* a1,glV3f* a2,glV3f* a3,glV3f* a4){
    memcpy(ret + 0, a1, sizeof(GLfloat) * 3);
    memcpy(ret + 3, a2, sizeof(GLfloat) * 3);
    memcpy(ret + 6, a3, sizeof(GLfloat) * 3);
    memcpy(ret + 9, a4, sizeof(GLfloat) * 3);
    return ret;
};

//Identity
enum glIdentityFlag{
    IdentityFlag3All = 0b111,
    IdentityFlag3TL  = 0b010,
    IdentityFlag3TR  = 0b110,
    IdentityFlag3BR  = 0b100,
    IdentityFlag3BL  = 0b000,
    IdentityFlag12SQ =  IdentityFlag3BL << 9 |
                        IdentityFlag3TL << 6 |
                        IdentityFlag3TR << 3 |
                        IdentityFlag3BR
};
GLfloat* glIdentity(GLfloat* v,int flag,GLfloat positive,GLfloat negtive){
    int i = 0;
     while ( 1 != flag){
        if(flag & 0b1){
            *(v + i) = positive;
        }else{
            *(v + i) = negtive;
        }
        flag = flag >> 1;
        ++ i ;
     }
    return v;
};

glV12f* glIdentity12(glV12f* v,GLfloat positive,GLfloat negtive){
    //1000010011001 convert clock-wise
    //1001011010000 clock-wise
    glIdentity(*v,0b1000010011001,positive,negtive);
    return v;
}
glV12f* glMult12(glV12f* v,float scale){
    for (int i = 0; i < 12; ++i) {
        (*v)[i] *= scale;
    }
    return v;
}

//debug

void glPrintV12f(glV12f* v){
    for (int i = 0; i < 12; ++i) {
        printf("%f\t",(*v)[i]);
        if (0 == (i + 1)%3) {
            printf("\n");
        }
    }
    printf("\n");
}
void glPrintV16f(glV16f* v){
    for (int i = 0; i < 16; ++i) {
        printf("%f\t",(*v)[i]);
        if (0 == (i + 1)%4) {
            printf("\n");
        }
    }
    printf("\n");
}

#define PerfLog(__INFO__)\
_PerformanceLog(__FILE__,__LINE__,__INFO__)
class _PerformanceLog{
public:
    char *_file,*_info;
    char _pureFile[100];
    int _line;
    clock_t begin;
    _PerformanceLog(char* file,int line,char * info){
        _file = file;
        _line = line;
        _info = info;
        begin = clock();
        int i = 0;
        int lastSplit = 0;
        while (*(file + i) != '\0') {
            if (*(file + i) == '/') {
                lastSplit = i;
            }
            ++ i;
        }
        sprintf(_pureFile, "%s",file+lastSplit);
    };
    ~_PerformanceLog(){
        printf("%s LINE:%d %s CLOCK:%ld\n",_pureFile,_line,_info,clock() - begin);
    };
};

#endif
