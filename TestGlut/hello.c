#include <stdlib.h>  
#include "GL/gl.h"  
#include "GL/glut.h"  
#include <stdio.h>
void display(void)  
{  

   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);  
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);  
      glVertex3f (0.75, 0.25, 0.0);  
      glVertex3f (0.75, 0.75, 0.0);  
      glVertex3f (0.25, 0.75, 0.0);  
   glEnd();  
    glFlush ();
    glutSwapBuffers();
}  
void initOrtho (void)  
{  
   glClearColor (0.0, 1.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity();  
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
} 
void initTxt(){
  
}

void idle(void)
{
    display();
}
int main(int argc, char** argv)  
{  
   glutInit(&argc, argv);  
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello");
   // initOrtho();
   initTxt();
   glutDisplayFunc(&display); 
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;  
}