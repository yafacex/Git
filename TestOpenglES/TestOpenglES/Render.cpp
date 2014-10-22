//
//  Render.cpp
//  TestOpenglES
//
//  Created by yafacex on 14-7-14.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "Render.h"
#include "TextureReader/BWReader.h"

// Uniform index.
enum
{
    CUNIFORM_MODELVIEWPROJECTION_MATRIX,
    CUNIFORM_NORMAL_MATRIX,
    CNUM_UNIFORMS
};
GLint cuniforms[CNUM_UNIFORMS];

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

//GLfloat g_CubeVertexData[288] =
//{
//    // Data layout for each line below is:
//    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
//    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,
//    
//    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
//    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,
//    
//    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
//    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f,
//    
//    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f,
//    
//    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f,
//    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f,
//    
//    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
//    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
//    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f,
//    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f
//};

GLfloat g_CubeVertexData[288] =
{
    // Data layout for each line below is:
    // positionX, positionY, positionZ,     normalX, normalY, normalZ,
    0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,  0.0,0.0,
    0.5f, 0.5f, -0.5f,         1.0f, 0.0f, 0.0f,  0.0,1.0,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,  1.0,1.0,
    0.5f, -0.5f, 0.5f,         1.0f, 0.0f, 0.0f,  1.0,1.0,
    0.5f, 0.5f, -0.5f,          1.0f, 0.0f, 0.0f, 1.0,0.0,
    0.5f, 0.5f, 0.5f,         1.0f, 0.0f, 0.0f,   0.0,0.0,
    
    0.5f, 0.5f, -0.5f,         0.0f, 1.0f, 0.0f,  0.0,0.0,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,  0.0,1.0,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,  1.0,1.0,
    0.5f, 0.5f, 0.5f,          0.0f, 1.0f, 0.0f,  1.0,1.0,
    -0.5f, 0.5f, -0.5f,        0.0f, 1.0f, 0.0f,  1.0,0.0,
    -0.5f, 0.5f, 0.5f,         0.0f, 1.0f, 0.0f,  0.0,0.0,
    
    -0.5f, 0.5f, -0.5f,        -1.0f, 0.0f, 0.0f, 0.0,0.0,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f, 0.0,1.0
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f, 1.0,1.0,
    -0.5f, 0.5f, 0.5f,         -1.0f, 0.0f, 0.0f, 1.0,1.0,
    -0.5f, -0.5f, -0.5f,       -1.0f, 0.0f, 0.0f, 1.0,0.0,
    -0.5f, -0.5f, 0.5f,        -1.0f, 0.0f, 0.0f, 0.0,0.0,
    
    -0.5f, -0.5f, -0.5f,       0.0f, -1.0f, 0.0f, 0.0,0.0,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f, 0.0,1.0,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f, 1.0,1.0,
    -0.5f, -0.5f, 0.5f,        0.0f, -1.0f, 0.0f, 1.0,1.0,
    0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f, 1.0,0.0,
    0.5f, -0.5f, 0.5f,         0.0f, -1.0f, 0.0f, 0.0,0.0,
    
    0.5f, 0.5f, 0.5f,          0.0f, 0.0f, 1.0f, 0.0,0.0,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f, 0.0,1.0,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f, 1.0,1.0,
    0.5f, -0.5f, 0.5f,         0.0f, 0.0f, 1.0f, 1.0,1.0,
    -0.5f, 0.5f, 0.5f,         0.0f, 0.0f, 1.0f, 1.0,0.0,
    -0.5f, -0.5f, 0.5f,        0.0f, 0.0f, 1.0f, 0.0,0.0,
    
    0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f, 0.0,0.0,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f, 0.0,1.0,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f, 1.0,1.0,
    0.5f, 0.5f, -0.5f,         0.0f, 0.0f, -1.0f, 1.0,1.0,
    -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, -1.0f, 1.0,0.0,
    -0.5f, 0.5f, -0.5f,        0.0f, 0.0f, -1.0f, 0.0,0.0,
};

