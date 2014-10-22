//
//  VBOTest.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-21.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_VBOTest_h
#define TestOpenglView_VBOTest_h
#include"YFGL_Utils/glYF.h"
#include "OpenGL/gl.h"
class VBOTest{
public:
    VBOTest(){
        
        
    };
    
    void draw(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        
        //data
        GLfloat vertices[] = {
            -0.5,-0.5,0,
            -0.5,0.5,0,
            0.5,0.5,0,
            0.5,-0.5,0
        };
        GLuint indices[] = {
            0,1,3,2
        };
        //vbo
        GLuint buffers[2];
        glGenBuffers(2, buffers);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glIndexPointer(GL_UNSIGNED_INT, 0, indices);
        
        glColorPointer(3, GL_FLOAT, 0, vertices);
        
       

        
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, indices);
    }
    void base(){
        
    }
    ~VBOTest(){};
};

#endif
