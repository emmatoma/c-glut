#include <gl/glut.h>
#include "pixelheart.h"

void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 320, 0, 240);
}

GLboolean color = GL_TRUE;
int tam = 8; 
int cx = 160;
int cy = 120;

void keyboard(unsigned char key, int x, int y){
    switch(key) {
        case 27: exit(0);
    }
}

void dibuja(void){
    int i,j;
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(tam);
    glBegin(GL_POINTS);

    for(i=0 ; i< ALTO; i++){
        for(j=0 ; j< ANCHO; j++){
            ///switch colors
            glColor3ubv((color)?paleta[pixelheart[i][j]]:paletaswitch[pixelheart[i][j]]);
            glVertex2i(cx+j*tam,cy-i*tam);
        }
    }

    glEnd();
    glFlush();
}

void timer(int value) {
    //switch color value
    color = !color;
    glutPostRedisplay();
    glutTimerFunc(600, timer, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(320, 240); // tamaño de ventana 320x240
    glutInitWindowPosition(0,0);
    glutCreateWindow("Pixel Heart");
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ajusta);
    glutTimerFunc(600, timer, 0); // llamada timer function para switch colors cada 600ms
    glutMainLoop();
    return 0;
}