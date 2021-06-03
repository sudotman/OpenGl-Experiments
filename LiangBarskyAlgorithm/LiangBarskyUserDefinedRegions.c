#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>


float orthoDivisor = 80;

//Rectangle Clipping Boundaries
float x_max = 200;
float x_min = -300;
float y_min = -200;
float y_max = 500;

//Region Codes
const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000
 
//Variables to help
int print = 1;

char inputting = 0;
char canDrawAnother = 1;

float wh = 600;
float ww = 600;

int temp_x1,temp_y1,temp_x2,temp_y2;


/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
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


// this function gives the maximum
float maxi(float arr[],int n) {
  float m = 0;
  for (int i = 0; i < n; ++i)
    if (m < arr[i])
      m = arr[i];
  return m;
}

// this function gives the minimum
float mini(float arr[], int n) {
  float m = 1;
  for (int i = 0; i < n; ++i)
    if (m > arr[i])
      m = arr[i];
  return m;
}

void Liang(float x1, float y1, float x2, float y2) {
  // defining variables
  float p1 = -(x2 - x1);
  float p2 = -p1;
  float p3 = -(y2 - y1);
  float p4 = -p3;

  float q1 = x1 - x_min;
  float q2 = x_max - x1;
  float q3 = y1 - y_min;
  float q4 = y_max - y1;

  float posarr[5], negarr[5];
  int posind = 1, negind = 1;
  posarr[0] = 1;
  negarr[0] = 0;

  if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0)) {
      printf("Line is parallel to clipping window! \n");
      return;
  }
  if (p1 != 0) {
    float r1 = q1 / p1;
    float r2 = q2 / p2;
    if (p1 < 0) {
      negarr[negind++] = r1; // for negative p1, add it to negative array
      posarr[posind++] = r2; // and add p2 to positive array
    } else {
      negarr[negind++] = r2;
      posarr[posind++] = r1;
    }
  }
  if (p3 != 0) {
    float r3 = q3 / p3;
    float r4 = q4 / p4;
    if (p3 < 0) {
      negarr[negind++] = r3;
      posarr[posind++] = r4;
    } else {
      negarr[negind++] = r4;
      posarr[posind++] = r3;
    }
  }

  float xn1, yn1, xn2, yn2;
  float rn1, rn2;
  rn1 = maxi(negarr, negind); // maximum of negative array
  rn2 = mini(posarr, posind); // minimum of positive array

  if (rn1 > rn2)  { // reject
    DrawLines(x1,y1,x2,y2,0);
    return;
  }

  xn1 = x1 + p2 * rn1;
  yn1 = y1 + p4 * rn1; // computing new points

  xn2 = x1 + p2 * rn2;
  yn2 = y1 + p4 * rn2;

  DrawLines(xn1, yn1, xn2, yn2, 1); // the drawing the new line
  printf("New clipped line: (%d,%d) to (%d,%d). \n", (int) xn1 ,(int) yn1,(int) xn2,(int) yn2);

  //setlinestyle(1, 1, 0);

  DrawLines(x1, y1, xn1, yn1, 0);
  DrawLines(x2, y2, xn2, yn2, 0);
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

    //glRectf(-3,1,2,6);

    DrawRectangle(x_max,y_max,x_min,y_min);

    glFlush(); // Render now

    print = 0;
}



/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    wh = height;
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();
    //    if (width >= height) {
    //      // aspect >= 1, set the height from -1 to 1, with larger width
    //       gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    //    } else {
    //       // aspect < 1, set the width to -1 to 1, with larger height
    //      gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    //    }
    gluOrtho2D(-600, 600, -600, 600);
}

void SpecialKeyHandler(int key, int x, int y)
{
   
}

void mouse(int button, int state, int x, int y)
{
    
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = (x - (ww/2)) * (ww*2) / ww;
        y = ((wh/2) - y) * (wh*2) / wh;

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
                
                Liang(temp_x1,temp_y1,temp_x2,temp_y2);
            }
        }
        

        //char things[] = {x,y};
        //output(200,200,1,1,1,things);
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitWindowSize(ww, wh);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("User Defined Clipping");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutSpecialFunc(SpecialKeyHandler);
   glutMouseFunc(mouse);
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}