#include <GL/glut.h>

// Colores
GLfloat green[] = {0.0, 1.0, 0.0};
GLfloat yellow[] = {1.0, 1.0, 0.0};
GLfloat red[] = {1.0, 0.0, 0.0};
GLfloat gray[] = {0.5, 0.5, 0.5};

// Enumera colores
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
    gluOrtho2D(0, 640, 0, 480);
}

// Se dibujan los 3 triangulos
void drawStoplight() {
    // luz verde
    if (currentColor == GREEN) {
        glColor3fv(green);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 400);
    glVertex2i(250, 350);
    glVertex2i(350, 350);
    glEnd();

    // luz amarilla
    if (currentColor == YELLOW) {
        glColor3fv(yellow);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 325);
    glVertex2i(250, 275);
    glVertex2i(350, 275);
    glEnd();

    // luz roja
    if (currentColor == RED) {
        glColor3fv(red);
    } else {
        glColor3fv(gray);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 250);
    glVertex2i(250, 200);
    glVertex2i(350, 200);
    glEnd();
}

// actualiza color
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Stoplight");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(500, timerCallback, 0); // tiempo de display
    glutMainLoop();
    return 0;
}