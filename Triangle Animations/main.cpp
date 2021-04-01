#include <stdlib.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

using namespace std;

bool drawTriangle = false;
int count = 0;
float _angle = 30.0f;
float vertexForShrink = -0.5f;
bool sizeUp = false;
bool colorUp = false;
bool translateDown = false;

float blueAnimate = 1.0f;
float translate = 0.0f;


void keyPress(unsigned char key,int x,int y)
{

    switch(key)
    {
       case 27:
            exit(0);     
    }
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void resize(int w, int h) {
   
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); 
    

    glLoadIdentity(); //reset
    gluPerspective(45.0,                 
                   (double)w / (double)h, 
                   1.0,                 
                   200.0);               
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);
   
    glLoadIdentity();


//rotate

    glPushMatrix(); //save transform

    glRotatef(_angle, -1.5f, 0.5f, -5.0f); 
	glColor3f(0.5f, blueAnimate, 0.2f);
    glBegin(GL_TRIANGLES);
   
        glVertex3f(-0.5f, 0.5f, -5.0f);
        glVertex3f(-1.0f, 1.5f, -5.0f);
        glVertex3f(-1.5f, 0.5f, -5.0f);

    glEnd();
    glPopMatrix(); //undo transform

//shrink/expand

	glPushMatrix(); //save transform

	glColor3f(0.5f, 0.2f, blueAnimate);
    glBegin(GL_TRIANGLES);
   		
        glVertex3f(-1, -1.5f, -5.0f);
        glVertex3f(-2.0f, vertexForShrink, -5.0f);
        glVertex3f(-2.0f, -1.5f, -5.0f);

    glEnd();
    glPopMatrix(); //undo transform

//translate

	glPushMatrix(); //save transform
	
	glTranslatef(translate, translate, translate); 
	glColor3f(blueAnimate, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
   		
        glVertex3f(-1, -1.5f, -5.0f);
        glVertex3f(-2.0f, -0.5, -5.0f);
        glVertex3f(-2.0f, -1.5f, -5.0f);

    glEnd();
    glPopMatrix(); //undo transform

	
		

    glutSwapBuffers();
}

void timerFunc(int value) {
    _angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
	
	
	if(translateDown){
		translate -=0.01f;
		if(translate<0){
			translateDown = false;
		}
	}
	else{
		translate+=0.01f;
		if(translate > 1.7f){
		translateDown = true;
		}
	}
	
	
	
	if(colorUp){
		blueAnimate += 0.01f;
		if(blueAnimate >1){
			colorUp = false;
		}
	}
	else{
		blueAnimate -= 0.01f;
		if(blueAnimate<0){
		colorUp=true;
		}
	}
	
	

	if(sizeUp){
		vertexForShrink = 0.01f + vertexForShrink;
		if((vertexForShrink)>-0.5f){
		sizeUp=false;
		}
	}
	else{
		if(vertexForShrink>-1.3f){
			vertexForShrink -= 0.01f;
		}
		else {
			sizeUp = true;
		}
	}
	
   
    glutPostRedisplay(); //redisplay
   
    //update at 25 seconds
    glutTimerFunc(25, timerFunc, 0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
   
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
   
    glutInitWindowSize(400,400);
   
    glutCreateWindow("satyam");
   
    initRendering();
   
    glutDisplayFunc(display);
   
    glutKeyboardFunc(keyPress);

    glutReshapeFunc(resize);
   
    glutTimerFunc(25, timerFunc, 0); //timer function
   
    glutMainLoop();
   
    return(0);
}


