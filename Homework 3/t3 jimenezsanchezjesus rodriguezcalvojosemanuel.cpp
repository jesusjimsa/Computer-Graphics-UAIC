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

bool pertenece(int i,int j, int x1,int y1,int x2,int y2){
	if(i==x1 && j==y1){return true;}
	else{
		if(i==x2 && j==y2){return true;}
		else{	
				double derecha, izquierda;
				if(i-x1==0){return false;}
				else{derecha=(j-y1);
					derecha=derecha/(i-x1);}
				if(x2-x1==0){return false;}
				else{izquierda=(y2-y1);
					izquierda=izquierda/(x2-x1);}
			if(izquierda-derecha==0){return true;}
			else{return false;}
		}
	}
}

void pixelIntersectionUp(CartesianGrid &grid,int x1, int y1,int x2,int y2){
	for(double t=-4;t<=4;t++){
		for(int i = -grid.getColumns() / 2; i <=grid.getColumns() / 2; i ++){
			for(int j= -grid.getColumns() / 2; j <=grid.getColumns() / 2; j++){
						
					if(pertenece(i,j,x1+t,y1,x2+t,y2)){
						grid.writePixel(i,j);
					}
			}
		}
	}
}


double aplicarfomula(int j,int x1, int y1,int x2,int y2){
		double i;
		i=(j-y1)*(x2-x1);
		i=i/(y2-y1);
		i=i+x1;
		return i;
}
pair<int,int> acerca(CartesianGrid &grid, double j){
		
	int t1=(int)j;
	if(j<0){j=j-1;}else{j=j+1;}
	 int t2=(int)j;
	pair<int,int> sol(t1,t2);
	return sol;
}


void pixelIntersectionDown(CartesianGrid &grid,int x1, int y1,int x2,int y2 ){
		int arriba,abajo;		
		if(y1>y2){arriba=x1;abajo=x2;}
		else{arriba=x2;abajo=x1;}		
		for (int i=abajo;i<=arriba;i=i+1){
				double pj=aplicarfomula(i,x1,y1,x2,y2);
				int pjx=pj;
				double tjx=pjx*1.0;				
				if(tjx==pj){grid.writePixel(pj,i);}
				else{
					cout<<pj<<endl<<endl;
					pair<int,int> sol=acerca(grid,pj);
					grid.writePixel(sol.first,i);
					grid.writePixel(sol.second,i);	
				}
		}

}

void Display1(){
	int n_rows = 24;
	int n_columns = 24;
	CartesianGrid grid(n_rows, n_columns);

	grid.drawGrid();
	grid.drawLine(-n_columns / 2, n_rows / 2, n_columns / 2, n_rows / 6);
	pixelIntersectionUp(grid,-n_columns / 2, n_rows / 2, n_columns / 2, n_rows / 6);
	
	grid.drawLine(-n_columns / 2, -n_rows / 2, n_columns / 2, (-n_rows / 24) + 2);
	pixelIntersectionDown(grid,-n_columns / 2, -n_rows / 2, n_columns / 2, (-n_rows / 24) + 2);
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
