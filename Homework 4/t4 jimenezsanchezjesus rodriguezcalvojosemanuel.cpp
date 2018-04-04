		#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include<iostream>
#include "GL/glut.h"
using namespace std;

// window size
#define dim 300
#define PI 3.141594


unsigned char prevKey;

class CartesianGrid{
private:
	int n_rows, n_columns;
	double increment_rows, increment_columns;

	bool checkPoint(int x, int y){
		return ((x <= (n_columns / 2) && x >= -(n_columns / 2))) && (y <= (n_rows / 2) && y >= -(n_rows / 2));
	}
public:
	CartesianGrid(){
		n_columns = 0;
		n_rows = 0;
	}

	CartesianGrid(int n_columns_param, int n_rows_param){
		n_columns = n_columns_param;
		n_rows = n_rows_param;

		increment_columns = 2.0 / n_columns;	// Coordinates go from -1.0 to 1.0 so we have to divide a space of length 2
		increment_rows = 2.0 / n_rows;
	}

	int getRows(){
		return n_rows;
	}

	int getColumns(){
		return n_columns;
	}

	void drawGrid(){
		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 0.0);

		for(float columns = -1.0; columns < 1.0; columns += increment_columns) {
			glVertex2f(-1.0, columns);
			glVertex2f(1.0, columns);
		}

		for(float rows = -1.0; rows < 1.0; rows += increment_rows) {
			glVertex2f(rows, -1.0);
			glVertex2f(rows, 1.0);
		}

		glEnd();
	}



	void writePixel(int x, int y){
		// First, we check if the coordinates are inside the grid

			float translated_x = -1+((float)x / (float)(n_rows / 2));
			float translated_y = -1+((float)y / (float)(n_columns / 2));

			glPointSize(10);
			glColor3f(0.0, 0.0, 0.0);	// black

			glBegin (GL_POINTS);

			glVertex2f(translated_x, translated_y);

			glEnd();

			cout << "Point (" << x << ", " << y << ") drawn succesfully" << endl;

	}

	void writePixelF(double translated_x,double translated_y){
		// First, we check if the coordinates are inside the grid

			glPointSize(10);
			glColor3f(0.0, 0.0, 0.0);	// black

			glBegin (GL_POINTS);

			glVertex2f(translated_x, translated_y);

			glEnd();

			cout << "Point (" << translated_x << ", " << translated_y<< ") drawn succesfully" << endl;

	}

	void drawLine(int begin_x, int begin_y, int end_x, int end_y){
		if(checkPoint(begin_x, begin_y) && checkPoint(end_x, end_y)){
			float translated_begin_x = (float)begin_x / (float)(n_rows / 2);
			float translated_begin_y = (float)begin_y / (float)(n_columns / 2);
			float translated_end_x = (float)end_x / (float)(n_rows / 2);
			float translated_end_y = (float)end_y / (float)(n_columns / 2);

			glColor3f(1.0, 0.0, 0.0); // red
			glLineWidth(3);

			glBegin(GL_LINES);

			glVertex2f(translated_begin_x, translated_begin_y);
			glVertex2f(translated_end_x, translated_end_y);

			glEnd();

			glLineWidth(1);

			cout << "Line from (" << begin_x << ", " << begin_y << ") to (" << end_x << ", " << end_y << ") drawn succesfully" << endl;
		}
		else{
			cout << "Wrong coordinates, nothing will be drawn" << endl;
		}
	}
	double ajuste(double x,double y,int &t_x,int &t_y){
		double t1_x=(x+1)*(n_rows/2);
		double t1_y=(y+1)*(n_columns/2);

		int abajoX=t1_x;
		int abajoY=t1_y;

		int arribaX=abajoX+1;
		int arribaY=abajoY+1;

		double dabajoX=abajoX*1.0;
		double dabajoY=abajoY*1.0;

		double darribaX=arribaX*1.0;
		double darribaY=arribaY*1.0;
		cout<<t1_x<<"		"<<dabajoX<<" , "<<darribaX<<endl;
		cout<<t1_y<<"		"<<dabajoY<<" , "<<darribaY<<endl;


		if((t1_x-dabajoX)>=(darribaX-t1_x)){
			t_x=darribaX;
		}
		else{
			t_x=dabajoX;
		}
		if((t1_y-dabajoY)>=(darribaY-t1_y)){
			t_y=darribaY;
		}
		else{
			t_y=dabajoY;
		}
	}
};






double angle(int t,float radio){
		return ((PI/2)-((PI/2)/radio)*t);
}


void dibujarpuntos(CartesianGrid &grid, float q){

	for(int t=0;t<=q;t++	){
		double angulo=angle(t,q);
		cout<<t<<"	"<<angulo<<endl;
		//float f=tg(angulo);

	}

}

void Display1(){
	int n_rows = 24;
	int n_columns = 24;
	CartesianGrid grid(n_rows, n_columns);

	grid.drawGrid();
	float radius=1.5;

	int x,y;
	grid.writePixel(0,0);
	//cout<<cos(PI/4) * radius-1<<"			"<<sin(PI/4) * radius-1<<endl;


	for(double t=PI/4;t>=-1;t-=PI/60){
	//grid.writePixelF(cos(t) * radius-1, sin(t) * radius-1);
	grid.ajuste(cos(t) * radius-1, sin(t) * radius-1, x,y);
	cout<<x<<"		"<<y<<endl;
	grid.writePixel(x,y);
	grid.writePixel(x+1,y);
	grid.writePixel(x-1,y);
	}
	glLineWidth(2);
			glColor3f(1.0, 0.0, 0.0); // red
			glBegin(GL_LINE_STRIP);
			for(double i =0; i <PI/2; i += PI / 1440)
 					glVertex2f(cos(i) * radius-1, sin(i) * radius-1);
	glEnd();

	//dibujarpuntos(grid, radius);

}

void Init(void) {

	glClearColor(1.0,1.0,1.0,1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch(prevKey) {
		case '1':
			Display1();
			break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;

	if (key == 27) // escape
		exit(0);

	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow (argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
