#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// window size
#define dim 300

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
		if(checkPoint(x, y)){
			float translated_x = (float)x / (float)(n_rows / 2);
			float translated_y = (float)y / (float)(n_columns / 2);
			
			glPointSize(10);
			glColor3f(0.0, 0.0, 0.0);	// black
			
			glBegin (GL_POINTS);
			
			glVertex2f(translated_x, translated_y);
			
			glEnd();
			
			cout << "Point (" << x << ", " << y << ") drawn succesfully" << endl;
		}
		else{
			cout << "Wrong coordinates, nothing will be drawn" << endl;
		}
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
};

void pixelIntersectionUp(CartesianGrid &grid){
	int p_row = grid.getRows() / 2;

	for(int i = -grid.getColumns() / 2; i <= grid.getColumns() / 2; i += 3){
		for(int j = i - 4; j <= i + 4; j++){
			grid.writePixel(j, p_row);
		}

		p_row--;
	}
}

void pixelIntersectionDown(CartesianGrid &grid){
	int p_row = -grid.getRows() / 2;
	
	for(int i = -grid.getColumns() / 2; i <= grid.getColumns() / 2; i += 2){
		grid.writePixel(i, p_row);
		grid.writePixel(i + 1, p_row);
		
		p_row++;
	}
}

void Display1(){
	int n_rows = 24;
	int n_columns = 24;
	CartesianGrid grid(n_rows, n_columns);

	grid.drawGrid();
	grid.drawLine(-n_columns / 2, n_rows / 2, n_columns / 2, n_rows / 6);
	pixelIntersectionUp(grid);
	
	grid.drawLine(-n_columns / 2, -n_rows / 2, n_columns / 2, (-n_rows / 24) + 1);
	pixelIntersectionDown(grid);
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
