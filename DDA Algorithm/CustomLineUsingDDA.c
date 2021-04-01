#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float a, b, c, d;
char inputting = 0;
char canDrawAnother = 1;
int temp_x1,temp_y1,temp_x2,temp_y2;

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
  //DDA(-400, 0, 400, 0); //x-axis
  //DDA(0, -400, 0, 400); //y-axis
  //output(200,200,1,1,1,"Quadrant 1");
  //output(-200,200,1,1,1,"Quadrant 2");
  //output(-200,-200,1,1,1,"Quadrant 3");
  //output(200,-200,1,1,1,"Quadrant 4");

  //Enter predefined points here if any
  

}

void mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = (x - 200) * 800.0 / 400;
        y = (200 - y) * 800.0 / 400;
        printf("%d,%d \n",x,y);
        
        if(canDrawAnother){
            if(inputting == 0){
                inputting = 1;
                temp_x1 = x;
                temp_y1 = y;
            }
            else if(inputting == 1){
                inputting = 0;
                temp_x2 = x;
                temp_y2 = y;
                printf("x1: %d,x2: %d,x3: %d, x4: %d \n",temp_x1,temp_x2,temp_y1,temp_y2);
                DDA(temp_x1,temp_y1,temp_x2,temp_y2);
            }
        }
        

        //printf("%d,%d \n",glutGet(GLUT_SCREEN_HEIGHT),glutGet(GLUT_SCREEN_HEIGHT));
        //char things[] = {x,y};
        //output(200,200,1,1,1,things);
    }
}


void init(void) {

  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
}

void resize(int width, int height){
    glutReshapeWindow(400,400);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(400, 400);
  
  glutCreateWindow("Drawing lines using DDA");
  init();
  glutMouseFunc(mouse);
  glutDisplayFunc(drawMyLine);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}