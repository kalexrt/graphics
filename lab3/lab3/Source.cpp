#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

using namespace std;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-400.0, 400.0, -400.0, 400.0);
}


// Circle co-ordinates generator
void display_circle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	cout << "Enter the value for circle \n";
	float x0, y0, r;

	cout << "Enter x co-ordinate of center";
	cin >> x0;

	cout << "Enter y co-ordinate of center";
	cin >> y0;

	cout << "Enter the value of the radius: ";
	cin >> r;

	float x = 0;
	float y = r;
	float pk = (float)5 / (float)4 - r;

	do {
		if (pk < 0) {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + y, y0 + x);
			glVertex2f(x0 - x, y0 - y);
			glVertex2f(x0 - y, y0 - x);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - y, y0 + x);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 + y, y0 - x);
			glEnd();
			glFlush();
			x = x + 1;
			pk = pk + 2 * x + 1;
		}
		else {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + y, y0 + x);
			glVertex2f(x0 - x, y0 - y);
			glVertex2f(x0 - y, y0 - x);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - y, y0 + x);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 + y, y0 - x);
			glEnd();
			glFlush();
			x = x + 1;
			y = y - 1;
			pk = pk + 2 * x + 1 - 2 * y;
		}
	} while (x < y);
}
void display_ellipse() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	cout << "Enter the value for ellipse \n";

	float x0, y0, rx, ry;

	cout << "Enter x co-ordinate of center";
	cin >> x0;

	cout << "Enter y co-ordinate of center";
	cin >> y0;

	cout << "Enter the value of the radius x: ";
	cin >> rx;
	cout << "Enter the value of the radius y: ";
	cin >> ry;

	float x = 0;
	float y = ry;
	float p1 = ry * ry - rx * rx * ry + (rx * rx / 4);

	while ((2 * ry * ry * x) <= (2 * rx * rx * y)) {
		if (p1 < 0) {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 - x, y0 - y);
			glEnd();
			glFlush();
			x = x + 1;
			p1 = p1 + 2 * ry * ry * x + ry * ry;
		}
		else {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 - x, y0 - y);
			glEnd();
			glFlush();
			x = x + 1;
			y = y - 1;
			p1 = p1 + 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
		}
	}

	float p2 = ry * ry * (x + (float)0.5) * (x + (float)0.5) + rx * rx * (y - (float)1) * (y - (float)1) - rx * rx * ry * ry;
	do {
		if (p2 < 0) {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 - x, y0 - y);
			glEnd();
			glFlush();
			x = x + 1;
			y = y - 1;
			p2 = p2 + 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
		}
		else {
			glBegin(GL_POINTS);
			glVertex2f(x0 + x, y0 + y);
			glVertex2f(x0 + x, y0 - y);
			glVertex2f(x0 - x, y0 + y);
			glVertex2f(x0 - x, y0 - y);
			glEnd();
			glFlush();
			y = y - 1;
			p2 = p2 - 2 * rx * rx * y + rx * rx;
		}
	} while (y >= 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(" Lab 3 ");

	init();
	glutDisplayFunc(display_ellipse);
	//glutDisplayFunc(display_circle);
	glutMainLoop();
	return 0;
}
