#include <GL/glut.h>
void ajusta(int ancho, int alto){
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,630,0,470);
}
void dibuja(){
float rojo[3]={1.0, 0.0, 0.0};
float rojo2[3]={1.0, 0.5, 1.0};
float rojo3[3]={1.0, 0.5, 0.5};
float naranja[3]={ 1.0 , 0.5, 0.0};
float rosa[3]={1.0, 0.0, 0.5};
float rosa2[3]={1.0, 0.75, 1.0};
float amarillo[3]={1.0, 1.0, 0.0};
float verde[3]={0.0, 1.0, 0.0};
float verde2[3]={0.0, 1.0, 0.5};
float verde3[3]={0.5, 1.0, 0.5};
float morado[3]={1.0, 0.0, 1.0};
float morado2[3]={1.0, 0.5, 1.0};
float azul[3]={0.0, 0.0, 1.0};
float azul2[3]={0.0, 0.5, 1.0};
float azul3[3]={0.5, 0.5, 1.0};

//fond
glClearColor(0.9, 0.9, 0.9, 0.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3fv(amarillo);
glBegin(GL_QUADS);
glVertex2i(0, 640);
glVertex2i(640, 480);
glVertex2i(640, 0);
glVertex2i(0, 0);
glEnd();

//Cuadrilatero
glColor3fv(naranja);
glBegin(GL_QUADS);
glVertex2i(100, 450);
glVertex2i(150, 350);
glVertex2i(250, 400);
glVertex2i(250, 450);
glEnd();

//Pentagono wireframe
glLineWidth(5);
glColor3fv(rojo);
glBegin(GL_LINE_STRIP);
glVertex2i(50, 100);
glVertex2i(50, 200);
glVertex2i(100, 250);
glVertex2i(150, 200);
glVertex2i(150, 100);
glVertex2i(50, 100);
glEnd();
//Pentagono punteado
glLineWidth(5);
glColor3fv(azul);
glEnable(GL_LINE_STIPPLE);
glLineStipple(5,0xB5AD);
glBegin(GL_LINE_LOOP);
glVertex2i(450, 100);
glVertex2i(450, 200);
glVertex2i(500, 250);
glVertex2i(550, 200);
glVertex2i(550, 100);
glEnd();
glDisable(GL_LINE_STIPPLE);
//Pentagono solido
glColor3fv(morado);
glBegin(GL_POLYGON);
glVertex2i(250, 100);
glVertex2i(250, 200);
glVertex2i(300, 250);
glVertex2i(350, 200);
glVertex2i(350, 100);
glEnd();
//Pentagono triangulos
glBegin(GL_TRIANGLES);
glColor3fv(rosa);
glVertex2i(400, 300);
glColor3fv(amarillo);
glVertex2i(450, 350);
glColor3fv(azul2);
glVertex2i(400, 400);
glColor3fv(morado2);
glVertex2i(400, 300);
glColor3fv(verde);
glVertex2i(450, 350);
glColor3fv(rojo);
glVertex2i(500, 300);
glColor3fv(naranja);
glVertex2i(500, 300);
glColor3fv(rosa);
glVertex2i(450, 350);
glColor3fv(azul);
glVertex2i(500, 400);
glColor3fv(morado);
glVertex2i(400, 400);
glColor3fv(verde2);
glVertex2i(450, 350);
glColor3fv(rosa);
glVertex2i(500, 400);
glColor3fv(azul3);
glVertex2i(400, 400);
glColor3fv(rojo3);
glVertex2i(450, 450);
glColor3fv(verde3);
glVertex2i(500, 400);
glEnd();
glFlush();
}
int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(0, 0);
glutCreateWindow("SHAPES");
glutReshapeFunc(ajusta);
glutDisplayFunc(dibuja);
glutMainLoop();
return 0;
}