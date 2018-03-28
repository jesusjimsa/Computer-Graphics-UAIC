#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// the size of the window measured in pixels
#define dim 300

// the maximum number of iterations for the Julia-Fatou set membership testing
#define NRITER_JF 5000

// the maximum value of M for the Julia-Fatou set membership testing
#define MODMAX_JF 10000000

// increments used in CJuliaFatou
#define RX_JF 0.01
#define RY_JF 0.01

using namespace std;

unsigned char prevKey;
int level = 0;

class CComplex{
public:
	CComplex() : re(0.0), im(0.0){
		
	}
	
	CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0){
		
	}
	
	CComplex(const CComplex &c) : re(c.re), im(c.im){
		
	}
	
	~CComplex(){
		
	}
	
	CComplex &operator=(const CComplex &c){
		re = c.re;
		im = c.im;
		
		return *this;
	}
	
	double getRe(){
		return re;
	}
	
	void setRe(double re1){
		re = re1;
	}
	
	double getIm(){
		return im;
	}
	
	void setIm(double im1) {
		im = im1;
	}
	
	double getMod() {
		return sqrt(re * re + im * im);
	}
	
	int operator==(CComplex &c1){
		return ((re == c1.re) && (im == c1.im));
	}
	
	CComplex pow2(){
		CComplex rez;
		rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
		rez.im = 2.0 * re * im;
		return rez;
	}
	
	friend CComplex operator+(const CComplex &c1, const CComplex &c2);
	friend CComplex operator*(CComplex &c1, CComplex &c2);
	
	void print(FILE *f){
		fprintf(f, "%.20f%+.20f i", re, im);
	}
	
private:
	double re, im;
};

CComplex operator+(const CComplex &c1, const CComplex &c2) {
	CComplex rez(c1.re + c2.re, c1.im + c2.im);
	
	return rez;
}

CComplex operator*(CComplex &c1, CComplex &c2) {
	CComplex rez(c1.re * c2.re - c1.im * c2.im, c1.re * c2.im + c1.im * c2.re);
	
	return rez;
}

class CJuliaFatou {
public:
	CJuliaFatou(){
		// m.c is initialized by default with 0+0i
		
		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}
	
	CJuliaFatou(CComplex &c){
		m.c = c;
		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}
	
	~CJuliaFatou(){
		
	}
	
	void setmodmax(double v){
		assert(v <= MODMAX_JF); m.modmax = v;
	}
	
	double getmodmax(){
		return m.modmax;
	}
	
	void setnriter(int v){
		assert(v <= NRITER_JF); m.nriter = v;
	}
	
	int getnriter() {
		return m.nriter;
	}
	
	// it tests if x belongs to the Julia-Fatou set Jc
	// it returns 0 if yes, -1 for finite convergence, +1 for infinite convergence
	int isIn(CComplex &x){
		int rez = 0;
		// an array for storing the values for computing z_n+1 = z_n * z_n + c
		CComplex z0,z1;
		
		z0 = x;
		
		for (int i = 1; i < m.nriter; i++){
			z1 = z0 * z0 + m.c;
			
			if (z1 == z0){
				// x does not belong to the J-F set because the
				// iterative process converges finitely
				rez = -1;
				
				break;
			}
			else{
				if (z1.getMod() > m.modmax){
					// x does not belong to the J-F set because the
					// iterative process converges infinitely
					rez = 1;
					
					break;
				}
			}
			
			z0 = z1;
		}
		
		return rez;
	}
	
	// it displays a J-F set
	void display(double xmin, double ymin, double xmax, double ymax){
		glPushMatrix();
		glLoadIdentity();
		
		glBegin(GL_POINTS);
		
		for(double x = xmin; x <= xmax; x += RX_JF){
			for(double y = ymin; y <= ymax; y += RY_JF){
				CComplex z(x, y);
				int r = isIn(z);
				
				if (r == 0){
					glVertex3d(x,y,0);
				}
				else{
					if (r == -1){
					}
					else{
						if (r == 1){
						}
					}
				}
			}
		}
		
		fprintf(stdout, "STOP\n");
		
		glEnd();
		
		glPopMatrix();
	}
	
private:
	struct SDate{
		CComplex c;
		
