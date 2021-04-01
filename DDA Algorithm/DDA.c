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

void DDA(int x1, int y1, int x2, int y2) {

  int steps; //The number of steps to be taken
  int dx, dy; //The delta of initial and final points
  float x, y, x_inc, y_inc; //Variables for increments, and setting the pixels

  int i; //Will help with a loop / and the number of points drawn

  //Getting the delta
  dx = x2 - x1;
  dy = y2 - y1;

  //Do we need to travel more to x or y?
  steps = abs(dx) > abs(dy) ?  abs(dx) : abs(dy);

  //Calculate what the increment would be for each step
  x_inc = dx / (float) steps;
  y_inc = dy / (float) steps;

  //Start our line drawing from our first co-ordinates
  x = x1;
  y = y1;
  for (i = 0; i <= steps; i++) {
    setpixel((round(x)), (round(y)));
    x = x + x_inc;
    y = y + y_inc;
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

  //Draw axes
  DDA(-400, 0, 400, 0); //x-axis
  DDA(0, -400, 0, 400); //y-axis
  output(200,200,1,1,1,"Quadrant 1");
  output(-200,200,1,1,1,"Quadrant 2");
  output(-200,-200,1,1,1,"Quadrant 3");
  output(200,-200,1,1,1,"Quadrant 4");

  //Enter predefined points here if any
  DDA(-10,-70,90,-50);
  DDA(-70,-10,-50,90);
  DDA(-10,70,90,50);
  DDA(70,-10,50,90);
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
  glutCreateWindow("DDA Part 1");
  init();
  glutDisplayFunc(drawMyLine);
  glutMainLoop();
  return 0;
}