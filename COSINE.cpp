#include <GL/glut.h>
#include <math.h>
void ajusta(int ancho, int alto){
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,640,0,480);
}
float cos(int x){
float rad= 3.1415/180;
return cos(x*rad);
}
void funct(){
int i;
int x, y;
glLineWidth(3);
glBegin(GL_LINE_STRIP);
for(i=-420; i<=420; i++){
y = (cos(i)*100)+240;//*magnitud +240 centro
x = i+320;
glVertex2i(x,y);
}
glEnd();
}

void ejes(){
glLineWidth(3);
glBegin(GL_LINES);
//mitad y=240 mitad x=320
glVertex2i(0, 240);
glVertex2i(640, 240);
glVertex2i(320, 0);
glVertex2i(320, 480);
glEnd();
}
void mesh(){
int i;
glLineWidth(1);
glEnable(GL_LINE_STIPPLE);
glLineStipple(5,0x5555);
glBegin(GL_LINES);
//step 20 para cuadricula
for(i=0; i<=640;i+=20){
glVertex2i(i, 0);
glVertex2i(i, 480);
glVertex2i(0, i);
glVertex2i(640, i);
}
glEnd();
glDisable(GL_LINE_STIPPLE);
}
void dibuja(){
float negro[3]={0.0, 0.0, 0.0};
float azul[3]={0.0, 0.0, 1.0};
float naranja[3]={ 1.0 , 0.5, 0.0};
glClearColor(1.0, 1.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3fv(azul);
mesh();
glColor3fv(naranja);
funct();
glColor3fv(negro);
ejes();
glFlush();
}
int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(0, 0);
glutCreateWindow("Cosine");
glutReshapeFunc(ajusta);
glutDisplayFunc(dibuja);
glutMainLoop();
return 0;
}