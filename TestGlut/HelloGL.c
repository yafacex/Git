#include <stdlib.h>  
#include "GL/gl.h"  
#include "GL/glut.h"  
#include <stdio.h>
void display(void)  
{  

   glClear (GL_COLOR_BUFFER_BIT);/* clear all pixels  */  
    // glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
   glColor3f (1.0, 1.0, 1.0);  
   glBegin(GL_POLYGON);/* draw white polygon with corners at(0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)*/  
      glVertex3f (0.25, 0.25, 0.0);  
      glVertex3f (0.75, 0.25, 0.0);  
      glVertex3f (0.75, 0.75, 0.0);  
      glVertex3f (0.25, 0.75, 0.0);  
   glEnd();  
    glFlush ();/* start processing buffered OpenGL routines  */  
    glutSwapBuffers();
    printf("haha\n");
}  
void init (void)  
{  
   glClearColor (0.0, 1.0, 0.0, 0.0);/* select clearing color  */  
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();  
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);/* initialize viewing values  */  
}  

void idle(void)
{
    display();
}
int main(int argc, char** argv)  
{  
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);/*Declare initial display mode(single buffer and RGBA).*/  
   glutInitWindowSize (400, 400); /*Declare initial window size.*/  
   glutInitWindowPosition (100, 100);/*Declare initial window position.*/  
   glutCreateWindow ("hello");/*Open window with "hello"in its title bar.*/  
   init ();//Call initialization routines.  
   glutDisplayFunc(&display); /*Register callback function to display graphics.*/  
   glutIdleFunc(idle);
   glutMainLoop();/*Enter main loop and process events.*/  
   return 0;   /* ANSI C requires main to return int. */  
}