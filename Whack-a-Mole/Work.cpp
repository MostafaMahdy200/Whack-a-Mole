#include <GL/glut.h> // Required header for OpenGL and GLUT
#include <GL/gl.h>

void myDisplay(void);
void myInit(void);

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the frame buffer
    glBegin(GL_POINTS); // Begin drawing a point
    glVertex2i(0, 0); // Display a point at the origin (0, 0)
    glEnd();
    glFlush(); // Execute all OpenGL commands in finite time
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set white background color
    glColor3f(1.0f, 0.0f, 0.0f); // Set drawing color to red (change to blue if needed)
    glPointSize(10.0); // Set point size to 10 pixels (thick dot)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffer and RGB mode
    glutInitWindowSize(400, 400); // Set window size
    glutInitWindowPosition(100, 150); // Set window position on screen

    glutCreateWindow("Display a Dot"); // Window title
    myInit(); // Initialize drawing settings
    glutDisplayFunc(myDisplay); // Display callback function
    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}
