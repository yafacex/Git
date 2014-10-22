//
//  Render.h
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//
#ifndef __TestOpenglES__Render__
#define __TestOpenglES__Render__
#include <iostream>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <GLKit/GLKMatrix4.h>
#include <GLKit/GLKMatrix3.h>
#include <GLKit/GLKMathUtils.h>
#include "Shader.h"
#include <string>
enum GLVertexAttrib
{
    GLVertexAttribPosition,
    GLVertexAttribNormal,
    GLVertexAttribColor,
    GLVertexAttribTexCoord0,
    GLVertexAttribTexCoord1
};

typedef struct CSize_ {
    float width;
    float height;
}CSize;

class Render{
public:
    Render(){};
    ~Render(){};
    
    void setup(CSize viewSize,const char* path);
    void setupShader();
    void setupTexture();
    void update();
    void draw();
    void tearDown();
    void updateData();
protected:
//    GLuint _program;
    
    GLKMatrix4 _modelViewProjectionMatrix;
    GLKMatrix3 _normalMatrix;
    float _rotation;
    
    GLuint _vertexArray;
    GLuint _vertexBuffer;
    
    CSize mViewSize;
    
    std::string mPath;
    
    Shader mShader;
};

#endif /* defined(__TestOpenglES__Render__) */