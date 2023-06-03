#include <GL/freeglut.h>
#include <iostream>
const int INSIDE = 0; // Bitwise code to represent inside region
const int LEFT = 1;   // Bitwise code to represent left region
const int RIGHT = 2;  // Bitwise code to represent right region
const int BOTTOM = 4; // Bitwise code to represent bottom region
const int TOP = 8;    // Bitwise code to represent top region
float xmin, ymin, xmax, ymax; // Clipping window coordinates
// Function to calculate the bitwise code for a point
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
// Function to perform Sutherland-Hodgman Polygon Clipping
void sutherlandHodgman(float x1, float y1, float x2, float y2) {
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
            // Calculate intersection point using slope-intercept form
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
                x1 = x;
                y1 = y;
                code1 = calculateCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = calculateCode(x2, y2);
            }
        }
    }
    if (accept) {
        glColor3f(0.0, 0.0, 1.0); // Set color to blue
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}
// Function to clip a polygon
void clipPolygon(float subjectPolygon[][2], int subjectPolygonSize) {
    for (int i = 0; i < 4; i++) {
        float clipPolygon[][2] = { {xmin, ymin}, {xmax, ymin}, {xmax, ymax}, {xmin, ymax} };
        float tempPolygon[20][2];
        int tempPolygonSize = 0;
        for (int j = 0; j < subjectPolygonSize; j++) {
            float x1 = subjectPolygon[j][0];
            float y1 = subjectPolygon[j][1];
            float x2 = subjectPolygon[(j + 1) % subjectPolygonSize][0];
            float y2 = subjectPolygon[(j + 1) % subjectPolygonSize][1];
            sutherlandHodgman(x1, y1, x2, y2);
            if (calculateCode(x2, y2) == INSIDE) {
                tempPolygon[tempPolygonSize][0] = x2;
                tempPolygon[tempPolygonSize][1] = y2;
                tempPolygonSize++;
            }
        }
        subjectPolygonSize = tempPolygonSize;
        for (int k = 0; k < subjectPolygonSize; k++) {
            subjectPolygon[k][0] = tempPolygon[k][0];
            subjectPolygon[k][1] = tempPolygon[k][1];
        }
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
    // Original polygon
    float originalPolygon[][2] = { {90, 90}, {105,120}, {150, 120}, {140, 100},{120,50},{100,40} };
    int originalPolygonSize = 6;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < originalPolygonSize; i++) {
        glVertex2f(originalPolygon[i][0], originalPolygon[i][1]);
    }
    glEnd();
    // Clipped polygon
    clipPolygon(originalPolygon, originalPolygonSize);
    glFlush();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 200, 0, 200);
}
int main(int argc, char** argv) {
    xmin = 75;
    ymin = 100;
    xmax = 135;
    ymax = 145;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
