#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// window size
#define dim 300
#define PI 3.141594
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

typedef struct{
	double x, y;
} Point;

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
		
		increment_columns = 2.0 / n_columns; // Coordinates go from -1.0 to 1.0 so we have to divide a space of length 2
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
		
		for (float columns = -1.0; columns < 1.0; columns += increment_columns){
			glVertex2f(-1.0, columns);
			glVertex2f(1.0, columns);
		}
		
		for (float rows = -1.0; rows < 1.0; rows += increment_rows){
			glVertex2f(rows, -1.0);
			glVertex2f(rows, 1.0);
		}
		
		glEnd();
	}
	
	void writePixel(int x, int y){
		// First, we check if the coordinates are inside the grid
		
		float translated_x = -1 + ((float)x / (float)(n_rows / 2));
		float translated_y = -1 + ((float)y / (float)(n_columns / 2));
		
		glPointSize(10);
		glColor3f(0.0, 0.0, 0.0); // black
		
		glBegin(GL_POINTS);
		
		glVertex2f(translated_x, translated_y);
		
		glEnd();
		
		cout << "Point (" << x << ", " << y << ") drawn succesfully" << endl;
	}
	
	void writePixelF(double translated_x, double translated_y){
		// First, we check if the coordinates are inside the grid
		glPointSize(10);
		glColor3f(0.0, 0.0, 0.0); // black
		
		glBegin(GL_POINTS);
		
		glVertex2f(translated_x, translated_y);
		
		glEnd();
		
		cout << "Point (" << translated_x << ", " << translated_y << ") drawn succesfully" << endl;
	}
	
	void drawLine(int begin_x, int begin_y, int end_x, int end_y){
		if (checkPoint(begin_x, begin_y) && checkPoint(end_x, end_y)){
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
	
	void ajuste(double x, double y, int &t_x, int &t_y){
		double t1_x = (x + 1) * (n_rows / 2);
		double t1_y = (y + 1) * (n_columns / 2);
		
		int abajoX = t1_x;
		int abajoY = t1_y;
		
		int arribaX = abajoX + 1;
		int arribaY = abajoY + 1;
		
		double dabajoX = abajoX * 1.0;
		double dabajoY = abajoY * 1.0;
		
		double darribaX = arribaX * 1.0;
		double darribaY = arribaY * 1.0;
		
		cout << t1_x << "		" << dabajoX << " , " << darribaX << endl;
		cout << t1_y << "		" << dabajoY << " , " << darribaY << endl;
		
		if ((t1_x - dabajoX) >= (darribaX - t1_x)){
			t_x = darribaX;
		}
		else{
			t_x = dabajoX;
		}
		
		if ((t1_y - dabajoY) >= (darribaY - t1_y)){
			t_y = darribaY;
		}
		else{
			t_y = dabajoY;
		}
	}
};

void Display1(){
	int n_rows = 24;
	int n_columns = 24;
	
	CartesianGrid grid(n_rows, n_columns);
	grid.drawGrid();
	
	float radius = 1.5;
	int x, y;
	
	grid.writePixel(0, 0);
	
	for (double t = PI / 4; t >= -1; t -= PI / 60){
		//grid.writePixelF(cos(t) * radius-1, sin(t) * radius-1);
		grid.ajuste(cos(t) * radius - 1, sin(t) * radius - 1, x, y);
		cout << x << "		" << y << endl;
		grid.writePixel(x, y);
		grid.writePixel(x + 1, y);
		grid.writePixel(x - 1, y);
	}
	
	glLineWidth(2);
	glColor3f(1.0, 0.0, 0.0); // red
	glBegin(GL_LINE_STRIP);
	
	for (double i = 0; i < PI / 2; i += PI / 1440){
		glVertex2f(cos(i) * radius - 1, sin(i) * radius - 1);
	}
	
	glEnd();
}

class CartesianGridTra{
private:
	int n_rows, n_columns;
	double increment_rows, increment_columns;
	
	bool checkPoint(int x, int y){
		return ((x <= (n_columns / 2) && x >= -(n_columns / 2))) && (y <= (n_rows / 2) && y >= -(n_rows / 2));
	}
	
public:
	CartesianGridTra(){
		n_columns = 0;
		n_rows = 0;
	}
	
	CartesianGridTra(int n_columns_param, int n_rows_param){
		n_columns = n_columns_param;
		n_rows = n_rows_param;
		
		increment_columns = 2.0 / n_columns; // Coordinates go from -1.0 to 1.0 so we have to divide a space of length 2
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
		
		for (float columns = -1.0; columns < 1.0; columns += increment_columns){
			glVertex2f(-1.0, columns);
			glVertex2f(1.0, columns);
		}
		
		for (float rows = -1.0; rows < 1.0; rows += increment_rows){
			glVertex2f(rows, -1.0);
			glVertex2f(rows, 1.0);
		}
		
		glEnd();
	}
	
	void writePixel(int x, int y){
		// First, we check if the coordinates are inside the grid
		if (checkPoint(x, y)){
			float translated_x = (float)x / (float)(n_rows / 2);
			float translated_y = (float)y / (float)(n_columns / 2);
			
			glPointSize(10);
			glColor3f(0.0, 0.0, 0.0); // black
			
			glBegin(GL_POINTS);
			glVertex2f(translated_x, translated_y);
			glEnd();
		}
		else{
			cout << "Wrong coordinates, nothing will be drawn" << endl;
		}
	}
	
	void drawLine(int begin_x, int begin_y, int end_x, int end_y){
		if (checkPoint(begin_x, begin_y) && checkPoint(end_x, end_y)){
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
	
	void ajuste(double x, double y, int &t_x, int &t_y){
		double t1_x = x * (n_rows / 2);
		double t1_y = y * (n_columns / 2);
		
		int abajoX = t1_x;
		int abajoY = t1_y;
		
		int arribaX = abajoX + 1;
		int arribaY = abajoY + 1;
		
		double dabajoX = abajoX * 1.0;
		double dabajoY = abajoY * 1.0;
		
		double darribaX = arribaX * 1.0;
		double darribaY = arribaY * 1.0;
		
		if ((dabajoX) >= (darribaX)){
			t_x = darribaX;
		}
		else{
			t_x = dabajoX;
		}
		
		if ((dabajoY) >= (darribaY)){
			t_y = darribaY;
		}
		else{
			t_y = dabajoY;
		}
	}
};

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments){
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta); //precalculate the sine and cosine
	float s = sinf(theta);
	float t;
	float x = 1; //we start at angle = 0
	float y = 0;
	
	glBegin(GL_LINE_LOOP);
	
	for (int ii = 0; ii < num_segments; ii++){
		//apply radius and offset
		glVertex2f(x * rx + cx, y * ry + cy); //output vertex
											  //apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}

bool tercer_cuadrante(int x, int y, float cx, float cy){
	if (x < cx && y <= cy){
		return true;
	}
	else{
		return false;
	}
}

void DrawPoints(CartesianGridTra &grid, float cx, float cy, float rx, float ry, int num_segments){
	map<int, int> puntos;
	
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta); //precalculate the sine and cosine
	float s = sinf(theta);
	float t;
	float x = 1; //we start at angle = 0
	float y = 0;
	
	for (int ii = 0; ii < num_segments; ii++){
		//apply radius and offset
		int t_x, t_y;
		
		grid.ajuste(x * rx + cx, y * ry + cy, t_x, t_y); //output vertex
		
		if (tercer_cuadrante(t_x, t_y, cx, cy)){
			grid.writePixel(t_x, t_y);
		}
		
		if (puntos.find(t_y) != puntos.end()){
			int principio, fin;
			
			if (puntos[t_y] <= t_x){
				principio = puntos[t_y];
				fin = t_x;
			}
			else{
				principio = t_x;
				fin = puntos[t_y];
			}
			
			cout << principio << "		" << fin << endl;
			
			for (int k = principio; k <= fin; k++){
				if (tercer_cuadrante(k, t_y, cx, cy))
					grid.writePixel(k, t_y);
			}
		}
		else{
			puntos[t_y] = t_x;
		}
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
}

void Display2(){
	int n_rows = 24;
	int n_columns = 24;
	CartesianGridTra grid(n_rows, n_columns);
	grid.drawGrid();
	
	double centroX = 0;
	double centroY = 0;
	double altura = 1;
	double anchura = 0.6;
	
	DrawEllipse(centroX, centroY, altura, anchura, 60);
	DrawPoints(grid, centroX, centroY, altura, anchura, 60);
}

bool InsidePolygon2(vector<pair<int, int>> polygon, int N, pair<int, int> p){
	int counter = 0;
	int i;
	double xinters;
	pair<int, int> p1, p2;
	
	p1 = polygon[0];
	
	for (i = 1; i <= N; i++){
		p2 = polygon[i % N];
		
		if (p.second > MIN(p1.second, p2.second)){
			if (p.second <= MAX(p1.second, p2.second)){
				if (p.first < MAX(p1.first, p2.first)){
					if (p1.second != p2.second){
						xinters = (p.second - p1.second) * (p2.first - p1.first) / (p2.second - p1.second) + p1.first;
						if (p1.first == p2.first || p.first <= xinters)
							counter++;
					}
				}
			}
		}
		
		p1 = p2;
	}
	
	if (counter % 2 == 0){
		return (false);
	}
	else{
		return (true);
	}
}

bool InsidePolygon1(vector<pair<int, int>> polygon, int N, pair<int, int> p){
	int counter = 0;
	int i;
	double xinters;
	pair<int, int> p1, p2;
	
	p1 = polygon[0];
	
	for (i = 0; i <= N; i++){
		p2 = polygon[i % N];
		if (p.second > MIN(p1.second, p2.second)){
			if (p.second <= MAX(p1.second, p2.second)){
				if (p.first <= MAX(p1.first, p2.first)){
					if (p1.second != p2.second){
						xinters = (p.second - p1.second) * (p2.first - p1.first) / (p2.second - p1.second) + p1.first;
						if (p1.first == p2.first || p.first <= xinters)
							counter++;
					}
				}
			}
		}
		
		p1 = p2;
	}
	
	if (counter % 2 == 0){
		return (false);
	}
	else{
		return (true);
	}
}

void Display3(){
	int n_rows = 24;
	int n_columns = 24;
	CartesianGridTra grid(n_rows, n_columns);
	grid.drawGrid();
	list< pair<int, int> > myset;
	
	ifstream fe("archivo.txt");
	string ta;
	getline(fe, ta);
	
	stringstream sta;
	sta.str(ta);
	
	int tamanyo;
	sta >> tamanyo;
	
	for (int i = 0; i < tamanyo; i++){
		string t;
		getline(fe, t);
		
		stringstream ss;
		ss.str(t);
		
		int x;
		ss >> x;
		
		int y;
		ss >> y;
		
		cout << x << "		" << y << endl;
		pair<int, int> p(x, y);
		myset.push_back(p);
	}
	
	list<pair<int, int>>::iterator it;
	list<pair<int, int>>::iterator fin = myset.end();
	fin--;
	
	for (it = myset.begin(); it != fin; it++){
		list<pair<int, int>>::iterator sig = it;
		sig++;
		
		grid.drawLine((*it).first, (*it).second, (*sig).first, (*sig).second);
		grid.writePixel((*it).first, (*it).second);
	}
	
	grid.writePixel((*it).first, (*it).second);
	grid.drawLine((*it).first, (*it).second, (*myset.begin()).first, (*myset.begin()).second);
	
	vector<pair<int, int>> v(myset.begin(), myset.end());
	
	for (int x1 = -grid.getColumns(); x1 <= grid.getColumns(); x1++){
		for (int y1 = -grid.getRows(); y1 <= grid.getRows(); y1++){
			pair<int, int> p1(x1, y1);
			
			if (InsidePolygon1(v, (int)v.size(), p1) or InsidePolygon2(v, (int)v.size(), p1)){
				grid.writePixel(x1, y1);
			}
		}
	}
}

void Init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glLineWidth(1);
	
	//   glPointSize(4);
	
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	switch (prevKey){
		case '1':
			Display1();
			break;
		case '2':
			Display2();
			break;
		case '3':
			Display3();
			break;
	}
	glFlush();
}

void Reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y){
	prevKey = key;
	
	if (key == 27) // escape
		exit(0);
	
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y){
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	
	glutInitWindowSize(dim, dim);
	
	glutInitWindowPosition(100, 100);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutCreateWindow(argv[0]);
	
	Init();
	
	glutReshapeFunc(Reshape);
	
	glutKeyboardFunc(KeyboardFunc);
	
	glutMouseFunc(MouseFunc);
	
	glutDisplayFunc(Display);
	
	glutMainLoop();
	
	return 0;
}
