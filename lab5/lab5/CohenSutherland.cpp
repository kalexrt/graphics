#include <GL/freeglut.h>
#include <iostream>
// Bitwise code
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
int xmin, ymin, xmax, ymax;
int calculateCode(float x, float y) {
    int code = INSIDE;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    return code;
}
void cohenSutherland(float x1, float y1, float x2, float y2) {
    int code1 = calculateCode(x1, y1);
    int code2 = calculateCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) { // If both endpoints are inside the clip window
            accept = true;
            break;
        }
        else if (code1 & code2) { // If both endpoints are outside the same region
            break;
        }
        else {
            // Calculate intersection point
            float x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {

                code1 = calculateCode(x, y);
            }
            else {

                code2 = calculateCode(x, y);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0); // Set color to green
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f); // Red color for the rejected line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    // Clipping window rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    float x1 = 50, y1 = 50, x2 = 150, y2 = 150;
    cohenSutherland(x1, y1, x2, y2);
    float x3 = 105, y3 = 5, x4 = 10, y4 = 150;
    cohenSutherland(x3, y3, x4, y4);
    glFlush();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 200, 0, 200);
}
int main(int argc, char** argv) {
    xmin = 75;
    ymin = 75;
    xmax = 125;
    ymax = 125;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
