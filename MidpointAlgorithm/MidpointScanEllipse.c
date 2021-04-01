#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float a, b, c, d;
char inputting = 0;
int semi_major;
int semi_minor;
char canDrawAnother = 1;
int Ox,Oy,Ax,Ay, Bx, By;

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


void BresenhamEllipse(int major_r, int minor_r, int xc, int yc)
{
    //printf("Center_x: %d, Center_y: %d, Semi_major: %ld, Semi_minor: %ld \n",h,k,a,b);
    float dx, dy, d1, d2, x, y; 
    x = 0; 
    y = minor_r; 
  
    // Initial decision parameter of region 1 
    d1 = (minor_r * minor_r) 
         - (major_r * major_r * minor_r) 
         + (0.25 * major_r * major_r); 
    dx = 2 * minor_r * minor_r * x; 
    dy = 2 * major_r * major_r * y; 
  
    // For region 1 
    while (dx < dy) { 
  
        // Print points based on 4-way symmetry 
        setpixel( x + xc, y + yc); 
        setpixel( -x + xc, y + yc); 
        setpixel(x + xc, -y + yc); 
        setpixel( -x + xc, -y + yc); 
  
        // Checking and updating value of 
        // decision parameter based on algorithm 
        if (d1 < 0) { 
            x++; 
            dx = dx + (2 * minor_r * minor_r); 
            d1 = d1 + dx + (minor_r * minor_r); 
        } 
        else { 
            x++; 
            y--; 
            dx = dx + (2 * minor_r * minor_r); 
            dy = dy - (2 * major_r * major_r); 
            d1 = d1 + dx - dy + (minor_r * minor_r); 
        } 
    } 
  
    // Decision parameter of region 2 
    d2 = ((minor_r * minor_r) * ((x + 0.5) * (x + 0.5))) 
         + ((major_r * major_r) * ((y - 1) * (y - 1))) 
         - (major_r * major_r * minor_r * minor_r); 
  
    // Plotting points of region 2 
    while (y >= 0) { 
  
        // printing points based on 4-way symmetry 
        setpixel( x + xc, y + yc); 
        setpixel( -x + xc, y + yc); 
        setpixel(x + xc, -y + yc); 
        setpixel(-x + xc, -y + yc); 
  
        // Checking and updating parameter 
        // value based on algorithm 
        if (d2 > 0) { 
            y--; 
            dy = dy - (2 * major_r * major_r); 
            d2 = d2 + (major_r * major_r) - dy; 
        } 
        else { 
            y--; 
            x++; 
            dx = dx + (2 * minor_r * minor_r); 
            dy = dy - (2 * major_r * major_r); 
            d2 = d2 + dx - dy + (major_r * major_r); 
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

void callBresenham(){
    BresenhamLine(Ox,Oy,Ax,Ay);
    BresenhamLine(Ox,Oy,Bx,By);
    semi_major = sqrt( pow((Ax - Ox), 2) + pow((Ay - Oy), 2) ); 
    semi_minor = sqrt( pow((Bx - Ox), 2) + pow((By - Oy), 2) ); 
    BresenhamEllipse(semi_major, semi_minor, Ox, Oy);
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
                Ax = x;
                Ay = y;
            }
            else if(inputting == 1){
                inputting = 2;
                Bx = x;
                By = y;
            }
            else if(inputting == 2){
                inputting = 0;
                Ox = x;
                Oy = y;
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
    //BresenhamEllipse(319,239,50,40);
}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27)
		exit(0);
    else if(key=='t'){
        BresenhamEllipse(319,239,50,40);
    }
   
}

void SpecialKeyHandler (int key, int x, int y)
{
    
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(400, 400);
  
  glutCreateWindow("Scan converting Ellipse");
  init();
  glutMouseFunc(mouse);
  glutDisplayFunc(drawMyLine);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(SpecialKeyHandler);
  glutReshapeFunc(resize);
  glutMainLoop();
  
  return 0;
}