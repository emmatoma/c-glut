#include <GL/glut.h>
#include <math.h>
#include <iostream>

float xc = 50, yc = 125, velX = 0.1, velY = 0.1, radio = 25;
GLubyte paleta[3][3] = {{0, 0, 0}, {255, 0, 0}, {0, 0, 255}};
enum colores {negro, rojo, azul};
enum colores col = negro;
GLenum modo = GL_POLYGON; // wireframe o solida
int lados = 20; // number of sides for the shape

void dibujaFigura(float x, float y, int lados){
    glBegin(modo);
    for(int i=0; i<lados; i++){
        glVertex2f(x+radio*cos(2*M_PI*i/lados),y+radio*sin(2*M_PI*i/lados));
    }
    glEnd();
}

void cambia(int opcion){
    switch(opcion){
        case 10: modo = GL_POLYGON; break;
        case 20: modo = GL_LINE_LOOP; break;
        case 30: lados = 3; break; // cambio lados to 3 for a triangle
        case 40: lados = 8; break; // cambio lados to 8 for an octagon
        case 50: lados = 12; break; // cambio lados to 12 for a dodecagon
        case 60: lados = 18; break; // cambio lados to 18 for a dodecagon
        case 70: lados = 20; break; // cambio lados to 20 for a Isodecagon
        case 100: exit(0);
    }
    glutPostRedisplay();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ubv(paleta[col]);
    dibujaFigura(xc, yc, lados);
    glutSwapBuffers();
}

void anima(void){
    if (xc+radio >= 640 || xc-radio <= 0) velX = -velX;
    if (yc+radio >= 480 || yc-radio <= 0) velY = -velY;
    xc += velX; yc += velY;
    glutPostRedisplay();
}

void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void pinta(unsigned char tecla, int x, int y) {
    switch(tecla) {
        case 'n': col = negro; break;
        case 'r': col = rojo; break;
        case 'a': col = azul; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Moving Shape");
    glutReshapeFunc(ajusta);
    glutIdleFunc(anima);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(pinta);

    // menu 
    glutCreateMenu(cambia);
    glutAddMenuEntry("Circle", 10);
    glutAddMenuEntry("Wireframe", 20);
    glutAddMenuEntry("Triangle", 30);
    glutAddMenuEntry("Octagon", 40);
    glutAddMenuEntry("Dodecagon", 50);
    glutAddMenuEntry("Octodecagon", 60);
    glutAddMenuEntry("Isodecagon", 70);
    glutAddMenuEntry("Exit", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