		// number of iterations
		int nriter;
		
		// the maximum value of M
		double modmax;
	} m;
};

// Mandelbrot set
class Mandelbrot{
private:
	struct SDate{
		CComplex c;
		
		// number of iterations
		int nriter;
		
		// the maximum value of M
		double modmax;
	} m;
public:
	Mandelbrot(){
		// m.c is initialized by default with 0+0i
		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}
	
	Mandelbrot(CComplex &c){
		m.c = c;
		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}
	
	~Mandelbrot(){
		
	}
	
	void setmodmax(double v){
		assert(v <= MODMAX_JF); m.modmax = v;
	}
	
	double getmodmax(){
		return m.modmax;
	}
	
	void setnriter(int v){
		assert(v <= NRITER_JF); m.nriter = v;
	}
	
	int getnriter() {
		return m.nriter;
	}
	
	// it tests if x belongs to the Mandelbrot set
	// it returns 0 if yes, -1 for finite convergence, +1 for infinite convergence
	int isIn(CComplex &x){
		int rez = 0;
		// an array for storing the values for computing z_n+1 = z_n * z_n + c
		CComplex z0, z1;
		bool first = true;
		
		z0 = CComplex();
		
		for (int i = 1; i < m.nriter; i++){
			if(first){
				z1 = CComplex();	// z1 = 0.0 + 0.0i
				first = false;
			}
			else{
				z1 = (z0 * z0) + x;
			}
			
			if(z1.getMod() > m.modmax){
				rez = 1;
				
				break;
			}
			
			z0 = z1;
		}
		
		return rez;
	}
	
	void display(double xmin, double ymin, double xmax, double ymax){
		int r;
		
		glPushMatrix();
		glLoadIdentity();
		
		glBegin(GL_POINTS);
		
		for(double x = xmin; x <= xmax; x += RX_JF){
			for(double y = ymin; y <= ymax; y += RY_JF){
				CComplex z(x, y);
				r = isIn(z);
				
				if(r == 0){
					glVertex3d(x / 2, y / 2, 0);
				}
				else{
					glColor3f(0.001, 0.001, 0.001); // black
					
					glVertex3d(x, y, 0);
					
					glColor3f(1.0, 0.0, 0.0); // red
				}
			}
		}
		
		glEnd();
		
		glPopMatrix();
	}
};

class C2coord{
public:
	C2coord(){
		m.x = m.y = 0;
	}
	
	C2coord(double x, double y){
		m.x = x;
		m.y = y;
	}
	
	C2coord(const C2coord &p){
		m.x = p.m.x;
		m.y = p.m.y;
	}
	
	C2coord &operator=(C2coord &p){
		m.x = p.m.x;
		m.y = p.m.y;
		return *this;
	}
	
	int operator==(C2coord &p){
		return ((m.x == p.m.x) && (m.y == p.m.y));
	}
	
protected:
	struct SDate{
		double x,y;
	} m;
};

class CPunct : public C2coord{
public:
	CPunct() : C2coord(0.0, 0.0){
		
	}
	
	CPunct(double x, double y) : C2coord(x, y){
		
	}
	
	CPunct &operator=(const CPunct &p){
		m.x = p.m.x;
		m.y = p.m.y;
		return *this;
	}
	
	void getxy(double &x, double &y){
		x = m.x;
		y = m.y;
	}
	
	int operator==(CPunct &p){
		return ((m.x == p.m.x) && (m.y == p.m.y));
	}
	
	void mark(){
		glBegin(GL_POINTS);
		
		glVertex2d(m.x, m.y);
		
		glEnd();
	}
	
	void print(FILE *fis){
		fprintf(fis, "(%+f,%+f)", m.x, m.y);
	}
	
};

class CVector : public C2coord{
public:
	CVector() : C2coord(0.0, 0.0){
		normalization();
	}
	
	CVector(double x, double y) : C2coord(x, y){
		normalization();
	}
	
	CVector &operator=(CVector &p){
		m.x = p.m.x;
		m.y = p.m.y;
		return *this;
	}
	
	int operator==(CVector &p){
		return ((m.x == p.m.x) && (m.y == p.m.y));
	}
	
