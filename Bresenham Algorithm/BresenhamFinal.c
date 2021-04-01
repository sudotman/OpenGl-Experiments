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

void Bersenham(int X1, int Y1, int X2, int Y2) {

    //calculating range for line between start and end point
    int dx = X2 - X1;
    int dy = Y2 - Y1;

    int x = X1;
    int y = Y1;

    //second quadrant
    if (dx < 0 && dy >= 0)
    {
        //this is the case when slope(m) < 1
        if (abs(dx) > abs(dy))
        {
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dy)) - abs(dx);

            for (int i = 0; i < abs(dx); i++)
            {
                x = x - 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dy));
                else
                {
                    y = y + 1;
                    pk = pk + (2 * abs(dy)) - (2 * abs(dx));
                }
                setpixel(x, y);
            }
        }
        else
        {
            //this is the case when slope is greater than or equal to 1  i.e: m>=1
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dx)) - abs(dy);

            for (int i = 0; i < abs(dy); i++)
            {
                y = y + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dx));
                else
                {
                    x = x - 1;
                    pk = pk + (2 * abs(dx)) - (2 * abs(dy));
                }

                setpixel(x, y); // display pixel at coordinate (x, y)
            }
        }
    }
    else if(dx < 0 && dx < 0) //third quadrant
    {
        //this is the case when slope(m) < 1
        if (abs(dx) > abs(dy))
        {
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dy)) - abs(dx);

            for (int i = 0; i < abs(dx); i++)
            {
                x = x - 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dy));
                else
                {
                    y = y - 1;
                    pk = pk + (2 * abs(dy)) - (2 * abs(dx));
                }
                setpixel(x, y);
            }
        }
        else
        {
            //this is the case when slope is greater than or equal to 1  i.e: m>=1
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dx)) - abs(dy);

            for (int i = 0; i < abs(dy); i++)
            {
                y = y - 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dx));
                else
                {
                    x = x - 1;
                    pk = pk + (2 * abs(dx)) - (2 * abs(dy));
                }

                setpixel(x, y); // display pixel at coordinate (x, y)
            }
        }
    }
    //fourth quadrant
    else if(dx > 0 && dy < 0)
    {
        //this is the case when slope(m) < 1
        if (abs(dx) > abs(dy))
        {
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dy)) - abs(dx);

            for (int i = 0; i < abs(dx); i++)
            {
                x = x + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dy));
                else
                {
                    y = y - 1;
                    pk = pk + (2 * abs(dy)) - (2 * abs(dx));
                }
                setpixel(x, y);
            }
        }
        else
        {
            //this is the case when slope is greater than or equal to 1  i.e: m>=1
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dx)) - abs(dy);

            for (int i = 0; i < abs(dy); i++)
            {
                y = y - 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dx));
                else
                {
                    x = x + 1;
                    pk = pk + (2 * abs(dx)) - (2 * abs(dy));
                }

                setpixel(x, y); // display pixel at coordinate (x, y)
            }
        }
    }
    else
    {
        //this is the case when slope(m) < 1
        if (abs(dx) > abs(dy))
        {
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dy)) - abs(dx);

            for (int i = 0; i < abs(dx); i++)
            {
                x = x + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dy));
                else
                {
                    y = y + 1;
                    pk = pk + (2 * abs(dy)) - (2 * abs(dx));
                }
                setpixel(x, y);
            }
        }
        else
        {
            //this is the case when slope is greater than or equal to 1  i.e: m>=1
            setpixel(x, y); //this putpixel is for very first pixel of the line
            int pk = (2 * abs(dx)) - abs(dy);

            for (int i = 0; i < abs(dy); i++)
            {
                y = y + 1;
                if (pk < 0)
                    pk = pk + (2 * abs(dx));
                else
                {
                    x = x + 1;
                    pk = pk + (2 * abs(dx)) - (2 * abs(dy));
                }

                setpixel(x, y); // display pixel at coordinate (x, y)
            }
        }
    }
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

  //Draw axes
  Bersenham(-400, 0, 400, 0); //x-axis
  Bersenham(0, -400, 0, 400); //y-axis  

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