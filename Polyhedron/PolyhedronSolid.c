#include <GL/glut.h>


void reshape(int width, int height)
{

	glViewport(0, 0, (GLint)width, (GLint)height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);

	glMatrixMode(GL_MODELVIEW);
}


void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(4.5, 0.0, 0.0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.70, 0.80, 0.5);
	glutSolidCube(3.0);

	glColor3f(0.70, 0.80, 0.5);
	glutWireCube(3.0);

	glLoadIdentity();
	glTranslatef(-3.5, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(3.0);

	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(3.0);

	glColor3f(0.44, 0.0, 1.0);
	glLoadIdentity();
	glTranslatef(-3.0, -5.5, 0.0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glutSolidTorus(0.75, 1.5, 10, 10);

	glColor3f(0.44, 0.0, 1.0);
	glutWireTorus(0.75, 1.5, 10, 10);

	glColor3f(0.34, 1.0, 0.0);
	glLoadIdentity();
	glTranslatef(0.0, 5.5, 0.0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glutSolidCone(2.0, 4.0, 10, 10);

	glColor3f(0.34, 1.0, 0.0);
	glutWireCone(2.0, 4.0, 10, 10);

	glColor3f(0.50, 0.45, 1.0);
	glLoadIdentity();
	glTranslatef(-5.5, 5.0, 0.0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glutSolidSphere(2.0, 20, 30);

	glColor3f(0.50, 0.45, 1.0);
	glutWireSphere(2.0, 20, 30);

	glColor3f(1.0, 0.0, 0.2);
	glLoadIdentity();
	glTranslatef(4.5, 5.5, 0.0);
	glRotatef(45, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glutSolidTetrahedron();

	glColor3f(1.0, 0.0, 0.2);
	glutWireTetrahedron();

	glColor3f(0.5, 0.10, 0.0);
	glLoadIdentity();
	glTranslatef(-7.0, -5.5, 0.0);
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(60, 0.0, 1.0, 0.0);
	glutSolidOctahedron();

	glColor3f(0.5, 0.10, 0.0);
	glutWireOctahedron();

	glColor3f(0.65, 0.50, 0.5);
	glLoadIdentity();
	glTranslatef(2.5, -5.5, 0.0);
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(60, 0.0, 1.0, 0.0);
	glutSolidDodecahedron();

	glColor3f(0.65, 0.50, 0.5);
	glutWireDodecahedron();

	glColor3f(0.0, 0.5, 0.0);
	glLoadIdentity();
	glTranslatef(6.5, -5.5, 0.0);
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(60, 0.0, 1.0, 0.0);
	glutSolidIcosahedron();

	glColor3f(0.0, 0.5, 0.0);
	glutWireIcosahedron();
	glFlush();
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Polyhedron Solid Shapes");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);

	glutMainLoop();

}