	CPunct getDest(CPunct &orig, double length){
		double x, y;
		
		orig.getxy(x, y);
		CPunct p(x + m.x * length, y + m.y * length);
		
		return p;
	}
	
	void rotate(double degrees){
		double x = m.x;
		double y = m.y;
		double t = 2 * (4.0 * atan(1.0)) * degrees / 360.0;
		
		m.x = x * cos(t) - y * sin(t);
		m.y = x * sin(t) + y * cos(t);
		normalization();
	}
	
	void draw(CPunct p, double length){
		double x, y;
		
		p.getxy(x, y);
		
		glColor3f(1.0, 0.1, 0.1);
		glBegin(GL_LINE_STRIP);
		
		glVertex2d(x, y);
		glVertex2d(x + m.x * length, y + m.y * length);
		
		glEnd();
	}
	
	void print(FILE *fis){
		fprintf(fis, "%+fi %+fj", C2coord::m.x, C2coord::m.y);
	}
	
private:
	// it is used for normalizing a vector
	void normalization(){
		double d = sqrt(C2coord::m.x * C2coord::m.x + C2coord::m.y * C2coord::m.y);
		if (d != 0.0){
			C2coord::m.x = C2coord::m.x * 1.0 / d;
			C2coord::m.y = C2coord::m.y * 1.0 / d;
		}
	}
};

class CKochCurve{
public:
	void segmentKoch(double length, int level, CPunct &p, CVector v){
		CPunct p1;
		
		if (level == 0){
			v.draw(p, length);
		}
		else{
			segmentKoch(length / 3.0, level - 1, p, v);
			p1 = v.getDest(p, length / 3.0);
			
			v.rotate(60);
			segmentKoch(length / 3.0, level - 1, p1, v);
			p1 = v.getDest(p1, length / 3.0);
			
			v.rotate(-120);
			segmentKoch(length / 3.0, level - 1, p1, v);
			p1 = v.getDest(p1, length / 3.0);
			
			v.rotate(60);
			segmentKoch(length / 3.0, level - 1, p1, v);
		}
	}
	
	void display(double length, int level){
		CVector v1(sqrt(3.0)/2.0, 0.5);
		CPunct p1(-1.0, 0.0);
		
		CVector v2(0.0, -1.0);
		CPunct p2(0.5, sqrt(3.0)/2.0);
		
		CVector v3(-sqrt(3.0)/2.0, 0.5);
		CPunct p3(0.5, -sqrt(3.0)/2.0);
		
		segmentKoch(length, level, p1, v1);
		segmentKoch(length, level, p2, v2);
		segmentKoch(length, level, p3, v3);
	}
};

class CBinaryTree{
public:
	void binaryTree(double length, int level, CPunct &p, CVector v){
		CPunct p1;
		
		if (level == 0){
			v.draw(p, length);
		}
		else{
			binaryTree(length, level - 1, p, v);
			p1 = v.getDest(p, length);
			
			v.rotate(-45);
			binaryTree(length / 2.0, level - 1, p1, v);
			
			v.rotate(90);
			binaryTree(length / 2.0, level - 1, p1, v);
		}
	}
	
	void display(double length, int level){
		CVector v(0.0, -1.0);
		CPunct p(0.0, 1.0);
		
		binaryTree(length, level, p, v);
	}
};

class CPerronTree{
public:
	void arborePerron(double length, int level, double division_factor, CPunct p, CVector v){
		assert(division_factor != 0);
		CPunct p1, p2;
		
		if (level == 0){
		}
		else{
			v.rotate(30);
			v.draw(p, length);
			p1 = v.getDest(p, length);
			arborePerron(length * division_factor, level - 1, division_factor, p1, v);
			
			v.rotate(-90);
			v.draw(p, length);
			p1 = v.getDest(p, length);
			p2 = p1;
			
			v.rotate(-30);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			arborePerron(length * division_factor, level - 1, division_factor, p1, v);
			
			p1 = p2;
			v.rotate(90);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			p2 = p1;
			
			v.rotate(30);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			arborePerron(length * division_factor, level - 1, division_factor, p1, v);
			
			p1 = p2;
			v.rotate(-90);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			arborePerron(length * division_factor, level - 1, division_factor, p1, v);
		}
	}
	
