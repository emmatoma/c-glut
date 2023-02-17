#include <GL/glut.h>

float xc = 0;
float yc = 120;
float velX = 0.0;// horizontal vel
float velY = 0.0; // vertical vel
float ancho = 90;

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void move(void) {
    xc += velX;
    yc += velY;

    if (xc < -ancho) {
        xc = 640;
    } else if (xc > 640) {
        xc = -ancho;
    }

    // Wrap al lado opuesto si se sale de los border
    if (xc + ancho < 0) {
        xc = 640;
    } else if (xc > 640) {
        xc = -ancho;
    }

    if (yc + 250 > 480) {
        yc = 230;
    } else if (yc < 0) {
        yc = 0;
    }

    glutPostRedisplay();
}

void letra(int x, int y) {
    int i, n = 20;
    float rosa[3] = {1.0, 0.0, 0.5};

    int mi_letra[n][2] = {
        {50, 50}, {50, 250}, {100, 250}, {100, 50},
        {50, 50}, {200, 50}, {200, 100}, {100, 100},
        {100, 150}, {150, 150}, {150, 175}, {100, 175},
        {100, 200}, {200, 200}, {200, 250}, {100, 250}
    };

    // dibuja a la izq
    glColor3fv(rosa);
    glPointSize(2);
    glBegin(GL_QUADS);
    for (i = 0; i < n; i++) {
        glVertex2i(mi_letra[i][0] + x - 640, mi_letra[i][1] + y);
    }
    glEnd();

    // Dibuja a la derecha
    glBegin(GL_QUADS);
    for (i = 0; i < n; i++) {
        glVertex2i(mi_letra[i][0] + x, mi_letra[i][1] + y);
    }
    glEnd();

    // Si se pasa de la izq se va a la derecha 
    if (x < 0) {
        glPushMatrix();
        glTranslatef(640, 0, 0);
        glColor3fv(rosa);
        glPointSize(2);
        glBegin(GL_QUADS);
        for (i = 0; i < n; i++) {
            glVertex2i(mi_letra[i][0] + x + 640, mi_letra[i][1] + y);
        }
        glEnd();
        glPopMatrix();
    }

    // Si se pasa de la der se va a la izq
    if (x > 640 - ancho) {
        glPushMatrix();
        glTranslatef(-640, 0, 0);
        glColor3fv(rosa);
        glPointSize(2);
        glBegin(GL_QUADS);
        for (i = 0; i < n; i++) {
            glVertex2i(mi_letra[i][0] + x - 640, mi_letra[i][1] + y);
        }
        glEnd();
        glPopMatrix();
    }
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 27: 
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void tecladoEspecial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT:
            velX = -0.1;
            break;
        case GLUT_KEY_RIGHT:
            velX = 0.1;
            break;
        case GLUT_KEY_UP:
            velY = 0.1;
            break;
        case GLUT_KEY_DOWN:
            velY = -0.1;
            break;
    }
}

void tecladoEspecialUp(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            velX = 0.0;
            break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            velY = 0.0;
            break;
    }
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    letra(xc, yc);

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    int v = 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Letter");
    glutReshapeFunc(ajusta);
    glutIdleFunc(move);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutSpecialUpFunc(tecladoEspecialUp);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}
