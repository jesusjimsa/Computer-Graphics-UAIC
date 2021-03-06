#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// the size of the window measured in pixels
#define dim 600

unsigned char prevKey;
GLint k;

// the size of the cube
GLdouble lat = 5;

void parallelProjection(unsigned char);
void DisplayAxe();
void InitObiect();
void DisplayObject();

void Init(void){
	glClearColor(1, 1, 1, 1);
	
	glEnable(GL_DEPTH_TEST);
	
	// generation of one empty display list having the ID k
	k = glGenLists(1);
	InitObiect();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Display(){
	switch (prevKey){
		case '0':
			// the identity matrix replaces the matrices at the top of the
			// stacks of the modelview and projection matrices
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			DisplayAxe();
			break;
		case 'a':
			DisplayAxe();
			break;
		case 'c':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;
		case 'x':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			parallelProjection('X');
			glMatrixMode(GL_MODELVIEW);
			glRotatef(10, 1, 0, 0);
			DisplayAxe();
			DisplayObject();
			break;
		case 'y':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			parallelProjection('Y');
			glMatrixMode(GL_MODELVIEW);
			glRotatef(10, 0, 1, 0);
			DisplayAxe();
			DisplayObject();
			break;
		case 'z':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			parallelProjection('Z');
			glMatrixMode(GL_MODELVIEW);
			glRotatef(10, 0, 0, 1);
			DisplayAxe();
			DisplayObject();
			break;
		case 'q':
			// orthographic parallel projection: front-elevation projection
			parallelProjection('q');
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			DisplayAxe();
			glTranslated(0, 0, -lat);
			DisplayObject();
			break;
		case 'w':
			// orthographic parallel projection: front-elevation projection
			parallelProjection('w');
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();
			glTranslated(0, 0, -lat);
			glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
			glRotated(180, 0, 1, 0);
			glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
			DisplayAxe();
			DisplayObject();
			glPopMatrix();
			break;
		case 'e':
			// orthographic parallel projection: front-elevation projection
			parallelProjection('w');
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();
			glTranslated(0, 0, -lat);
			glTranslated(lat / 2.0, lat / 2.0, lat / 2.0);
			glRotated(90, 1, 0, 0);
			glTranslated(-lat / 2.0, -lat / 2.0, -lat / 2.0);
			DisplayAxe();
			DisplayObject();
			glPopMatrix();
			break;
		case '+':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			parallelProjection('+');
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(-10, -10, -10);
			DisplayAxe();
			DisplayObject();
			glTranslatef(10, 10, 10);
			glPopMatrix();
			break;
		case 'n':
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			parallelProjection('n');
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-15, -10, -40);
			DisplayObject();
			DisplayAxe();
			glTranslatef(15, 10, 40);
			glPopMatrix();
			break;
		default:
			break;
	}
	
	glutSwapBuffers();
}

void Reshape(int w, int h){
	h = (h == 0) ? 1 : h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y){
	prevKey = key;
	
	if (key == 27){
		exit(0);
	}
	
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y){
}

void parallelProjection(unsigned char c){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double t = 30 * atan(1) * 4 / 180;
	double cost = cos(t) / 2;
	double sint = sin(t) / 2;
	GLdouble m[16] = {1, 0, 0, 0, 0, 1, 0, 0, cost, sint, 0, 0, 0, 0, 0, 1};
	
	switch (c){
		case 'X':
		case 'Y':
		case 'Z':
			glOrtho(-10, 10, -10, 10, -20, 20);
			break;
		case 'q':
		case 'w':
		case 'e':
			glOrtho(-1, 6, -1, 6, -1, 20);
			break;
		case '+':
			glFrustum(-5, 5, -5, 5, 2, 200);
			break;
		case 'n':glMultMatrixd(m);
			glOrtho(-10, 10, -10, 10, 2, 20);
			
			break;
		default:
			break;
	}
}

void DisplayAxe(){
	int X, Y, Z;
	X = Y = Z = 200;
	glLineWidth(2);
	
	// Ox axis - green
	glColor3f(0.1, 1, 0.1);
	glBegin(GL_LINE_STRIP);
	
	glVertex3f(0, 0, 0);
	glVertex3f(X, 0, 0);
	
	glEnd();
	
	// Oy axus - blue
	glColor3f(0.1, 0.1, 1);
	glBegin(GL_LINE_STRIP);
	
	glVertex3f(0, 0, 0);
	glVertex3f(0, Y, 0);
	
	glEnd();
	
	// Oz axis - red
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Z);
	
	glEnd();
	
	glLineWidth(1);
}

void InitObiect(){
	glNewList(k, GL_COMPILE);
	
	// face 1
	glColor3f(1, 0, 0); // red
	glBegin(GL_QUADS);
	
	glVertex3d(0, lat, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, 0, lat);
	glVertex3d(0, 0, lat);
	
	glEnd();
	
	// face 2
	glColor3f(1, 1, 0); // yellow
	glBegin(GL_QUADS);
	
	glVertex3d(lat, 0, 0);
	glVertex3d(lat, 0, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, lat, 0);
	
	glEnd();
	
	// face 3
	glColor3f(0, 1, 0); // green
	glBegin(GL_QUADS);
	
	glVertex3d(0, lat, lat);
	glVertex3d(lat, lat, lat);
	glVertex3d(lat, lat, 0);
	glVertex3d(0, lat, 0);
	
	glEnd();
	
	// face 4
	glColor3f(0, 0, 1); // blue
	glBegin(GL_QUADS);
	
	glVertex3d(0, 0, 0);
	glVertex3d(lat, 0, 0);
	glVertex3d(lat, 0, lat);
	glVertex3d(0, 0, lat);
	
	glEnd();
	
	// face 5
	glColor3f(1, 0, 1); // magenta
	glBegin(GL_QUADS);
	
	glVertex3d(0, 0, lat);
	glVertex3d(0, 0, 0);
	glVertex3d(0, lat, 0);
	glVertex3d(0, lat, lat);
	
	glEnd();
	
	// face 6
	glColor3f(0, 1, 1); // cyan
	glBegin(GL_QUADS);
	
	glVertex3d(0, lat, 0);
	glVertex3d(lat, lat, 0);
	glVertex3d(lat, 0, 0);
	glVertex3d(0, 0, 0);
	
	glEnd();
	glEndList();
}

void DisplayObject(){
	glCallList(k);
}

int main(int argc, char **argv){
	
	glutInit(&argc, argv);
	
	glutInitWindowSize(dim, dim);
	
	glutInitWindowPosition(100, 100);
	
	glutInitDisplayMode(GL_COLOR_BUFFER_BIT | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutCreateWindow(argv[0]);
	
	Init();
	
	glutReshapeFunc(Reshape);
	
	glutKeyboardFunc(KeyboardFunc);
	
	glutMouseFunc(MouseFunc);
	
	glutDisplayFunc(Display);
	
	glutMainLoop();
	
	return 0;
}