	void display(double length, int level){
		CVector v(0.0, 1.0);
		CPunct p(0.0, -1.0);
		
		v.draw(p, 0.25);
		p = v.getDest(p, 0.25);
		arborePerron(length, level, 0.4, p, v);
	}
};



class CHilbertCurve{
public:
	void HilbertCurve(double length, int level, CPunct &p, CVector &v, int d){
		if (level == 0){
		}
		else{
			v.rotate(d * 90);
			HilbertCurve(length, level - 1, p, v, -d);
			
			v.draw(p, length);
			p = v.getDest(p, length);
			
			v.rotate(-d * 90);
			HilbertCurve(length, level - 1, p, v, d);
			
			v.draw(p, length);
			p = v.getDest(p, length);
			
			HilbertCurve(length, level - 1, p, v, d);
			
			v.rotate(-d * 90);
			v.draw(p, length);
			p = v.getDest(p, length);
			
			HilbertCurve(length, level - 1, p, v, -d);
			
			v.rotate(d * 90);
		}
	}
	
	void display(double length, int level){
		CVector v(0.0, 1.0);
		CPunct p(0.0, 0.0);
		
		HilbertCurve(length, level, p, v, 1);
	}
};

class CSquares{
public:
	void drawSquare(float tam, float cx, float cy){
		glBegin(GL_LINE_STRIP);
		
		glVertex2f(cx - tam, cy + tam);
		glVertex2f(cx + tam, cy + tam);
		
		glVertex2f(cx + tam, cy + tam);
		glVertex2f(cx + tam, cy - tam);
		
		glVertex2f(cx + tam, cy - tam);
		glVertex2f(cx - tam, cy - tam);
		
		glVertex2f(cx - tam, cy - tam);
		glVertex2f(cx - tam, cy + tam);
		
		glEnd();
	}
	
	void prepareSquares(float tam, float cx, float cy, int level){
		if(level >= 0){
			float sep = (tam / 2) + (tam / 6) + 1.5 * tam;
			
			tam = tam / 3;
			
			drawSquare(tam,cx+sep ,cy);
			
			if(level > 1){
				prepareSquares(tam, cx + sep, cy, level - 1);
			}
			
			drawSquare(tam, cx + sep, cy + sep);
			
			if(level > 1){
				prepareSquares(tam, cx + sep, cy + sep, level - 1);
			}
			
			drawSquare(tam, cx, cy + sep);
			
			if(level > 1){
				prepareSquares(tam, cx, cy + sep, level - 1);
			}
			
			drawSquare(tam, cx - sep, cy + sep);
			
			if(level > 1){
				prepareSquares(tam, cx - sep, cy + sep, level - 1);
			}
			
			drawSquare(tam, cx - sep, cy);
			
			if(level > 1){
				prepareSquares(tam, cx - sep, cy, level - 1);
			}
			
			drawSquare(tam, cx - sep, cy - sep);
			
			if(level > 1){
				prepareSquares(tam, cx - sep, cy - sep, level - 1);
			}
			
			drawSquare(tam, cx, cy - sep);
			
			if(level > 1){
				prepareSquares(tam, cx, cy - sep, level - 1);
			}
			
			drawSquare(tam,cx+sep,cy-sep);
			
			if(level > 1){
				prepareSquares(tam,cx+sep,cy-sep,level-1);
			}
		}
	}
	
	void squares(double lungime, int nivel, CPunct &p, CVector &v, int d){
		if (nivel != 0){
			drawSquare(0.3, 0.0, 0.0);
			prepareSquares(0.3, 0.0, 0.0, nivel);
		}
	}
	
	void afisare(double lungime, int nivel){
		CVector v(0.0, 1.0);
		CPunct p(0.0, 0.0);
		
		squares(lungime, nivel, p, v, 1);
	}
};



