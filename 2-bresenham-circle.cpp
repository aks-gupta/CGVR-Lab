#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int xc = 0, yc = 0, xr, yr, r = 100;

void drawCircle(int xc, int yc, int x, int y) {
	glColor3f(0, 0, 1);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc - y, yc - x);
	glEnd();
}

void bresCircle(int xc, int yc, int r) {
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x < y) {
		drawCircle(xc, yc, x, y);
		x++;
		if (d < 0)
			d += 4 * x + 6;
		else {
			y--;
			d += 4 * (x - y) + 10;
		}
		drawCircle(xc, yc, x, y);
	}
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawCircleK() {
	bresCircle(xc, yc, r);
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xc = x - WINDOW_WIDTH / 2;
		yc = WINDOW_HEIGHT / 2 - y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		xr = x - WINDOW_WIDTH / 2;
		yr = WINDOW_HEIGHT / 2 - y;
		r = sqrt((float)(pow(xc - xr, 2) + pow(yc - yr, 2)));
		cout << "Circle with center at (" << xc << "," << yc << ") and radius " << r << endl;
		bresCircle(xc, yc, r);
	}
}

int main(int argc, char* argv[]) {
	int choice;
	std::cout << "Press:\n1. Keyboard\n2. Mouse\n3. Default\n";
	std::cin >> choice;
	if (choice == 1)
	{
		std::cout << "Enter xc : ";
		std::cin >> xc;
		std::cout << "Enter yc : ";
		std::cin >> yc;
		std::cout << "Enter radius : ";
		std::cin >> r;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Bresenham Circle Drawing");
	glutDisplayFunc(drawCircleK);
	if (choice == 2) {
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		myInit();
	}
	else {
		//glutDisplayFunc(display);
		glutDisplayFunc(drawCircleK);
		myInit();
	}
	glutMainLoop();
	return 0;
}
