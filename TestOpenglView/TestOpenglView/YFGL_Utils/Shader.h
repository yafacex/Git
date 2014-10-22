//
//  Shader.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-26.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_Shader_h
#define TestOpenglView_Shader_h
#include"OpenGL/gl3.h"
#include <assert.h>
class Shader{
public:
    enum ShaderType{VertexShader,FragShader};
    Shader():vertexSource(NULL),fragSource(NULL){};
    ~Shader(){
        if (vertexSource) {
            delete vertexSource;
        }
        if (fragSource) {
            delete fragSource;
        }
    };
    
    void genShader(){
        
        vertexShader = initVertexShader();
        fragShader = initFragmentShader();
        
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);
        
        GLint bLinked;
        checkStatus(program);
//        glGetProgramiv(program, GL_LINK_STATUS, &bLinked);
//        
//        if (bLinked) {
//            glUseProgram(program);
//        }else{
//            checkStatus(program);
//        }
    }
    
    GLuint initVertexShader(){
        readFromFile("/Users/yafacex/Documents/LUA/Cpp/TestOpenglView/TestOpenglView/vert.vsh", vertexSource, 300);
        printf("%s\n",vertexSource);
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
//        freeBuffer(vertexSource);
        
        checkStatus(vertexShader);
        return vertexShader;
    }
    
    GLuint initFragmentShader(){
        readFromFile("/Users/yafacex/Documents/LUA/Cpp/TestOpenglView/TestOpenglView/frag.fsh", fragSource, 300);
            
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragSource, NULL);
        glCompileShader(fragShader);
        freeBuffer(fragSource);
        
        checkStatus(fragShader);
        return fragShader;
    }
    
    void readFromFile(const char* file,char *&buffer,int length){
        buffer = (GLchar*)malloc(sizeof(GLchar*)*length);
        FILE* fp = fopen(file, "r");
        if (fp) {
            size_t len = 0;
            while (NULL!=fgets((char*)(buffer+len), 100, fp)){
                len = strlen(buffer);
            };
        }
    }
    
    void checkStatus(GLuint shader){
        GLint bComplied;
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
    }
    
    void freeBuffer(char* &buffer){
        if (buffer) {
            delete buffer;
            buffer = NULL;
        }
    };
    
    GLint getAttribLocation(ShaderType type,const GLchar* name){
        switch (type) {
            case FragShader:
                return glGetAttribLocation(fragShader, name);
                break;
            case VertexShader:
                return glGetAttribLocation(vertexShader, name);
                break;
            default:
                assert(false);
                break;
        }
    }
    
    void use(){
        glUseProgram(program);
    }
    
    char* vertexSource;
    char* fragSource;
    
    GLuint vertexShader;
    GLuint fragShader;
    GLuint program;
    
};

#endif
