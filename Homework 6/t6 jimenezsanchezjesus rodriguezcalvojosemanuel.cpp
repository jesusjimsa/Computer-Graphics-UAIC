#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>       /* time */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// the size of the window measured in pixels
#define dim 600

using namespace std;

unsigned char prevKey;

enum EObiect{cubw, cubs, sferaw, sferas, triangle, asked_cube} ob = cubw;

int change_cube_axis = 0;
int vertexA[3], vertexB[3], vertexC[3];

void DisplayAxe(){
	int X, Y, Z;
	X = Y = 200;
	Z = 200;
	
	glLineWidth(2);
	
	// Ox axis - green
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(X, 0, 0);
	glEnd();
	
	// Oy axis - blue
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, Y, 0);
	glEnd();
	
	// Oz axis - red
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Z);
	glEnd();
	
	glLineWidth(1);
}

// wireframe cube
void Display1(){
	glColor3f(1, 0, 0);
	glutWireCube(1);
}

// solid cube
void Display2(){
	glColor3f(1, 0, 0);
	glutSolidCube(1);
}

// wireframe sphere
void Display3(){
	glColor3f(0, 0, 1);
	glutWireSphere(1, 10, 10);
}

// solid sphere
void Display4(){
	glColor3f(0, 0, 1);
	glutSolidSphere(1, 10, 10);
}

void randAxis(int vertex[]){
	vertex[0] = rand() % 10;
	vertex[1] = rand() % 10;
	vertex[2] = rand() % 10;
}

// Triangle
void Display5(bool change_vertices){
	glColor3f(1, 0, 0);
	
	glBegin(GL_TRIANGLES);
	
	if(change_vertices){
		randAxis(vertexA);
	}
	
	glVertex3f(vertexA[0], vertexA[1], vertexA[2]);
	
	if(change_vertices){
		randAxis(vertexB);
	}
	
	glVertex3f(vertexB[0], vertexB[1], vertexB[2]);
	
	if(change_vertices){
		randAxis(vertexC);
	}
	
	glVertex3f(0, 0, 0);
	
	glEnd();
}

void Display6(bool change){
	glLineWidth(2);
	glColor3f(0, 0, 0);
	
	// Transformations for placing the cube in the right place
	switch (change_cube_axis) {
		case 1:
			glRotatef(45, 0, 0, 1);
			break;
		case 2:
			glRotatef(45, 0, 1, 0);
			break;
		case 3:
			glRotatef(45, 1, 0, 0);
			break;
		default:
			break;
	}
	
	glTranslatef(0.5, 0.5, 0.5);
	
	// Drawing the cube with the right size
	glutWireCube(1);
	
	// Placing everything where it was before
	glTranslatef(-0.5, -0.5, -0.5);
	
	switch (change_cube_axis) {
		case 0:
			if(change){
				change_cube_axis++;
			}
			break;
		case 1:
			glRotatef(-45, 0, 0, 1);
			
			if(change){
				change_cube_axis++;
			}
			break;
		case 2:
			glRotatef(-45, 0, 1, 0);
			
			if(change){
				change_cube_axis++;
			}
			break;
		case 3:
			glRotatef(-45, 1, 0, 0);
			
			if(change){
				change_cube_axis = 0;
			}
			break;
		default:
			break;
	}
}

void DisplayM(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glRotatef(-45, 0, 1, 0);
	
	Display6(false);
}

void DisplayObject(){
	switch (ob){
		case cubw:
			Display1();
			break;
		case cubs:
			Display2();
			break;
		case sferaw:
			Display3();
			break;
		case sferas:
			Display4();
			break;
		case triangle:
			Display5(false);
			break;
		case asked_cube:
			Display6(false);
			break;
		default:
			break;
	}
}

void DisplayQ(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(20, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
	glTranslatef(2.5, 2.5, 2.5);
//	glRotated(30, 1, 1, 1);
	glutWireCube(5);
}

void DisplayW(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(20, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
	glTranslatef(2.5, 2.5, 2.5);
//	glRotated(30, 1, 1, 1);
	glRotatef(45, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glutWireCube(5);
}

// the rotation with 10 degrees about the Ox axis
void DisplayX() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 1, 0, 0);
}

// the rotation with 10 degrees about the Oy axis
void DisplayY() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 1, 0);
}

// the rotation with 10 degrees about the Oz axis
void DisplayZ() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 0, 1);
}

// the rotation with 10 degrees about the all axes
void DisplayP() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 1, 1, 1);
}

// translation by 0.2, 0.2, 0.2
void DisplayT() {
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.2, 0.2, 0.2);
}

// scaling by 1.2, 1.2, 1.2
void DisplayS() {
	glMatrixMode(GL_MODELVIEW);
	glScalef(1.2, 1.2, 1.2);
}

void Init(void) {
	glClearColor(1, 1, 1, 1);
	glLineWidth(2);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 30, -30);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(20, 1, 0, 0);
	glRotated(-20, 0, 1, 0);
}

void Display(void) {
	switch(prevKey){
		case 'a':
			DisplayAxe();
			break;
		case '0':
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glRotated(20, 1, 0, 0);
			glRotated(-20, 0, 1, 0);
			break;
		case '1':
			Display1();
			ob = cubw;
			break;
		case '2':
			Display2();
			ob = cubs;
			break;
		case '3':
			Display3();
			ob = sferaw;
			break;
		case '4':
			Display4();
			ob = sferas;
			break;
		case '5':
			Display5(true);
			ob = triangle;
			break;
		case '6':
			Display6(true);
			ob = asked_cube;
			break;
		case 'x':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayX();
			DisplayAxe();
			DisplayObject();
			break;
		case 'y':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayY();
			DisplayAxe();
			DisplayObject();
			break;
		case 'z':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayZ();
			DisplayAxe();
			DisplayObject();
			break;
		case 't':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayT();
			DisplayAxe();
			DisplayObject();
			break;
		case 's':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayS();
			DisplayAxe();
			DisplayObject();
			break;
		case 'p':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayP();
			DisplayAxe();
			DisplayObject();
			break;
		case 'q':
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glClear(GL_COLOR_BUFFER_BIT);
			DisplayAxe();
			DisplayQ();
			break;
		case 'w':
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glClear(GL_COLOR_BUFFER_BIT);
			DisplayAxe();
			DisplayW();
			break;
		default:
			break;
	}
	
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	
	if (key == 27){
		exit(0);
	}
	
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {
	/* initialize random seed: */
	srand((unsigned int)time(NULL));
	
	glutInit(&argc, argv);
	
	glutInitWindowSize(dim, dim);
	
	glutInitWindowPosition(100, 100);
	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	
	glutCreateWindow (argv[0]);
	
	Init();
	
	glutReshapeFunc(Reshape);
	
	glutKeyboardFunc(KeyboardFunc);
	
	glutMouseFunc(MouseFunc);
	
	glutDisplayFunc(Display);
	
	glutMainLoop();
	
	return 0;
}
