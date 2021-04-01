#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides );

int main( void )
{
    GLFWwindow *window;
    

    if ( !glfwInit( ) )
    {
        return -1;
    }
    
   
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "satyam", NULL, NULL );
    
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    
    glfwMakeContextCurrent( window );
    
    glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); 
    glMatrixMode( GL_PROJECTION ); 
    glLoadIdentity( ); 
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); 
    glMatrixMode( GL_MODELVIEW ); 
    glLoadIdentity( );
    

    GLfloat lineVerticesTtoB[] =
    {
        640, 550, 0,
        640, 150, 0
    };

    GLfloat lineVerticesBackwardDiagonal[]=
	{
        820, 550, 0, //add 180
        440, 150, 0 //subtract 170
    };

    GLfloat lineVerticesRtoL[] =
    {
        470, 360, 0,
        800, 360, 0
    };

    GLfloat lineVerticesForwardDiagonal[]=
	{
        470, 540, 0,
        800, 190, 0
    };



    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );

        // render circle
        drawCircle( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 120, 8 );

	 // Render line t to b
        glEnable( GL_LINE_SMOOTH );
        
        glPushAttrib( GL_LINE_BIT );
        glLineWidth( 3 );
      
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, lineVerticesTtoB );
        glDrawArrays( GL_LINES, 0, 2 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glPopAttrib( );
        glDisable( GL_LINE_STIPPLE );
        glDisable( GL_LINE_SMOOTH );	

	 // Render line r to l
        glEnable( GL_LINE_SMOOTH );
     
        glPushAttrib( GL_LINE_BIT );
        glLineWidth( 3 );
       
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, lineVerticesRtoL );
        glDrawArrays( GL_LINES, 0, 2 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glPopAttrib( );
        glDisable( GL_LINE_STIPPLE );
        glDisable( GL_LINE_SMOOTH );	

 	// Render foward diagonal
        glEnable( GL_LINE_SMOOTH );
     
        glPushAttrib( GL_LINE_BIT );
        glLineWidth( 3 );
       
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, lineVerticesForwardDiagonal );
        glDrawArrays( GL_LINES, 0, 2 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glPopAttrib( );
        glDisable( GL_LINE_STIPPLE );
        glDisable( GL_LINE_SMOOTH );	


	// Render backward diagonal
        glEnable( GL_LINE_SMOOTH );
     
        glPushAttrib( GL_LINE_BIT );
        glLineWidth( 3 );
       
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, lineVerticesBackwardDiagonal );
        glDrawArrays( GL_LINES, 0, 2 );
        glDisableClientState( GL_VERTEX_ARRAY );
        glPopAttrib( );
        glDisable( GL_LINE_STIPPLE );
        glDisable( GL_LINE_SMOOTH );	

 	
        glfwSwapBuffers( window );
        
        glfwPollEvents( );
    }
    
    glfwTerminate( );
    
    return 0;
}


void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides )
{
    GLint numberOfVertices = numberOfSides + 1;
    
    GLfloat doublePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        circleVerticesX[i] = x + ( radius * cos( i * doublePi / numberOfSides ) );
        circleVerticesY[i] = y + ( radius * sin( i * doublePi / numberOfSides ) );
        circleVerticesZ[i] = z;
    }
    
    GLfloat allCircleVertices[numberOfVertices * 3];
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
        allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }
    
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
    glDrawArrays( GL_LINE_STRIP, 0, numberOfVertices );
    glDisableClientState( GL_VERTEX_ARRAY );

	if(radius>=0){
		drawCircle(x,y,z,radius-20, 8);
	}
	
	
}


