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
class VBOTest{
public:
    VBOTest(){
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
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glIndexPointer(GL_UNSIGNED_INT, 0, NULL);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, NULL);
        
    };
    void base(){
        
    }
    ~VBOTest(){};
};

#endif
