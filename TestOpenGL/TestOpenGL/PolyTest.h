//
//  PolyTest.h
//  TestOpenglView
//
//  Created by yafacex on 14-5-16.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_PolyTest_h
#define TestOpenglView_PolyTest_h

#include"glYF.h"

class PolyTest{
public:
    PolyTest(){
//        drawPoly5();
//        drawPolyEdge();
        testArray();
    };
    static int cnt ;

    void drawPoly5(){
//        glEnable(GL_LINE_STIPPLE);
//        int pattern = (1<<8) -1;
//        glLineStipple(1, pattern);

        
//        glPointSize(100);
//        glLineWidth(10);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);
        
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_LINE);
        
        glColor3f(1.0, 0.5, 1.0);
        glBegin(GL_POLYGON);
        glV12f v12;
        
        glIdentity12(&v12,1.0,-1);
        glMult12(&v12, 0.2);
        glPrintV12f(&v12);
        glVertexG3f(4,v12);
        
//        glVertex3f(-0.5, 0, -0.2);
//        glVertex3f(-0.2,0.2,-0.2);
        
        glEnd();
        
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(cnt++, 0, 1, 0);
        glPushMatrix();
    }
    
    void drawPolyEdge(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        glEdgeFlag(GL_TRUE);
        glVertex3f(-0.2, -0.2, 0);
        glEdgeFlag(GL_TRUE);
        glVertex3f(0.2, 0.2, 0);
        glEdgeFlag(GL_FALSE);
        glVertex3f(0.2, -0.2, 0);
        glEnd();
    }
    
    void testArray(){
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        //why wrong,no graphic?
//        GLint vertices[] = {
//            25,25,
//            100,325,
//            175,25,
//            175,325,
//            250,25,
//            325,325
//        };
        glV12f vertices;
        glIdentity12(&vertices, 1, -1);
        glMult12(&vertices, 0.3);
        GLfloat colors[] = {
            1,0.2,0.2,
            0.2,0.2,1.0,
            0.5,1.0,0.2,
            0.75,0.75,0.75,
            0.35,0.35,0.35,
            0.5,0.5,0.5
        };
        glColorPointer(3, GL_FLOAT
                       , 0, colors);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
//way 1=>element way
        glArrayElement(0);
        glArrayElement(1);
        glArrayElement(2);
        glArrayElement(0);
        glArrayElement(2);
        glArrayElement(3);
        
//way 2=>elements way
//        GLubyte indices0[] = {0,1,2};
//        GLubyte indices1[] = {0,2,3};
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices0);
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices1);
        
//way2-2
//        GLubyte indices[] = {0,1,2,3};
//        glDrawElements(GL_QUADS, 5, GL_UNSIGNED_BYTE, indices);
        
//way 3-multi elements
//But why replace GLvoid with GLubyte wrong??
//        GLubyte indices0[] = {0,1,2};
//        GLubyte indices1[] = {0,2,3};
//        static GLvoid *indices[] = {indices0,indices1};
//        GLsizei counts[] = {3,3};
//        glMultiDrawElements(GL_TRIANGLES, counts, GL_UNSIGNED_BYTE, indices, 2);
        
//way 4-array
//        glDrawArrays(GL_QUADS, 0, 4);

//way 4-2-array
//        GLfloat vertices2[15];
//        for (int i=0; i<12; ++i) {
//            vertices2[i] = vertices[i];
//        }
//        vertices2[12] = vertices[0];
//        vertices2[13] = vertices[1];
//        vertices2[14] = vertices[2];
//        glVertexPointer(3, GL_FLOAT, 0, vertices2);
//
//        GLint firsts[] = {0,2};
//        GLsizei sizes[] = {3,3};
//        glMultiDrawArrays(GL_TRIANGLES, firsts, sizes, 2);
    }
    
};

int PolyTest::cnt = 0;

#endif
