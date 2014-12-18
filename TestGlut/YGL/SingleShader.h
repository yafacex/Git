//
//  SingleShader.h
//
//  Created by yafacex on 14-5-26.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef YafaceX_SingleShader_h
#define YafaceX_SingleShader_h
#include <assert.h>
class SingleShader{
public:
    enum ShaderType{VertexShader,FragShader};
    SingleShader():vertexSource(NULL),fragSource(NULL){};
    ~SingleShader(){
        if (vertexSource) {
            delete vertexSource;
        }
        if (fragSource) {
            delete fragSource;
        }
    };
    void genShader(const char* vertFile,const char* fragFile){
        
        vertexShader = initVertexShader(vertFile);
        fragShader = initFragmentShader(fragFile);
        
        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragShader);
    }
    
    void compile(){
        glCompileShader(vertexShader);
        checkStatus(vertexShader);
        glCompileShader(fragShader);
        checkStatus(fragShader);
    }
    void link(){
        glLinkProgram(program);
         GLint bLinked;
        checkStatus(program);
        glGetProgramiv(program, GL_LINK_STATUS, &bLinked);
        
        if (!bLinked) {
            printf("shader link failed!\n");
            assert(false);
        }
    }
    
    GLuint initVertexShader(const char* file){
        readFromFile(file, vertexSource, 300);
        printf("%s\n",vertexSource);
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        freeBuffer(vertexSource);
        
        return vertexShader;
    }
    
    GLuint initFragmentShader(const char* file){
        readFromFile(file, fragSource, 300);
            
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, (const char**)&fragSource, NULL);
        freeBuffer(fragSource);
        
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
    
    void validate(){
        glValidateProgram(program);
    }
    
    void deleteSelf(){
        glDeleteProgram(program);
    }
    char* vertexSource;
    char* fragSource;
    
    GLuint vertexShader;
    GLuint fragShader;
    GLuint program;
};

#endif