class CHalfHex{
public:
	void mediohexagonup(double x1, double y1, double x2, double y2, int level){
		double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		double radius = length / 2;
		double first_x, first_y, second_x, second_y;
		
		CPunct c1(x1, y1);
		CPunct c2(x2, y2);
		CVector v1(x2 - x1, y2 - y1);
		v1.rotate(60);
		CPunct p1 = v1.getDest(c1, radius);
		
		p1.getxy(first_x, first_y);
		
		CVector v2(x2 - x1, y2 - y1);
		v2.rotate(120);
		CPunct p2 = v2.getDest(c2, radius);
		
		p2.getxy(second_x, second_y);
		
		if (level == 1){
			glBegin(GL_LINE_STRIP);
			glColor3f(1.0, 0.1, 0.1);
			
			glVertex2f(x2, y2);
			glVertex2f(second_x, second_y);
			
			glVertex2f(second_x, second_y);
			glVertex2f(first_x, first_y);
			
			glVertex2f(first_x, first_y);
			glVertex2f(x1, y1);
			
			glEnd();
		}
		else{
			mediohexagonup(x2, y2, second_x, second_y, level - 1);
			mediohexagondown(second_x, second_y, first_x, first_y, level - 1);
			mediohexagonup(first_x, first_y, x1, y1, level - 1);
		}
	}
	
	void mediohexagondown(double x1, double y1, double x2, double y2, int level){
		double longitud = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		double radio = longitud / 2;
		
		double first_x, first_y, second_x, second_y;
		CPunct c1(x1, y1);
		CPunct c2(x2, y2);
		CVector v1(x2 - x1, y2 - y1);
		
		v1.rotate(300);
		CPunct p1 = v1.getDest(c1, radio);
		p1.getxy(first_x, first_y);
		
		CVector v2(x2 - x1, y2 - y1);
		v2.rotate(240);
		CPunct p2 = v2.getDest(c2, radio);
		
		p2.getxy(second_x, second_y);
		
		if (level == 1){
			glBegin(GL_LINE_STRIP);
			glColor3f(1.0, 0.1, 0.1);
			
			glVertex2f(x2, y2);
			glVertex2f(second_x, second_y);
			
			glVertex2f(second_x, second_y);
			glVertex2f(first_x, first_y);
			
			glVertex2f(first_x, first_y);
			glVertex2f(x1, y1);
			
			glEnd();
		}
		else{
			mediohexagondown(x2, y2, second_x, second_y, level - 1);
			mediohexagonup(second_x, second_y, first_x, first_y, level - 1);
			mediohexagondown(first_x, first_y, x1, y1, level - 1);
		}
	}
	
	void halfHex(double length, int level, CPunct &p, CVector &v, int d){
		if (level == 0){
			glBegin(GL_LINE_STRIP);
			glColor3f(1.0, 0.1, 0.1);
			
			glVertex2f(-0.5, 0.5);
			glVertex2f(-0.5, -0.5);
			
			glEnd();
		}
		else{
			mediohexagonup(-0.5, 0.5, -0.5, -0.5, level);
		}
	}
	
	void draw(double lungime, int nivel){
		CVector v(0.0, 1.0);
		CPunct p(0.0, 0.0);
		
		halfHex(lungime, nivel, p, v, 1);
	}
};

class NewFractalTree{
public:
	void FractalTree(double length, int level, double division_factor, CPunct p, CVector v){
		assert(division_factor != 0);
		CPunct p1, p2;
		
		if (level != 0){
			v.rotate(-30);
			v.draw(p, length);
			p1 = v.getDest(p, length);
			FractalTree(length * division_factor, level - 1, division_factor, p1, v);
			
			v.rotate(90);
			v.draw(p, length);
			p1 = v.getDest(p, length);
			p2 = p1;
			
			v.rotate(30);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			FractalTree(length * division_factor, level - 1, division_factor, p1, v);
			
			p1 = p2;
			v.rotate(-45);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			p2 = p1;
			
			v.rotate(-30);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			FractalTree(length * division_factor, level - 1, division_factor, p1, v);
			
			p1 = p2;
			v.rotate(90);
			v.draw(p1, length);
			p1 = v.getDest(p1, length);
			FractalTree(length * division_factor, level - 1, division_factor, p1, v);
		}
	}
	
