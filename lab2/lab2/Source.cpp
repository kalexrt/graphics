#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

using namespace std;


void display_DDA() {
    float x1, y1, x2, y2;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    cout << "DDA line drawing algorithm \n";

    cout << "Enter x value for start point\n";
    cin >> x1;
    cout << "Enter y value for start point\n";
    cin >> y1;
    cout << "Enter x value for end point\n";
    cin >> x2;
    cout << "Enter y value for end point\n";
    cin >> y2;


    // DDA line drawing algorithm
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++) {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();

    glFlush();
}

void display_BLA() {
    float x1, y1, x2, y2;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    cout << "BLA line drawing algorithm \n";

    cout << "Enter x value for start point \n";
    cin >> x1;
    cout << "Enter y value for start point\n";
    cin >> y1;
    cout << "Enter x value for end point\n";
    cin >> x2;
    cout << "Enter y value for end point\n";
    cin >> y2;

    float x = x1, y = y1;
    glVertex2f(x, y);
    //BLA line drawing algorithm
    float dx = x2 - x1;
    float dy = y2 - y1;
    float pk;
    glBegin(GL_POINTS);
    if (abs(dy) <= abs(dx)) {
        pk = 2 * (dy)-(dx);
        for (int k = 0; k < dx; k++) {
            if (pk < 0) {
                pk = pk = 2 * (dy);
                x = x + 1;
                glVertex2f(x, y);
            }
            else {
                pk = pk + 2 * (dy)-2 * (dx);
                x = x + 1;
                y = y + 1;
                glVertex2f(x, y);
            }
        }
    }

    else {
        pk = 2 * (dx)-(dy);
        for (int k = 0; k < dy; k++) {
            if (pk < 0) {
                pk = pk + 2 * (dx);
                y = y + 1;
                glVertex2f(x, y);
            }
            else {
                pk = pk + 2 * (dx)-2 * (dy);
                y = y + 1;
                x = x + 1;
                glVertex2f(x, y);
            }


        }
    }
    glEnd();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200.0, 200.0, -200.0, 200.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(" Graphics Lab 2");
    init();
    //glutDisplayFunc(display_BLA);
    glutDisplayFunc(display_DDA);
    glutMainLoop();
    return 0;
}