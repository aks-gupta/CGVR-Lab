#include <GL/glut.h>
// #include <unistd.h>

void draw_pixel(GLint cx, GLint cy)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}

void plotpixels(GLint xc, GLint yc, GLint x, GLint y)
{
	draw_pixel(xc + x, yc + y);
	draw_pixel(xc + x, yc - y);
	draw_pixel(xc - x, yc + y);
	draw_pixel(xc - x, yc - y);
	draw_pixel(xc + y, yc + x);
	draw_pixel(xc + y, yc - x);
	draw_pixel(xc - y, yc + x);
	draw_pixel(xc - y, yc - x);
}

void Circle_draw(GLint xc, GLint yc, GLint r)  // Midpoint Circle Drawing Algorithm
{
	int x = 0, y = r;
	int d = 3 - 2 * r; //decision parameter
	while (x <= y) { //45-90 octant
		plotpixels(xc, yc, x, y);
		x++;
		if (d < 0) {
			d += 4 * x + 6;
		}
		else {
			y--;
			d += 4 * (x - y) + 10;
		}
		plotpixels(xc, yc, x, y);
	}
	glFlush();
}

void Cylinder_draw()
{
	GLint xc = 100, yc = 100, r = 50, i, n = 50;

	for (i = 0; i < n; i += 3)
		Circle_draw(xc, yc + i, r);
	for (i = r; i > 0; i--)
		Circle_draw(xc, yc + n, i);
}

void rectangle(int x1, int x2, int y1, int y2)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}

void parallelepiped_draw()
{
	int x1 = 200, x2 = 300, y1 = 100, y2 = 175, i, j, n = 40;
	for (i = 0; i < n; i += 2)
		rectangle(x1 + i, x2 + i, y1 + i, y2 + i);
	for (int i = 0; i < x2-x1; i++)
		rectangle(x1 + n, x2 + n - i, y1 + n, y2 + n);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	parallelepiped_draw();
	glFlush();
}

void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	Cylinder_draw();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	int id1 = glutCreateWindow("Cylinder");
	glutSetWindow(id1);
	glutDisplayFunc(display1);
	init();
	glutInitWindowPosition(500, 100);
	int id2 = glutCreateWindow("Parallelepiped");
	glutSetWindow(id2);
	glutDisplayFunc(display2);
	init();
	glutMainLoop();
}