	void display(double length, int level){
		CVector v(0.0, -1.0);
		CPunct p(0.0, 3.0);
		
		v.draw(p, 0.25);
		p = v.getDest(p, 0.25);
		FractalTree(length, level, 0.4, p, v);
	}
};

// displays the Koch snowflake
void Display1(){
	CKochCurve cck;
	cck.display(sqrt(3.0), level);
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'K');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');
	
	level++;
}

// displays a binary tree
void Display2(){
	CBinaryTree cab;
	cab.display(1, level);
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	
	level++;
}

// displays a fractal tree
void Display3(){
	CPerronTree cap;
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	
	glPushMatrix();
	glLoadIdentity();
	glScaled(0.4, 0.4, 1);
	glTranslated(-0.5, -0.5, 0.0);
	cap.display(1, level);
	glPopMatrix();
	level++;
}

// displays the Hilbert curve
void Display4(){
	CHilbertCurve cch;
	cch.display(0.05, level);
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	
	level++;
}

void Display5(){
	CSquares cch;
	cch.afisare(0.05, level);
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'q');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');
	
	level++;
}

// displays fractal tree
void Display6(){
	NewFractalTree tree;
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98,-0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0,-0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'f');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	
	glPushMatrix();
	glLoadIdentity();
	glScaled(0.4, 0.4, 1);
	glTranslated(-0.5, -0.5, 0.0);
	tree.display(1, level);
	glPopMatrix();
	level++;
}

void Display7(){
	CHalfHex cch;
	cch.draw(0.05, level);
	
	char c[3];
	sprintf(c, "%2d", level);
	
	glRasterPos2d(-0.98, -0.98);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);
	
	glRasterPos2d(-1.0, -0.9);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'f');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'x');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'g');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	
	level++;
}

// Julia-Fatou set for z0 = 0 and c = -0.12375+0.056805i
void Display8() {
	CComplex c(-0.12375, 0.056805);
	CJuliaFatou cjf(c);
	
	glColor3f(1.0, 0.1, 0.1);
	cjf.setnriter(30);
	cjf.display(-0.8, -0.4, 0.8, 0.4);
}

// Julia-Fatou set for z0 = 0 and c = -0.012+0.74i
void Display9() {
	CComplex c(-0.012, 0.74);
	CJuliaFatou cjf(c);
	
	glColor3f(1.0, 0.1, 0.1);
	cjf.setnriter(30);
	cjf.display(-1, -1, 1, 1);
}

void DisplayQ(){
	CComplex c(-0.012, 0.74);
	Mandelbrot mandel(c);
	
	glColor3f(1.0, 0.1, 0.1);
	mandel.setnriter(30);
	mandel.display(-2, -2, 2, 2);
}

void Init(void) {
	glClearColor(1.0,1.0,1.0,1.0);
	
	glLineWidth(1);
	
	glPointSize(1);
	
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void){
	switch(prevKey){
		case '0':
			glClear(GL_COLOR_BUFFER_BIT);
			level = 0;
			fprintf(stderr, "level = %d\n", level);
			
			break;
		case '1':
			glClear(GL_COLOR_BUFFER_BIT);
			Display1();
			
			break;
		case '2':
			glClear(GL_COLOR_BUFFER_BIT);
			Display2();
			
			break;
		case '3':
			glClear(GL_COLOR_BUFFER_BIT);
			Display3();
			
			break;
		case '4':
			glClear(GL_COLOR_BUFFER_BIT);
			Display4();
			
			break;
		case '5':
			glClear(GL_COLOR_BUFFER_BIT);
			Display5();
			
			break;
		case '6':
			glClear(GL_COLOR_BUFFER_BIT);
			Display6();
			
			break;
		case '7':
			glClear(GL_COLOR_BUFFER_BIT);
			Display7();
			
			break;
		case '8':
			glClear(GL_COLOR_BUFFER_BIT);
			Display8();
			
			break;
		case '9':
			glClear(GL_COLOR_BUFFER_BIT);
			Display9();
			
			break;
		case 'q':
			glClear(GL_COLOR_BUFFER_BIT);
			DisplayQ();
			
			break;
		default:
			break;
	}
	
	glFlush();
}

void Reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y){
	prevKey = key;
	
	if (key == 27){
		exit(0);
	}
	
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


