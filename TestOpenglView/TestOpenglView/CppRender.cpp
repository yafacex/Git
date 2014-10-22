//
//  CppRender.cpp
//  TestOpenglView
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "YFGL_Utils/glYF.h"
#include "CppRender.h"
//#include "QuadTest.h"//gl2
#include "PolyTest.h"//gl2
#include "VBOTest.h"
#include "TerrianTest.h"
#include "Bitmap.h"
#include "WikiTest.h"
#include "YFGL_Utils/Shader.h"
//#include "RestartIndexTest.h"
#include "TestWater.h"
#include <math.h>
#include <assert.h>

CppRender* CppRender::m_Instance=NULL;
TerrianTest ter;
VBOTest vbo;
PolyTest poly;
TestWater water;
void CppRender::render(){
    
//    water.update();
//    return;
    
    PerfLog("haha");
    
    update();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
//    ter.draw();
    vbo.draw();
//    poly.testArray();
    
//    QuadTest quadTest;
//    PolyTest polyTest;
//    VBOTest vbo;
//    WikiTest wiki;
    
//    glBegin(GL_TRIANGLES);
//    glVertex3f(-0.3, 0, 0);
//    glVertex3f(0.3, 0.3, 0);
//    glVertex3f(0.3, -0.3, 0);
//    glEnd();
    
    glFlush();
}
void CppRender::update(){
    mRotate += M_PI * 0.1;
}
void CppRender::init(){
//    initShader();
    const GLubyte* sv = glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("ver::%s",sv);
    water.init("/Users/yafacex/Documents/LUA/Cpp/TestOpenglView/TestOpenglView/TextureReader/WATER1.BW");
//    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
void CppRender::initShader(){
    GLuint vertexShader,fragmentShader,program;
    
    vertexShader = initVertexShader();
    fragmentShader = initFragmentShader();
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    GLint bLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &bLinked);
    
    if (bLinked) {
        glUseProgram(program);
    }else{
        GLint logLen;
        GLint buffSize;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLen);
        buffSize = logLen * sizeof(GLchar);
        GLchar* log = (GLchar*)malloc(buffSize);
        glGetShaderInfoLog(vertexShader, buffSize, &logLen, log);
        printf("ShaderLog::%s\n",log);
        assert(false);
    }
}
GLuint CppRender::initVertexShader(){
    GLuint shader;
    GLint bComplied;
    
    const GLchar* shaderSrc[] = {
        "#version 150\n"
        "void main()"
        "{"
//        "vec4 c = vec4(0.3,0.3,0.3,0);"
//        "gl_Position = gl_Position + c;"
        "}"
    };
    
    
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &bComplied);
    
    if (!bComplied) {
        GLint logLen;
        GLint buffSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        buffSize = logLen * sizeof(GLchar);
        GLchar* log = (GLchar*)malloc(buffSize);
        glGetShaderInfoLog(shader, buffSize, &logLen, log);
        printf("ShaderLog::%s\n",log);
        assert(false);
    }
    return shader;
}
GLuint CppRender::initFragmentShader(){
    GLuint shader;
    GLint bComplied;
    
    const GLchar* shaderSrc[] = {
        "#version 150\n"
        "void main (void)"
        "{"
        
        "}"
    };
    
    
    shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, shaderSrc, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &bComplied);
    
    if (!bComplied) {
        GLint logLen;
        GLint buffSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        buffSize = logLen * sizeof(GLchar);
        GLchar* log = (GLchar*)malloc(buffSize);
        glGetShaderInfoLog(shader, buffSize, &logLen, log);
        printf("ShaderLog::%s\n",log);
        assert(false);
    }
    return shader;
}