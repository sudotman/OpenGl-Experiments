#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>


float orthoDivisor = 80;

//Rectangle Clipping Boundaries
float x_max = 2;
float x_min = -3;
float y_min = 1;
float y_max = 6;

//Region Codes
const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000
 
int print = 1;

/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

int CalculateRegionCode(int x, int y)
{
    // We initialize as it being inside to begin with
    int code = INSIDE;
  
    if (x < x_min) // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min) // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;
  
    return code;
}

void DrawLines(int x1, int y1, int x2, int y2, int i){
    
    glBegin(GL_LINES); 
        if(i == 0)
            glColor3f(1.0f, 0.0f, 0.0f);          //red
        else if(i == 1)
            glColor3f(0.0f, 1.0f, 0.0f);            //green
        else if(i == 2)
            glColor3f(1.0f, 1.0f, 1.0f);            //default white
        else
            glColor3f(1.0f, 0.0f, 0.0f);

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    glFlush();
    
}

int Cohen(int x1, int y1, int x2, int y2){
    int temp_x1 = x1;
    int temp_x2 = x2;
    int temp_y1 = y1;
    int temp_y2 = y2;

    int code1 = CalculateRegionCode(x1,y1);
    int code2 = CalculateRegionCode(x2,y2);

    int accept = 0;
    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            //Inside
            DrawLines(x1, y1, x2, y2, 1);
            accept = 1;
            break;
        }
        else if ((code1 & code2) != 0)
        {
            //same region
            DrawLines(x1, y1, x2, y2, 0);
            break;
        }
        else
        {
            int code_out;
            int x, y;

            if (code1 != 0)
            {
                code_out = code1;
            }
            else if (code2 != 0)
            {
                code_out = code2;
            }
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;

            }
            else if (code_out & RIGHT)
            {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
  
            }
            else if (code_out & LEFT)
            {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;

            }


            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = CalculateRegionCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = CalculateRegionCode(x2, y2);
            }
        }
    }

    if(accept == 1){
        if(print == 1)
        printf("New clipped line: (%d,%d) to (%d,%d). \n", x1 , y1, x2, y2);
        
        DrawLines(temp_x1,temp_y1,temp_x2,temp_y2,0);
        DrawLines(x1,y1,x2,y2,1);
    }
    else{
        if(print == 1)
        printf("Completely outside the region. \n");
    }

    return 1;
}

void DrawRectangle(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINE_LOOP);       // Each set of 3 vertices form a triangle
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    
    glVertex2f(x1, y1);

    glVertex2f(x2, y1);

    glVertex2f(x2, y2);

    glVertex2f(x1, y2);
    glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);   // To operate on Model-View matrix
    glLoadIdentity();             // Reset the model-view matrix

    DrawLines(-14,0,14,0,2);
    DrawLines(0,-10,0,10,2);
    Cohen(-4, 2, 1, 7);
    //Cohen(-1, 5, 3, 8);
    Cohen(-2, 3, 1, 2);
    Cohen(1, -2, 3, 3);
    Cohen(-4, 7, -2, 10);
    //Cohen(-1, 0, -1, 8);
    Cohen(-5, 3, 4, 3);
    //Cohen(-5,7,4,-1);

    //glRectf(-3,1,2,6);

    DrawRectangle(x_max,y_max,x_min,y_min);

    glFlush(); // Render now

    print = 0;
}



/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1
   ;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
//    if (width >= height) {
//      // aspect >= 1, set the height from -1 to 1, with larger width
//       gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
//    } else {
//       // aspect < 1, set the width to -1 to 1, with larger height
//      gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
//    }
    gluOrtho2D(-width/orthoDivisor,width/orthoDivisor, -height/orthoDivisor ,height/orthoDivisor );
}

void SpecialKeyHandler(int key, int x, int y)
{
   
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitWindowSize(900, 750);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Cohen Clipping");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutSpecialFunc(SpecialKeyHandler);
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}