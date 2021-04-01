#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float a, b, c, d;

void setpixel(GLint xCoordinate, GLint yCoordinate) {
  glBegin(GL_POINTS);
  glVertex2i(xCoordinate, yCoordinate);
  glEnd();
  glFlush();
}

void Bersenham(int x1, int y1, int x2, int y2) {

   int dx, dy, p, x, y;  
    dx=x2-x1;  
    dy=y2-y1;  
    x=x1;  
    y=y1;  
    p=2*dy-dx;  
    while(x<x2)  
    {  
        if(p>=0)  
        {  
            setpixel(x,y);  
            y=y+1;  
            p=p+2*dy-2*dx;  
        }  
        else  
        {  
            setpixel(x,y);  
            p=p+2*dy;}  
            x=x+1;  
        }  
  //printf("Line drawn.");
  //printf("The number of points drawn: %d", (i+1));
}

void output(int x, int y, float r, float g, float b, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
  }
}

void drawMyLine() { 
  output(200,200,1,1,1,"Quadrant 1");
  output(-200,200,1,1,1,"Quadrant 2");
  output(-200,-200,1,1,1,"Quadrant 3");
  output(200,-200,1,1,1,"Quadrant 4");

  //Enter predefined points here if any
  Bersenham(-10,-70,90,-50);
  Bersenham(-70,-10,-50,90);
  Bersenham(-10,70,90,50);
  Bersenham(70,-10,50,90);
}

void init(void) {

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(400, 400);
  glutCreateWindow("Bersenham Part 1");
  init();
  glutDisplayFunc(drawMyLine);
  glutMainLoop();
  return 0;
}