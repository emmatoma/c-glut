#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
// Colors
GLfloat green[] = {0.0, 1.0, 0.0};
GLfloat yellow[] = {1.0, 1.0, 0.0};
GLfloat red[] = {1.0, 0.0, 0.0};
GLfloat gray[] = {0.5, 0.5, 0.5};
GLfloat black[] = {0.0, 0.0, 0.0};

// Enumerate colors
enum LightColor {
    GREEN,
    YELLOW,
    RED,
    GRAY
};

enum LightColor currentColor = GREEN;
int blinkCount = 0;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, -200, 200);
}

// Draw the stoplight with circles
void drawStoplight() {
    // Draw black rectangles around the circles
    glColor3fv(black);
    glRecti(225, 150, 375, 450);
    glRecti(250, 125, 350, 475);
    glRecti(275, 100, 325, 500);

    // Draw green circle
    if (currentColor == GREEN) {
        glColor3fv(green);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3i(300, 350, 0);
    for (int i = 0; i <= 360; i++) {
        glVertex3f(25 * cos(i * M_PI / 180.0) + 300, 25 * sin(i * M_PI / 180.0) + 350, 0);
    }
    glEnd();

    // Draw yellow circle
    if (currentColor == YELLOW) {
        glColor3fv(yellow);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3i(300, 275, 0);
    for (int i = 0; i <= 360; i++) {
        glVertex3f(25 * cos(i * M_PI / 180.0) + 300, 25 * sin(i * M_PI / 180.0) + 275, 0);
    }
    glEnd();

    // Draw red circle
    if (currentColor == RED) {
        glColor3fv(red);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3i(300, 200, 0);
    for (int i = 0; i <= 360; i++) {
        glVertex3f(25 * cos(i * M_PI / 180.0) + 300, 25 * sin(i * M_PI / 180.0) + 200, 0);
    }
    glEnd();
}

// Update color
void updateStoplight() {
    // Incrementar los parpadeos del verde, va a hacerlo 3 veces
    if (currentColor == GREEN) {
        blinkCount++;
        if (blinkCount >= 6) {
            currentColor = YELLOW;
            blinkCount = 0;
        } else if (blinkCount % 2 == 0) {
            currentColor = GRAY;
        } else {
            currentColor = GREEN;
        }
    }
    // Switch al siguiente color si ya no es verde
    else {
        switch (currentColor) {
            case YELLOW:
                currentColor = RED;
                break;
            case RED:
                currentColor = GREEN;
                blinkCount = 0;
                break;
            case GRAY:
            default:
                currentColor = GREEN;
                break;
        }
    }
}
//se muestra el semáforo y actualiza colores
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawStoplight();
    glutSwapBuffers();
    updateStoplight();
}
// Timer callback function
void timerCallback(int value) {
    glutPostRedisplay(); // se vuelve a llamar a display después de cierto tiempo
    glutTimerFunc(500, timerCallback, 0); // tiempo de display
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Stoplight");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(500, timerCallback, 0); // tiempo de display
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
