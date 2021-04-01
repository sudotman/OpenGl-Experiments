#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float a, b, c, d;
char inputting = 0;
int radius;
char canDrawAnother = 1;
int temp_x1,temp_y1,temp_x2,temp_y2;

void setpixel(GLint xCoordinate, GLint yCoordinate) {
  glBegin(GL_POINTS);
  glVertex2i(xCoordinate, yCoordinate);
  glEnd();
  glFlush();
}

void BresenhamLine(int X1, int Y1, int X2, int Y2) {

    
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
        else //first quadrant
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

void drawCircle(int xc, int yc, int x, int y)
{
    setpixel(xc+x, yc+y);
    setpixel(xc-x, yc+y);
    setpixel(xc+x, yc-y);
    setpixel(xc-x, yc-y);
    setpixel(xc+y, yc+x);
    setpixel(xc-y, yc+x);
    setpixel(xc+y, yc-x);
    setpixel(xc-y, yc-x);
}

void BresenhamCircle(int xc, int yc, int r){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
         
        x++;
 
        // check for decision parameter
        // and correspondingly 
        // update d, x, y
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
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

void callBresenham(){
    BresenhamLine(temp_x1,temp_y1,temp_x2,temp_y2);
    radius = sqrt( pow((temp_x2 - temp_x1), 2) + pow((temp_y2 - temp_y1), 2) ); 
    BresenhamCircle(temp_x1,temp_y1,radius);
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
                callBresenham();
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

void drawMyLine(){

}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27)
		exit(0);
    else if(key == 'w'){
        printf("Conentric +1 \n");
        temp_x2 += 10;
        temp_y2 += 10;
        callBresenham();
    }
    else if(key == 's'){
        printf("Conentric -1 \n");
        temp_x2 -= 10;
        temp_y2 -= 10;
        callBresenham();
    }
}

void SpecialKeyHandler (int key, int x, int y)
{
    if (key==GLUT_KEY_UP) {
		printf("Size Increased \n");
        temp_x2 += 15;
        temp_y2 += 15;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        callBresenham();
    }
    else if(key == GLUT_KEY_DOWN){
        printf("Size Decreased \n");
        temp_x2 -= 15;
        temp_y2 -= 15;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        callBresenham();
    }  
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(400, 400);
  
  glutCreateWindow("Scan converting Circle");
  init();
  glutMouseFunc(mouse);
  glutDisplayFunc(drawMyLine);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(SpecialKeyHandler);
  glutReshapeFunc(resize);
  glutMainLoop();
  return 0;
}