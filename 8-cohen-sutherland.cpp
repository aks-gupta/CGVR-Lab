#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

#define outcode int
#define true 1
#define false 0

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;
int nl;
double xs[100], ys[100], xe[100], ye[100];

const int TOP = 1, BOTTOM = 2, RIGHT = 4, LEFT = 8; //TBRL

outcode computeoutcode(double x, double y)
{
	outcode code = 0;
	if (y > ymax)
		code |= TOP;
	else if (y < ymin)
		code |= BOTTOM;
	if (x > xmax)
		code |= RIGHT;
	else if (x < xmin)
		code |= LEFT;

	return code;
}

void cohensuther(double x0, double y0, double x1, double y1)
{
	outcode outcode0, outcode1, outcodeout;
	bool accept = false, done = false;

	outcode0 = computeoutcode(x0, y0);
	outcode1 = computeoutcode(x1, y1);

	do
	{
		if (!(outcode0 | outcode1))
		{
			accept = true;
			done = true;
		}
		else if (outcode0 & outcode1)
			done = true;
		else
		{
			double x, y;
			outcodeout = outcode0 ? outcode0 : outcode1;
			if (outcodeout & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (outcodeout & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (outcodeout & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (outcodeout == outcode0)
			{
				x0 = x;
				y0 = y;
				outcode0 = computeoutcode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				outcode1 = computeoutcode(x1, y1);
			}
		}

	} while (!done);

	if (accept)
	{
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;


		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for (int i = 0; i < nl; i++) {
		glVertex2d(xs[i], ys[i]);
		glVertex2d(xe[i], ye[i]);
	}
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin, yvmin);
	glVertex2f(xvmax, yvmin);
	glVertex2f(xvmax, yvmax);
	glVertex2f(xvmin, yvmax);
	glEnd();

	for (int i = 0; i < nl; i++)
		cohensuther(xs[i], ys[i], xe[i], ye[i]);

	glFlush();
}
void myinit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	cout << "Enter the number of lines: ";
	cin >> nl;
	for (int i = 0; i < nl; i++) {
		cout << "Enter the coordinates x1 y1 x2 y2:\n";
		cin >> xs[i] >> ys[i];
		cin >> xe[i] >> ye[i];
	}
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("clip");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
