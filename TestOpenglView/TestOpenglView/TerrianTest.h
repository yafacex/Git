//
//  TerrianTest.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-21.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_TerrianTest_h
#define TestOpenglView_TerrianTest_h
#include "glYF.h"
#include "Bitmap.h"
#include <math.h>
//#include "Shader.h"
#include "OpenGL/gl.h"
class Terrian{
public:
    Terrian(int w,int l){
        pixelL = 1.0;pixelW = 1.0;
        mW = w;mL = l;
        alloc();
        debug = false;
    }
    ~Terrian(){
        delloc();
    };
    void alloc(){
        heightMap = (GLfloat**)malloc(sizeof(GLfloat*)*mW);
        for (int i = 0; i < mL; ++i) {
            heightMap[i] = (GLfloat*)malloc(sizeof(GLfloat)*mL);
        }
        
        verties = (GLfloat*)malloc(sizeof(GLfloat)*getVerLen());
        
        indices = (GLuint*)malloc(sizeof(GLuint)*getInLen());
        
        colors = (GLfloat*)malloc(sizeof(GLfloat)*getVerLen()*3);
    };
    void delloc(){
        for (int i = 0; i < mL; ++i) {
            delete heightMap[i];
        }
        delete heightMap;
        
        delete verties;
        delete indices;
        delete colors;
    };
    void initHeightMap(float angle,BmpImage& img){
        for (int i = 0; i<mW; ++i) {
            for (int j = 0; j<mL; ++j) {
//                GLfloat x = - pixelW * 0.5 + pixelW * i / (mW-1);
//                GLfloat y = - pixelL * 0.5 + pixelL * j / (mL-1);
//                GLfloat sq = sqrtf(x * x + y * y);
                GLfloat rx = (float)i/(mW-1);
                GLfloat ry = (float)j/(mL-1);
                RGB rgb = img.getRGB(rx, ry);
                heightMap[i][j] = (float)(rgb.r + rgb.g + rgb.b)/(255*3);
            }
        }
        smoothHM();
        smoothHM();
        smoothHM();
        smoothHM();
    };
    void smoothHM(){
        for (int i = 1; i<mW-1; ++i) {
            for (int j = 1; j<mL-1; ++j) {
                heightMap[i][j] =(
                heightMap[i-1][j-1]+
                heightMap[i-1][j]+
                heightMap[i-1][j+1]+
                heightMap[i][j-1]+
                heightMap[i][j]+
                heightMap[i][j+1]+
                heightMap[i+1][j-1]+
                heightMap[i+1][j]+
                heightMap[i+1][j+1])/9;
            }
        }
    }
    void initVertices(){
        int hmLen = mW * mL ;
        for (int i = 0; i<hmLen; ++i) {
            int offset = i * 3;
            int r = i/mW;
            int c = i%mW;
            verties[offset] = - pixelW * 0.5 + pixelW * c / (mW-1);
            verties[offset+1] = heightMap[r][c];
            verties[offset+2] = - pixelL * 0.5 + pixelL * r / (mL-1);
            int colorOffset = offset;
            colors[colorOffset] = (verties[offset] + 0.5 * pixelW)/pixelW;
            colors[colorOffset+1] = (verties[offset+2] + 0.5 * pixelL)/pixelL;
            GLfloat colorSQ = (pixelW * pixelW + pixelL * pixelL)*0.25+0.5;
            colors[colorOffset+2] = heightMap[r][c];//heightMap[r][c]/sqrtf(colorSQ);
            if (debug) {
                printf("ver:[%d\t]%f\t%f\t%f\n",i,
                       verties[offset],
                       verties[offset+1],
                       verties[offset+2]);
            }
        }
        int vLen = getVerLen();
        printf("verLen:%d\n",vLen);
    };
    void initIndicesForStrip(){
        
        for(int r = 0; r<mW-1 ; ++r){
            for (int c = 0; c<mL; ++c) {
                int index = r * mL + c ;
                int ext = 2*r;
                
                if (c==0&&r>0) {
                    indices[2*index+ext-1] = indices[2*index+ext-2];
                    if (debug) {
                        printf("ind:[%d\t]%d\n",2*index+ext-1,indices[2*index+ext-1]);
                    }
                }
                
                indices[2*index+ext] = index;
                indices[2*index+1+ext] = index + mL;
                
                
                if (debug) {
                    printf("ind:[%d\t%d\t]%d\t%d\n",
                           2*index+ext,
                           2*index+1+ext,
                           indices[2*index+ext],
                           indices[2*index+1+ext]);
                }
                
                if (c == mL-1&&r!=mW-2) {
                    indices[2*index+2+ext] = indices[2*index+1+ext];
                    if (debug) {
                        printf("ind:[%d\t]%d\n",2*index+2+ext,indices[2*index+2+ext]);
                    }
                }
            }
        }
        int len = getInLen();
        printf("InLen:%d\n",len);
    };
    inline int getVerLen(){return mW*mL*3;};
    inline int getInLen(){return 2*(mW-1)*mL + 2*(mW-1)-2;};
    inline int getQuadNumber(){
        return (mW-1)*(mL-1);
    }
    GLfloat **heightMap;
    GLfloat* verties;
    GLuint* indices;
    GLfloat* colors;
protected:
    int mW,mL;
    GLfloat pixelW ,pixelL ;
    bool debug;
};


