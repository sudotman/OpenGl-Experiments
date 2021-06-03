// INFO:
// Left top right bottom

#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class point {
  public:
    float x;
    float y;
  
  point(float x, float y){
    this->x = x;
    this->y = y;
  }

  string display(){
    string temp = to_string(x) + "," + to_string(y);
    return temp;
  }
};

char situation = 0;

// 1. First is outside, second is inside. hence coming in the clipping area.: Second is in output, and then intersection
// 2. First is inside, second is outside. only the edge intersection is added
// 3. Both inside, then second is added.
// 4. Both outside, discard both.

vector<point> points;
vector<point> output;

float orthoDivisor = 80;

//Rectangle Clipping Boundaries
float x_max = 4;
float y_max = 4;
float x_min = 0;
float y_min = 0;

int print = 1;

/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

void AddPoint(int x, int y){
  points.push_back(point (x,y));
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

void DrawPolygon(vector<point> polygonPoints, int color){
  glBegin(GL_LINE_LOOP);

  if(color == 1){
    glColor3f(0.0f, 1.0f, 0.0f);
  }
  else{
    glColor3f(1.0f, 0.0f, 0.0f);
  }
  for(int i = 0; i < polygonPoints.size(); i++){
    glVertex2f(polygonPoints.at(i).x, polygonPoints.at(i).y);
  }

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

    
    DrawPolygon(points, 0);
  

    DrawRectangle(x_min,y_min, x_max,y_max);

    DrawPolygon(output, 1);

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
  
const int MAX_POINTS = 20;
  
// Returns x-value of point of intersectipn of two
// lines
float x_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4)
{
    float num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}
  
// Returns y-value of point of intersectipn of
// two lines
float y_intersect(int x1, int y1, int x2, int y2,
                int x3, int y3, int x4, int y4)
{
    float num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    float den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}
  
// This functions clips all the edges w.r.t one clip
// edge of clipping area
void clip(float poly_points[][2], int &poly_size,
          float x1, float y1, float x2, float y2)
{
    float new_points[MAX_POINTS][2], new_poly_size = 0;
  
    // (ix,iy),(kx,ky) are the co-ordinate values of
    // the points
    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon
        int k = (i+1) % poly_size;
        float ix = poly_points[i][0], iy = poly_points[i][1];
        float kx = poly_points[k][0], ky = poly_points[k][1];
  
        // Calculating position of first point
        // w.r.t. clipper line
        float i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
  
        // Calculating position of second point
        // w.r.t. clipper line
        float k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);
  
        // Case 1 : When both points are inside
        if (i_pos < 0  && k_pos < 0)
        {
            //Only second point is added
            new_points[(int) new_poly_size][0] = kx;
            new_points[(int) new_poly_size][1] = ky;
            new_poly_size++;
        }
  
        // Case 2: When only first point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            // Point of intersection with edge
            // and the second point is added
            new_points[(int) new_poly_size][0] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[(int) new_poly_size][1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
  
            new_points[(int) new_poly_size][0] = kx;
            new_points[(int) new_poly_size][1] = ky;
            new_poly_size++;
        }
  
        // Case 3: When only second point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            //Only point of intersection with edge is added
            new_points[(int) new_poly_size][0] = x_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_points[(int) new_poly_size][1] = y_intersect(x1,
                              y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
  
        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }
  
    // Copying new points into original array
    // and changing the no. of vertices
    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++)
    {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}
  
// Implements Sutherland–Hodgman algorithm
void suthHodgClip(float poly_points[][2], int poly_size,
                  float clipper_points[][2], float clipper_size)
{
    //i and k are two consecutive indexes
    for (int i=0; i<clipper_size; i++)
    {
        int k = (i+1) % (int) clipper_size;
  
        // We pass the current array of vertices, it's size
        // and the end points of the selected clipper line
        clip(poly_points, poly_size, clipper_points[i][0],
             clipper_points[i][1], clipper_points[k][0],
             clipper_points[k][1]);
    }
  
    // Printing vertices of clipped polygon
    for (int i=0; i < poly_size; i++)
        cout << '(' << poly_points[i][0] << ", " << poly_points[i][1] << ") " << endl;
}
  
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitWindowSize(900, 750);   // Set the window's initial width & height - non-square
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Sutherland Clipping");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   glutSpecialFunc(SpecialKeyHandler);

// Defining polygon vertices in clockwise order
    float poly_size = 8;
    float poly_points[20][2] = {{1,-1}, {1,2}, {-1,2}, {-1,5}, {1,3}, {1,6}, {-2,6}, {-2,-1}};
  
    // Defining clipper polygon vertices in clockwise order
    float clipper_size = 4;
    float clipper_points[][2] = {{0,0},{0,4},{4,4},{4,0}};
  
    for(int i = 0;i<poly_size;i++){
      points.push_back(point(poly_points[i][0],poly_points[i][1]));
    }

    //Calling the clipping function
    suthHodgClip(poly_points, poly_size, clipper_points,
                 clipper_size);

    for(int i = 0;i<poly_size;i++){
      output.push_back(point(poly_points[i][0],poly_points[i][1]));
    }


   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}



