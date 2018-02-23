#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

unsigned char prevKey;

void Display1() {
	glColor3f(0.2,0.15,0.88); // blue
	glBegin(GL_LINES); // drawing a line
	glVertex2i(1,1); // the coordinates of a peak
	glVertex2i(-1,-1);
	glEnd();
	
	glColor3f(1,0.1,0.1); // Red
	glBegin(GL_LINES);
	glVertex2i(-1,1);
	glVertex2i(1,-1);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2d(-0.5,0);
	glVertex2d(0.5,0);
	glEnd();
}

void Display2() {
	glColor3f(1,0.1,0.1); // Red
	glBegin(GL_LINES);
	glVertex2f(1.0,1.0);
	glVertex2f(0.9,0.9);
	glVertex2f(0.8,0.8);
	glVertex2f(0.7,0.7);
	glVertex2f(0.6,0.6);
	glVertex2f(0.5,0.5);
	glVertex2f(-0.5,-0.5);
	glVertex2f(-1.0,-1.0);
	glEnd();
}

void Display3() {
	// drawing points GL_POINTS: draws n points
	glColor3f(1,0.1,0.1); // Red
	glBegin(GL_POINTS);
	// to complete ...
	glEnd();
}

void Display4() {
	glColor3f(1,0.1,0.1); // Red
	// polygon line drawing GL_LINE_STRIP: (v0, v1), (v1, v2), (v_ {n-2}, v_ {n-1})
	glBegin(GL_LINE_STRIP);
	// to complete ...
	glEnd();
}

void Display5() {
	glColor3f(1,0.1,0.1); // Red
	// dark polygonal line drawing GL_LINE_LOOP : (v0,v1), (v1,v2), (v_{n-1},v0)
	glBegin(GL_LINE_LOOP);
	// to complete ...
	glEnd();
}

void Display6() {
	glColor3f(1,0.1,0.1); // Red
	// drawing triangles GL_TRIANGLES : (v0,v1,v2), (v3,v4,v5), ...
	glBegin(GL_TRIANGLES);
	// to complete ...
	glEnd();
}

void Display7() {
	// tracing rectangles GL_QUADS : (v0,v1,v2,v3), (v4,v5,v6,v7), ...
	glBegin(GL_QUADS);
	// to complete ...
	glEnd();
}

void Display8() {
	// convex polygon drawing GL_QUADS : (v0,v1,v2, ..., v_{n-1})
	glBegin(GL_POLYGON);
	// to complete ...
	glEnd();
}

void Init(void) {
	// Specifies the color of a buffer after it
	// was deleted using the glClear function. Last
	// argument represents transparency (1 - total
	// opacity, 0 - total transparency)
	glClearColor(1.0,1.0,1.0,1.0);
	
	// line thickness
	glLineWidth(3);
	
	// the size of the points
	glPointSize(4);
	
	// void function glPolygonMode (GLenum face, GLenum mode)
	// Controls how to draw a polygon
	// mode: GL_POINT (primitive only) GL_LINE (only
	// 		edges) GL_FILL (full polygon)
	// makes: type of geometric primitive dpdv. of orientation
	// 		GL_FRONT - primitive oriented directly
	// 		GL_BACK - Reverse Oriented primitives
	// 		GL_FRONT_AND_BACK - both types
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	printf("Call Display\n");
	
	// delete the indicated buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	switch(prevKey) {
		case '1':
			Display1();
			break;
		case '2':
			Display2();
			break;
		case '3':
			Display3();
			break;
		case '4':
			Display4();
			break;
		case '5':
			Display5();
			break;
		case '6':
			Display6();
			break;
		case '7':
			Display7();
			break;
		case '8':
			Display8();
			break;
		default:
			break;
	}
	
	// force redrawing image
	glFlush();
}

