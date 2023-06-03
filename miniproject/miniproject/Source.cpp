#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

int currentColor = 0; // 0: Red, 1: Yellow, 2: Green

void drawCircle(float centerX, float centerY, float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159 / 180;
        float x = centerX + radius * cos(theta);
        float y = centerY + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawTrafficLight()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw pole
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, -1.0f);
    glVertex2f(0.1f, -1.0f);
    glVertex2f(0.1f, -0.45f);
    glVertex2f(-0.1f, -0.45f);
    glEnd();

    // Draw rectangular box
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.45f);
    glVertex2f(0.4f, -0.45f);
    glVertex2f(0.4f, 0.85f);
    glVertex2f(-0.4f, 0.85f);
    glEnd();

    // Draw red light
    if (currentColor == 0) drawCircle(0.0f, 0.6f, 0.15f, 1.0f, 0.0f, 0.0f); // Red
    else drawCircle(0.0f, 0.6f, 0.15f, 0.3f, 0.0f, 0.0f); // Dim red

    // Draw yellow light
    if (currentColor == 1) drawCircle(0.0f, 0.2f, 0.15f, 1.0f, 1.0f, 0.0f); // Yellow
    else drawCircle(0.0f, 0.2f, 0.15f, 0.3f, 0.3f, 0.0f); // Dim yellow

    // Draw green light
    if (currentColor == 2) drawCircle(0.0f, -0.2f, 0.15f, 0.0f, 1.0f, 0.0f); // Green
    else drawCircle(0.0f, -0.2f, 0.15f, 0.0f, 0.3f, 0.0f); // Dim green

    glFlush();
    glutSwapBuffers();
}

void timerFunc(int value)
{
    currentColor = (currentColor + 1) % 3; // Toggle between red, yellow, and green

    glutPostRedisplay(); // Redraw the scene

    if (currentColor == 0 || currentColor == 2)
        glutTimerFunc(10000, timerFunc, 0); // 10 seconds for red or green light
    else
        glutTimerFunc(2000, timerFunc, 0); // 2 seconds for yellow light
}

void initialize()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(400, 600);
    glutCreateWindow("Traffic Light");
    glutDisplayFunc(drawTrafficLight);
    glutTimerFunc(0, timerFunc, 0);
    initialize();
    glutMainLoop();

    return 0;
}