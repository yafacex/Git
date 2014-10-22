//
//  QuadTest.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-16.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_QuadTest_h
#define TestOpenglView_QuadTest_h

#include"YFGL_Utils/glYF.h"

class QuadTest{
public:
    QuadTest(){
        glColor3f(1.0, 0.5, 1.0);
        glBegin(GL_POLYGON);
        glV12f v12;
        glIdentity12(&v12,1.0,-1.0);
        glMult12(&v12, 0.5);
        glPrintV12f(&v12);
        glVertexG3f(4,v12);
        glEnd();
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glRotated(mRotate, 0.0, 0.0, 1.0);
        glPushMatrix();
        
        glV16f mv;
        glGetFloatv(GL_MODELVIEW, mv);
        glPrintV16f(&mv);
    };
};

#endif
