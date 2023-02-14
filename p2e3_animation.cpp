#include <gl/glut.h>
#include "pixelheart.h"
void ajusta(int ancho, int alto) {
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0, 640, 0, 480);
}
GLboolean color=GL_TRUE;
int tam=4; 
int cx=300;
int cy=220;

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
void pageUp_Down(int key, int x, int y) {
 switch(key) {
 case GLUT_KEY_UP: cy=cy+10; break;
 case GLUT_KEY_DOWN: cy=cy-10; break;
 case GLUT_KEY_RIGHT: cx=cx+10; break;
 case GLUT_KEY_LEFT: cx=cx-10; break;
 }
 //switch color value
 color=!color;
 glutPostRedisplay();
}
int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
glutInitWindowSize(640,480);
glutInitWindowPosition(0,0);
glutCreateWindow("Pixel Heart");
glutDisplayFunc(dibuja);
glutSpecialFunc(pageUp_Down);
glutKeyboardFunc(keyboard);
glutReshapeFunc(ajusta);
glutMainLoop();
return 0;
}
