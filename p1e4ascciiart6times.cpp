#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ajusta(int ancho, int alto){

    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);

}

float random01(){
    float rMax=RAND_MAX;
    float random=rand();

    float num=random/rMax;
    return num;
}

void dibuja(){
    char c;
    int x,y;
    FILE *fp;

    x=225;
    y=400;

    srand((unsigned) time(NULL));

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    fp=fopen("calamardo.txt","r");
    if(fp==NULL) {
        puts("Problemas con archivo");
    }

    // paleta 8 colores
    float palette[8][3] = {
        {1.0, 0.0, 0.0},   // Rojo
        {0.0, 1.0, 0.0},   // VERDE
        {0.0, 0.0, 1.0},   // AZUL
        {1.0, 1.0, 0.0},   // AMARILLO
        {1.0, 0.0, 1.0},   // Magenta
        {0.0, 1.0, 1.0},   // Cyan
        {1.0, 0.5, 0.0},   // NARANJA
        {0.5, 0.0, 1.0}    // MORADO
    };

    int i;
    for (i = 0; i < 6; i++) {
        // escoger un color aleatorio
        int colorIndex = rand() % 8;
        float* color = palette[colorIndex];

        glColor3fv(color);

        while((c=fgetc(fp)) != EOF){
            printf("%c",c);

            glRasterPos2i(x,y);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            x = x + 10;

            if(c=='\n'){
                x= 225;
                y= y-20;
            }
        }
        rewind(fp);
        y -= 100;
    }

    fclose(fp);
    glFlush();

}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ascii");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;

}
