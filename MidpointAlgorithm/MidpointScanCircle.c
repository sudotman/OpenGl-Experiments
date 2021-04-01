#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float a, b, c, d;
char inputting = 0;
char canDrawAnother = 1;
int temp_x1, temp_y1, temp_x2, temp_y2;

void setpixel(GLint xCoordinate, GLint yCoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xCoordinate, yCoordinate);
    glEnd();
    glFlush();
}

void MidpointLine(int X1, int Y1, int X2, int Y2)
{

    // calculate dx & dy

    int dx = X2 - X1;
    int dy = Y2 - Y1;

    if (dy <= dx)
    {
        // initial value of decision parameter d
        int d = dy - (dx / 2);
        int x = X1, y = Y1;

        // Plot initial given point
        // putpixel(x,y) can be used to print pixel
        // of line in graphics
        setpixel(x, y);
        // iterate through value of X
        while (x < X2)
        {
            x++;

            // E or East is chosen
            if (d < 0)
                d = d + dy;

            // NE or North East is chosen
            else
            {
                d += (dy - dx);
                y++;
            }

            // Plot intermediate points
            // putpixel(x,y) is used to print pixel
            // of line in graphics
            setpixel(x, y);
        }
    }

    else if (dx < dy)
    {
        // initial value of decision parameter d
        int d = dx - (dy / 2);
        int x = X1, y = Y1;

        // Plot initial given point
        // putpixel(x,y) can be used to print pixel
        // of line in graphics
        setpixel(x, y);

        // iterate through value of X
        while (y < Y2)
        {
            y++;

            // E or East is chosen
            if (d < 0)
                d = d + dx;

            // NE or North East is chosen
            // NE or North East is chosen
            else
            {
                d += (dx - dy);
                x++;
            }

            // Plot intermediate points
            // putpixel(x,y) is used to print pixel
            // of line in graphics
            setpixel(x, y);
        }
    }
}

void drawCircle(int xc, int yc, int x, int y)
{
    setpixel(xc + x, yc + y);
    setpixel(xc - x, yc + y);
    setpixel(xc + x, yc - y);
    setpixel(xc - x, yc - y);
    setpixel(xc + y, yc + x);
    setpixel(xc - y, yc + x);
    setpixel(xc + y, yc - x);
    setpixel(xc - y, yc - x);
}

void MidpointCircle(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        setpixel(x0 + x, y0 + y);
        setpixel(x0 + y, y0 + x);
        setpixel(x0 - y, y0 + x);
        setpixel(x0 - x, y0 + y);
        setpixel(x0 - x, y0 - y);
        setpixel(x0 - y, y0 - x);
        setpixel(x0 + y, y0 - x);
        setpixel(x0 + x, y0 - y);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void output(int x, int y, float r, float g, float b, char *string)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
    }
}

void drawMyLine()
{
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
        printf("%d,%d \n", x, y);

        if (canDrawAnother)
        {
            if (inputting == 0)
            {
                inputting = 1;
                temp_x1 = x;
                temp_y1 = y;
            }
            else if (inputting == 1)
            {
                inputting = 0;
                temp_x2 = x;
                temp_y2 = y;
                printf("x1: %d,x2: %d,x3: %d, x4: %d \n", temp_x1, temp_x2, temp_y1, temp_y2);
                MidpointLine(temp_x1, temp_y1, temp_x2, temp_y2);
                int radius = sqrt(pow((temp_x2 - temp_x1), 2) + pow((temp_y2 - temp_y1), 2));
                MidpointCircle(temp_x1, temp_y1, radius);
            }
        }

        //printf("%d,%d \n",glutGet(GLUT_SCREEN_HEIGHT),glutGet(GLUT_SCREEN_HEIGHT));
        //char things[] = {x,y};
        //output(200,200,1,1,1,things);
    }
}

void init(void)
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
}

void resize(int width, int height)
{
    glutReshapeWindow(400, 400);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(400, 400);

    glutCreateWindow("Scan converting Circle");
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(drawMyLine);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}