class TerrianTest{
public:
    enum{w = 300 , h = 300 };
    TerrianTest():ter(w,h){
        
    };
    
    void draw(){
        if (!bInit) {
            img.readBMP("hm.bmp");
            ter.initHeightMap(mYAngel,img);
            ter.initVertices();
            ter.initIndicesForStrip();
            //            shader.genShader();
            bInit=true;
            initVBO();

        }

        glDrawElements(GL_TRIANGLE_STRIP, ter.getInLen(), GL_UNSIGNED_INT, NULL);
        
        const GLubyte* version = glGetString(GL_VERSION);
        printf("Version:%s\n",version);
        
        GLint ind;
        glGetIntegerv(GL_PRIMITIVE_RESTART_INDEX, &ind);
        
        GLboolean b = glIsEnabled(GL_PRIMITIVE_RESTART);
        GLuint uind = ind;
        if (b) {
            uind = 0;
        }
        
        rotate();
//        glDeleteBuffers(3, buffers);
    }
    void initVBO(){
        
        
        glGenBuffers(3, buffers);
//        {
//            GLuint vertexArrayObject;
//            glGenVertexArrays(1, &vertexArrayObject);
//            glBindVertexArray(vertexArrayObject);
//        }
        
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*ter.getVerLen(), ter.verties, GL_STATIC_DRAW);


//            GLint vPos = shader.getAttribLocation(Shader::VertexShader, "position");
//            glEnableVertexAttribArray(vPos);
//            glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glVertexPointer(3, GL_FLOAT, 0, NULL);
            glEnableClientState(GL_VERTEX_ARRAY);
        }
        
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ter.getInLen(), ter.indices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(VERTEX_POS_INDX); 
            glIndexPointer(GL_UNSIGNED_INT, 0, NULL);
        }
        
        {
            glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*ter.getVerLen(), ter.colors, GL_STATIC_DRAW);
//            GLint vColor = shader.getAttribLocation(Shader::VertexShader, "colour");
//            glEnableVertexAttribArray(vColor);
//            glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glColorPointer(3, GL_FLOAT, 0, NULL);
            glEnableClientState(GL_COLOR_ARRAY);
        }
        
//        glPrimitiveRestartIndex(INT32_MAX);
//        glEnable(GL_PRIMITIVE_RESTART);
        
//        glDeleteBuffers(3, buffers);
//        shader.use();
    }
    void rotate(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(45, 1, 0, 0);
        glRotatef(mYAngel, 0, 1, 0);
        glTranslatef(0, -0.2, -0.4);
        mYAngel += 2;
    };
    ~TerrianTest(){};
    static GLfloat mYAngel;
    Terrian ter;
    static bool bInit;
    BmpImage img;
    GLuint buffers[3];
//    Shader shader;
};
 GLfloat TerrianTest::mYAngel = 0;
bool TerrianTest::bInit = false;

#endif
