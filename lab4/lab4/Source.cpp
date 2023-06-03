#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

float A[3],B[3],C[3];
float res1[3], res2[3], res3[3];
float M[3][3];

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

void multiplication() {
    for (int k = 0; k < 3; k++) {
        res1[k] = 0;
        res2[k] = 0;
        res3[k] = 0;
    }
    int a;
    for (int i = 0; i < 3; i++)
    {
        a = 0;
        for (int j = 0; j < 3; j++)
        {
            res1[i] += M[i][j] * A[a];
            res2[i] += M[i][j] * B[a];
            res3[i] += M[i][j] * C[a];
            a++;
        }

    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1.0f);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, -100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(A[0], A[1]);
    glVertex2f(B[0], B[1]);
    glVertex2f(C[0], C[1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(res1[0], res1[1]);
    glVertex2f(res2[0], res2[1]);
    glVertex2f(res3[0], res3[1]);
    glEnd();
    glFlush();

}


int main(int argc, char** argv) {
    int a;
    A[0] = 20;
    A[1] = 25;
    A[2] = 1;
    B[0] = -50;
    B[1] = 70;
    B[2] = 1;
    C[0] = -2;
    C[1] = -2;
    C[2] = 1;
    
    std::cout << "Enter the process to be done:\n1 -> Rotation\n2 -> Translation\n3 -> Scaling\n4 -> Reflection\n5 -> Shearing\n";
    std::cin >> a;

    switch (a) {
    case 1:

        float theta, b;
        M[2][0] = M[2][1] = M[0][2] = M[1][2] = 0;
        M[2][2] = 1;
        std::cout << "Enter rotation angle" << std::endl;
        std::cin >> theta;
        b = theta * 3.14159f / 180.0f;
        M[0][0] = M[1][1] = cos(b);
        M[1][0] = sin(b);
        M[0][1] = -M[1][0];
        break;
    case 2:
        M[0][0] = M[1][1] = M[2][2] = 1;
        M[0][1] = M[1][0] = M[2][0] = M[2][1] = 0;
        std::cout << "Enter transformation Along X-axis" << std::endl;
        std::cin >> M[0][2];
        std::cout << "Enter transformation Along y-axis" << std::endl;
        std::cin >> M[1][2];
        break;
    case 3:
        float Sx, Sy;
        std::cout << "Enter X- scaling factor" << std::endl;
        std::cin >> Sx;
        std::cout << "Enter Y- scaling factor" << std::endl;
        std::cin >> Sy;
        M[0][0] = Sx;
        M[1][1] = Sy;
        M[2][2] = 1;
        M[0][1] = M[1][0] = M[0][2] = M[1][2] = M[2][0] = M[2][1] = 0;
        break;
    case 4:
        M[0][0] = M[2][2] = 1;
        M[1][1] = -1;
        M[0][1] = M[0][2] = M[1][0] = M[1][2] = M[2][0] = M[2][1] = 0;
        break;
    case 5:
        float Shx, Shy;
        std::cout << "Enter X - searing factor" << std::endl;
        std::cin >> Shx;
        std::cout << "Enter Y - shearing factor" << std::endl;
        std::cin >> Shy;
        M[0][0] = M[1][1] = M[2][2] = 1;
        M[1][0] = Shx;
        M[0][1] = Shy;
        M[0][2] = M[1][2] = M[2][0] = M[2][1] = 0;
        break;

    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab4");
    init();
    multiplication();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}