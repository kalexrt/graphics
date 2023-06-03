#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);

    // Draw the top triangle
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.8f);
    glVertex2f(0.0f, 0.25f); 
    glVertex2f(0.5f, 0.25f);

    glEnd();

    // Draw the bottom triangle 
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.425f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.5f, -0.2f);

    glEnd();

    // Draw the blue stripe
    glLineWidth(5.5f);
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.8f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.5f, -0.2f);
    glVertex2f(0.15f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glEnd();



    //draw sun
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    float x, y;
    float radius = 0.08f;
    float center_x = 0.15f, center_y = 0.0f;
    glVertex2f(center_x, center_y);
    for (int i = 0; i <= 360; i++)
    {
        x = center_x + radius * cos(i * 3.14159f / 180.0f);
        y = center_y + radius * sin(i * 3.14159f / 180.0f);
        glVertex2f(x, y);
    }
    glEnd();


    // draw moon

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    float a, b;
    float radius1 = 0.08f;
    float center_a = 0.15f, center_b = 0.4f;
    glVertex2f(center_a, center_b);
    for (int i = 0; i <= 360; i++)
    {
        a = center_a + radius1 * cos(i * 3.14159f / 180.0f);
        b = center_b + radius1 * sin(i * 3.14159f / 180.0f);
        glVertex2f(a, b);
    }
    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    float radius2 = 0.073f;
    float center_c = 0.15, center_d = 0.42;
    glVertex2f(center_c, center_d);
    for (int i = 0; i <= 360; i++)
    {
        a = center_c + radius2 * cos(i * 3.14159f / 180.0f);
        b = center_d + radius2 * sin(i * 3.14159f / 180.0f);
        glVertex2f(a, b);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graphics lab1");
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    std::cout << "Screen resolution: " << screenWidth << "x" << screenHeight << std::endl;
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}