/*
 	The w (width) and h (height) parameters represent
 	the new window dimensions
*/
void Reshape(int w, int h) {
	printf("Call Reshape : width = %d, height = %d\n", w, h);
	
	// void glViewport function (GLint x, GLint y,
	// 							GLsizei width, GLsizei height)
	// defines the display gate: that rectangular surface
	// from the display window used for viewing.
	// x, y are the coordinates of the stg. down again
	// width and height are width and height in pixels.
	// In the case below, the display gateway and the window coincide
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

/* 
 	The key parameter indicates the key code and
 	x, y the position of the mouse cursor
 */
void KeyboardFunc(unsigned char key, int x, int y) {
	printf("You typed <%c>. The mouse is in position %d, %d.\n", key, x, y);
	// the key pressed will be used in Display for
	// displaying some images
	prevKey = key;
	if (key == 27){ // escape
		exit(0);
	}
	glutPostRedisplay();
}

/* 
 Codul butonului poate fi :
 GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
 Parametrul state indica starea: "apasat" GLUT_DOWN sau
 "eliberat" GLUT_UP
 Parametrii x, y : coordonatele cursorului de mouse
 */
void MouseFunc(int button, int state, int x, int y) {
	printf("Call MouseFunc : you %s button %s in position %d %d\n", (state == GLUT_DOWN) ? "pressed" : "released",
		   (button == GLUT_LEFT_BUTTON) ? "left" : ((button == GLUT_RIGHT_BUTTON) ? "right": "middle"), x, y);
}

int main(int argc, char** argv) {
	// Initialization of the GLUT library. Arguments argc
	// and argv are arguments in the command line and must
	// not be modified before calling the function
	// void glutInit (int * argcp, char ** argv)
	// It is recommended to call any function in the library
	// GLUT to be made after calling this function.
	glutInit(&argc, argv);
	
	// Arguments of the function
	// void glutInitWindowSize (int width, int width)
	// represents the width and height of the window
	// expressed in pixels. The predefined values are 300, 300.
	glutInitWindowSize(300, 300);
	
	// Arguments of the function
	// void glutInitWindowPosition (int x, int y)
	// represents the coordinates of the upper left top
	// of the window, expressed in pixels.
	// Predefined values are -1, -1.
	glutInitWindowPosition(100, 100);
	
	// void glutInitDisplayMode (unsigned int mode)
	// sets the initial display mode. This is achieved
	// through a UA on bits between different display masks
	// (constants of the GLUT library):
	// 1. GLUT_SINGLE: single image buffer. Represent
	// 		default option for number of image
	// 		buffers.
	// 2. GLUT_DOUBLE: 2 image buffers.
	// 3. GLUT_RGB or GLUT_RGBA: the colors will be displayed in
	// 		RGB module.
	// 4. GLUT_INDEX: Color Selection Mode.
	// 		etc. (see the GLUT library specification)
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	
	// int glutCreateWindow (char * name)
	// creates a window with the name given by the argument
	// name and return a window identifier.
	glutCreateWindow (argv[0]);
	
	Init();
	
	// Callback functions: functions defined in the program and
	// registered in the system through some functions
	// GLUT. They are called by the operating system
	// depending on the event
	
	// Function
	// void glutReshapeFunc (void (* Reshape) (int width, int height)
	// records the callback function Reshape that is called
	// for the display window to change its shape.
	glutReshapeFunc(Reshape);
	
	// Function
	// void glutKeyboardFunc (void (* KeyboardFunc) (unsigned char, int, int))
	// records the Callback function called KeyboardFunc
	// to a key action.
	glutKeyboardFunc(KeyboardFunc);
	
	// Function
	// void glutMouseFunc (void (* MouseFunc)) (int, int, int, int)
	// records the MouseFunc callback function that is called
	// when you press or release a mouse button.
	glutMouseFunc(MouseFunc);
	
	// Function
	// void glutDisplayFunc (void (* Display) (void))
	// records the Callback Display function that is called
	// draw window whenever necessary: the
	// initialization when changing the window dimensions
	// or the function call
	// void glutPostRedisplay (void).
	glutDisplayFunc(Display);
	
	// void glutMainLoop () launches the processing loop
	// of GLUT events. The loop can only go out through
	// Close the application window. This function must be
	// called at most once in the program. functions
	// callback must be logged before calling this
	// functions.
	// When the event queue is empty then it is executed
	// callback function registered by calling IdleFunc
	// void glutIdleFunc (void (* IdleFunc) (void)
	glutMainLoop();
	
	return 0;
}
