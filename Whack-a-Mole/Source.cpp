#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>  

// Window dimensions
const int WIDTH = 600;
const int HEIGHT = 600;

// Mole properties
float moleX = 0.0f, moleY = 0.0f;
bool moleVisible = false;
int score = 0;
int moleIndex = -1;   // Mole's index (0 to 8 for 9 holes)
int lastMoleTime = 0; // Time when mole last appeared (in milliseconds)

// Hole positions 
float holePositions[9][2] = {
    {-0.5f, 0.5f}, {0.0f, 0.5f}, {0.5f, 0.5f},
    {-0.5f, 0.0f}, {0.0f, 0.0f}, {0.5f, 0.0f},
    {-0.5f, -0.5f}, {0.0f, -0.5f}, {0.5f, -0.5f}
};

// Function to draw a circle [Used for Holes]
void drawCircle(float x, float y, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Function to draw an oval [used for the mole]
void drawOval(float cx, float cy, float rx, float ry) {
    glColor3f(0.5f, 0.3f, 0.1f);            // Mole color [brown]
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        float x = rx * cos(angle);         // Calculate x component for oval
        float y = ry * sin(angle)*1.25;    // Calculate y component for oval
        glVertex2f(cx + x, cy + y);  
    }
    glEnd();
}

// Function to draw the mole's eyes
void drawEyes(float cx, float cy, float radius) {
    drawCircle(cx - 0.04f, cy + 0.04f, radius, 1.0f, 1.0f, 1.0f);  // Left eye
    drawCircle(cx + 0.04f, cy + 0.04f, radius, 1.0f, 1.0f, 1.0f);  // Right eye
    drawCircle(cx - 0.04f, cy + 0.04f, radius / 3.0f, 0.0f, 0.0f, 0.0f);  // Left pupil
    drawCircle(cx + 0.04f, cy + 0.04f, radius / 3.0f, 0.0f, 0.0f, 0.0f);  // Right pupil
}

// Function to generate a random position for the mole
void generateMole() {
    moleIndex = rand() % 9;  // Randomly select a hole index (0 to 8)
    moleX = holePositions[moleIndex][0];
    moleY = holePositions[moleIndex][1];
    moleVisible = true;
    lastMoleTime = glutGet(GLUT_ELAPSED_TIME);  // Record the time mole appeared
}

// Function to check if the mouse click hits the mole
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert screen coordinates to OpenGL coordinates
        float clickX = (x - WIDTH / 2.0f) / (WIDTH / 2.0f);
        float clickY = (HEIGHT / 2.0f - y) / (HEIGHT / 2.0f); // Invert y to match OpenGL coordinates

        // If the click is within the mole's area, increase the score
        if (moleVisible && (clickX >= moleX - 0.1f && clickX <= moleX + 0.1f) &&
                           (clickY >= moleY - 0.1f && clickY <= moleY + 0.1f)) {
            score++;             
            moleVisible = false; // Hide the mole
        }}}

// Function to render the game objects
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the holes [Background] 
    for (int i = 0; i < 9; i++) {
        float x = holePositions[i][0];
        float y = holePositions[i][1];
        drawCircle(x, y, 0.15f, 0.7f, 0.1f, 0.1f); // Hole color: [Red]
    }

    // If the mole is visible
    if (moleVisible) {
        drawOval(moleX, moleY, 0.1f, 0.1f);  // Mole's body
        drawEyes(moleX, moleY, 0.02f);       // Mole's eyes
    }

    // Draw the score on the screen
    glColor3f(1.0f, 1.0f, 1.0f); // White color for text
    glRasterPos2f(-0.12f, 0.9f);  // Position for score display

    // Convert score to string 
    std::ostringstream scoreTextStream;
    scoreTextStream << "Score: " << score;
    std::string scoreText = scoreTextStream.str();
    for (char c : scoreText) {glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);} // Display score as text
    
    glutSwapBuffers(); 
}

// Function to update the game each frame
void update(int value) {
    if (moleVisible) {
        // Check if 2 seconds have passed since the mole appeared
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - lastMoleTime >= 2000) {
            // Mole disappears after 2 seconds, score is decremented
            score--;
            moleVisible = false;
        }}
    else { generateMole(); }  // Randomly generate mole position when it disappears

    glutPostRedisplay();  // Request a redraw of the window
    glutTimerFunc(1000, update, 0); // Update every 1000ms (1 second)
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Use double buffering and RGB color
    glutInitWindowSize(WIDTH, HEIGHT);           // Set window size
    glutCreateWindow("Whack-a-Mole");            // Create window with title
    glutDisplayFunc(display);                    // Set display callback
    glutMouseFunc(mouse);                        // Set mouse click callback
    glutTimerFunc(1000, update, 0);              // Start the game update
    init();                                      // Initialize OpenGL
    glutMainLoop(); // Enter the main loop
    return 0;
}
