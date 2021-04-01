#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int dark = 0;
float dark_x;
float dark_y;
float dark_z;

float sun_x;
float sun_y;
float sun_z;

int randomize = 0;


float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14f;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14f;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void Display()
{
    
    glClearColor(dark_x, dark_y, dark_z, 0.9462f);
     glLineWidth(2.0f);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(0.3f, 0.6f, 0.4f); //the brown color sir asked us to
     
        glBegin(GL_TRIANGLE_STRIP);
           
        if(randomize == 1){
            glColor3f(float_rand(0,1), float_rand(0,1), float_rand(0,1)); // make this vertex greenish
            glVertex2f(0.0f, 0.75f); // top of the roof

            glColor3f(float_rand(0,1), float_rand(0,1), float_rand(0,1));
            glVertex2f(-0.5f, 0.25f); // left corner of the roof

            glColor3f(float_rand(0,1), float_rand(0,1), float_rand(0,1));
            glVertex2f(0.5f, 0.25f); // right corner of the roof

            glColor3f(float_rand(0,1), float_rand(0,1), float_rand(0,1));
            glVertex2f(-0.5f, -0.5f); // bottom left corner of the house

            glVertex2f(0.5f, -0.5f); //bottom right corner of the house
        }
        else{
            glColor3f(0.6f, 0.6f, 0.4f); // make this vertex greenish
            glVertex2f(0.0f, 0.75f); // top of the roof

            glColor3f(0.6f, 0.6f, 0.4f);
            glVertex2f(-0.5f, 0.25f); // left corner of the roof

            glColor3f(0.6f, 0.6f, 0.4f);
            glVertex2f(0.5f, 0.25f); // right corner of the roof

            glColor3f(0.3f, 0.6f, 0.4f);
            glVertex2f(-0.5f, -0.5f); // bottom left corner of the house

            glVertex2f(0.5f, -0.5f); //bottom right corner of the house
        }
            
        glEnd();

        //the seperator line
        glLineWidth(2.0f);
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_LINES);
            glVertex3f(-15, -0.5, 0.0);
            glVertex3f(15, -0.5, 0);
        glEnd();

        glColor3f(0.699f, 1.0f, 0.57f); //black rectangle
        glRectf(-15,-0.5, 15, -3); //rectangle


        //HOUSE !! HOUSE !! HOUSE!!
        //the left door line
        glLineWidth(2.5f);
        glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_LINES);
            glVertex3f(-0.1, -0.5, 0.0);
            glVertex3f(-0.1, 0, 0);
            //righ door line
            glVertex3f(0.1, -0.5, 0.0);
            glVertex3f(0.1, 0, 0);
            //door connector
            glVertex3f(-0.1, 0, 0.0);
            glVertex3f(0.1, 0, 0);
            //roof divider
            glVertex3f(-0.5, 0.25, 0.0);
            glVertex3f(0.5, 0.25, 0);
            //left face roof
            glVertex3f(-0.5, 0.25, 0.0);
            glVertex3f(0.0, 0.75,0.0);
            //right face roof
            glVertex3f(0.5, 0.25, 0);
            glVertex3f(0.0, 0.75,0.0);
            //left side
            glVertex3f(-0.5, 0.25, 0.0);
            glVertex3f(-0.5, -0.5, 0.0);
            //right side
            glVertex3f(0.5, 0.25, 0.0);
            glVertex3f(0.5, -0.5, 0.0);
            //chimney
            
        glEnd();  

        glLineWidth(10);
         //black rectangle
        glBegin(GL_LINE_STRIP);
            glColor3f(0.4f, 0.4f, 0.8f);
            glVertex3f(0.3, 0.4, 0);
            glColor3f(0.8f, 0.4f, 0.0f);
            glVertex3f(0.3, 0.8, 0);
        glEnd();

        //sun
        glColor3f(0.8f, 0.4f, 0.0f);
        drawHollowCircle(0.65f,0.5f,0.1);
        glColor3f(sun_x, sun_y, sun_z);
        drawFilledCircle(0.65f,0.5f,0.1);
        glColor3f(0.0f,0.0f,0.0f);
        
    glutSwapBuffers();
}

void Darken(){
    if(dark==0){
        
        dark_x = 0.1242f; 
        dark_y = 0.1197f; 
        dark_z = 0.21f;
        
        sun_x = 0.4f;
        sun_y = 0.4f;
        sun_z = 0.4f;

        dark = 1;

        glutPostRedisplay();
    }
    else{
        dark = 0;

        dark_x = 0.83f;
        dark_y = 1.0f;
        dark_z = 0.8543f;

        sun_x = 1.0f;
        sun_y = 0.9115f;
        sun_z = 0.41f;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("\n %d,%d",x,y);
        if(x>=618 && x <=702){
            if(y>=116 && y<=184){
                Darken();
                printf("inside sun");
            }
        }
    }
}




void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27)
		exit(0);
    else if (key=='r') {
		printf("\n here");
        if(randomize ==0 ){
            randomize = 1;
            glutPostRedisplay();
        }
        else{
            
            glutPostRedisplay();
        }
        

	}
    else if(key=='t'){
        randomize = 0;
        glutPostRedisplay();
    }

}



float RGB(float x){
    return x/255;
}

void Setup()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
int main(int argc, char** argv)
{

    srand((unsigned int)time(NULL));
    sun_x = 1.0f;
    sun_y = 0.9115f;
    sun_z = 0.41f;
    dark_x = 0.83f;
    dark_y = 1.0f;
    dark_z = 0.8543f;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Experiment 1");
    
    Setup();
    glutDisplayFunc(Display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();    
    printf("\n");
    //Pause to see results or the lack of results
    return 0;
}
