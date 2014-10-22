//
//  main.cpp
//  TestOpenGL
//
//  Created by yafacex on 14-2-24.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include <iostream>
#include "OpenGl/gl3.h"
#include <GLUT/glut.h>
//#include "GLUT/glut.h"
#include "MyOpenglView.h"
#include "VBOTest.h"
#include "TerrianTest.h"
static GLfloat spin = 0;
void renderScene(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

//    VBOTest vbo;
    TerrianTest ter;
    
    glutSwapBuffers();
//    glSwapAPPLE();
    printf("%f\n",spin);
}

void reshape(int w,int h){
}

void spinDisplay(){
    spin += 2;
    if (spin>360) {
        spin-=360;
    }
    glutPostRedisplay();
    
}
void init(){
    glClearColor(0, 0, 0, 0);
}
void mouse(int button,int state,int x,int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glutIdleFunc(spinDisplay);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                glutIdleFunc(NULL);
            }
        default:
            break;
    }
}

void testGlutView(int argc, char * argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("cao");
    init();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
}
int main(int argc, char * argv[])
{
    testGlutView(argc, argv);
    return 0;
}