void Render::setup(CSize viewSize,const char* path){
    mViewSize = viewSize;
    mPath = std::string(path);
    setupShader();
//    return;
    glEnable(GL_DEPTH_TEST);
    
    glGenVertexArraysOES(1, &_vertexArray);
    glBindVertexArrayOES(_vertexArray);
    
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_CubeVertexData), g_CubeVertexData, GL_STATIC_DRAW);
    long size = sizeof(g_CubeVertexData) / 4;
    glEnableVertexAttribArray(GLVertexAttribPosition);
    glVertexAttribPointer(GLVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
//    glVertexAttribPointer(<#GLuint indx#>, <#GLint size#>, <#GLenum type#>, <#GLboolean normalized#>, <#GLsizei stride#>, <#const GLvoid *ptr#>)
    glEnableVertexAttribArray(GLVertexAttribNormal);
    glVertexAttribPointer(GLVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
    
    glBindVertexArrayOES(0);
    
    setupTexture();
    
}
void Render::setupTexture(){
    return;
    BWReader reader;
    int width, height, components;
    std::string path = mPath + "/WATER1.BW";
    unsigned * data = reader.read_texture(path.c_str(), &width, &height, &components);
    GLuint texName;
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
void Render::setupShader(){
    mShader.genShader((mPath+"/Shader.vsh").c_str(), (mPath+"/Shader.fsh").c_str());
    mShader.compile();
    {
        glBindAttribLocation(mShader.program, GLVertexAttribPosition, "position");
        glBindAttribLocation(mShader.program, GLVertexAttribNormal, "normal");
    }
    mShader.link();
    mShader.validate();
    {
        cuniforms[CUNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(mShader.program, "modelViewProjectionMatrix");
        cuniforms[CUNIFORM_NORMAL_MATRIX] = glGetUniformLocation(mShader.program, "normalMatrix");
    }
}
void Render::update(){
    printf("caoooooo1\n");
    updateData();
    draw();
}
void Render::updateData(){
    float aspect = fabsf(mViewSize.width / mViewSize.height);
    GLKMatrix4 projectionMatrix = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.1f, 100.0f);
    
//    self.effect.transform.projectionMatrix = projectionMatrix;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf((GLfloat*)&projectionMatrix);
    
    GLKMatrix4 baseModelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -4.0f);
    baseModelViewMatrix = GLKMatrix4Rotate(baseModelViewMatrix, _rotation, 0.0f, 1.0f, 0.0f);
    
    // Compute the model view matrix for the object rendered with GLKit
    GLKMatrix4 modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, -1.5f);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    
//    self.effect.transform.modelviewMatrix = modelViewMatrix;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf((GLfloat*)&modelViewMatrix);
    
    
    // Compute the model view matrix for the object rendered with ES2
    modelViewMatrix = GLKMatrix4MakeTranslation(0.0f, 0.0f, 1.5f);
    modelViewMatrix = GLKMatrix4Rotate(modelViewMatrix, _rotation, 1.0f, 1.0f, 1.0f);
    modelViewMatrix = GLKMatrix4Multiply(baseModelViewMatrix, modelViewMatrix);
    
    _normalMatrix = GLKMatrix3InvertAndTranspose(GLKMatrix4GetMatrix3(modelViewMatrix), NULL);
    
    _modelViewProjectionMatrix = GLKMatrix4Multiply(projectionMatrix, modelViewMatrix);
    
    _rotation += 0.05f;
    
    draw();
}
void Render::draw(){
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArrayOES(_vertexArray);
    
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    mShader.use();
    
    glUniformMatrix4fv(cuniforms[CUNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, _modelViewProjectionMatrix.m);
    glUniformMatrix3fv(cuniforms[CUNIFORM_NORMAL_MATRIX], 1, 0, _normalMatrix.m);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Render::tearDown(){
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteVertexArraysOES(1, &_vertexArray);
   
    mShader.use();
//    if (_program) {
//        glDeleteProgram(_program);
//        _program = 0;
//    }
}
