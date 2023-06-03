#include <GL/freeglut.h>
#include <iostream>

GLfloat angle = 0.0f;   // Rotation angle
GLfloat scale = 1.0f;   // Scaling factor
GLfloat tx = 0.0f;      // Translation along x-axis
GLfloat ty = 0.0f;      // Translation along y-axis
GLfloat tz = 0.0f;      // Translation along z-axis
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();                                  // Reset the model-view matrix
    glTranslatef(tx, ty, tz);              // Perform translation
    glRotatef(angle, 0.0f, 1.0f, 1.0f);     // Perform rotation
    glScalef(scale, scale, scale);          // Perform scaling
    glBegin(GL_QUADS);
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);    // Red
    glVertex3f(-0.5f, -0.5f, 0.5f);  // Vertex 1
    glVertex3f(0.5f, -0.5f, 0.5f);   // Vertex 2
    glVertex3f(0.5f, 0.5f, 0.5f);    // Vertex 3
    glVertex3f(-0.5f, 0.5f, 0.5f);   // Vertex 4
    // Back face
    glColor3f(0.0f, 1.0f, 0.0f);    // Green
    glVertex3f(-0.5f, -0.5f, -0.5f); // Vertex 1
    glVertex3f(0.5f, -0.5f, -0.5f);  // Vertex 2
    glVertex3f(0.5f, 0.5f, -0.5f);   // Vertex 3
    glVertex3f(-0.5f, 0.5f, -0.5f);// Vertex 4
    // Top face
    glColor3f(0.0f, 0.0f, 1.0f);    // Blue
    glVertex3f(-0.5f, 0.5f, -0.5f);  // Vertex 1
    glVertex3f(-0.5f, 0.5f, 0.5f);   // Vertex 2
    glVertex3f(0.5f, 0.5f, 0.5f);    // Vertex 3
    glVertex3f(0.5f, 0.5f, -0.5f);  // Vertex 4
    // Bottom face
    glColor3f(1.0f, 1.0f, 0.0f);    // Yellow
    glVertex3f(-0.5f, -0.5f, -0.5f); // Vertex 1
    glVertex3f(0.5f, -0.5f, -0.5f);  // Vertex 2
    glVertex3f(0.5f, -0.5f, 0.5f);   // Vertex 3
    glVertex3f(-0.5f, -0.5f, 0.5f);    // Vertex 4
    // Right face
    glColor3f(1.0f, 0.0f, 1.0f);    // Magenta
    glVertex3f(0.5f, -0.5f, -0.5f);  // Vertex 1
    glVertex3f(0.5f, 0.5f, -0.5f);   // Vertex 2
    glVertex3f(0.5f, 0.5f, 0.5f);    // Vertex 3
    glVertex3f(0.5f, -0.5f, 0.5f);   // Vertex 4
    // Left face
    glColor3f(0.0f, 1.0f, 1.0f);    // Cyan
    glVertex3f(-0.5f, -0.5f, -0.5f); // Vertex 1
    glVertex3f(-0.5f, -0.5f, 0.5f);  // Vertex 2
    glVertex3f(-0.5f, 0.5f, 0.5f);   // Vertex 3
    glVertex3f(-0.5f, 0.5f, -0.5f);  // Vertex 4
    glEnd();
    glutSwapBuffers();
}
void reshape(int width, int height) {
    if (height == 0) height = 1;
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, 1000, 1000); // Set the viewport to cover the entire window
    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        angle += 10.0f; // Rotate clockwise by 10 degrees
        break;
    case 'a':
        angle -= 10.0f; // Rotate anti-clockwise by 10 degrees
        break;
    case 's':
        scale -= 0.1f;  // Scale down by 10%
        break;
    case 'b':
        scale += 0.1f;  // Scale up by 10%
        break;
    case 't':
        tx += 0.1f;     // Translate along x-axis by 0.1 units
        ty += 0.1f;     // Translate along y-axis by 0.1 units
        tz += 0.1f;     // Translate along z-axis by 0.1 units
        break;
    case 'n':
        tx -= 0.1f;     // Translate along x-axis by 0.1 units
        ty -= 0.1f;     // Translate along y-axis by 0.1 units
        tz -= 0.1f;     // Translate along z-axis by 0.1 units
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("3D Transformation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
