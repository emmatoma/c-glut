#include <gl/glut.h>
struct punto{
 int cx;
 int cy;
 float color[3];
 int size;
 struct punto *sig;
};
typedef struct punto Punto;
Punto *inicio=NULL;
Punto *creaNodo(int, int, float [3],int);
void inserta(int, int, float [3],int);
Punto *creaNodo(int x, int y, float color[3], int size){
Punto *p;
p=(Punto*)malloc(sizeof(Punto));
p->cx= x;
p->cy=y;
/////color
p->color[0]= color[0];
p->color[1]= color[1];
p->color[2]= color[2];
////
p->size= size;
p->sig=NULL;
return p;
}
void inserta(int x, int y, float color[3], int size){
Punto *aux=inicio;
if(inicio == NULL){
inicio = creaNodo(x,y, color, size);
} else {
while(aux->sig != NULL){
aux = aux->sig;
}
aux->sig = creaNodo(x,y, color, size);
}
}
void ajusta(int ancho, int alto) {
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0, 640, 0, 480);
}
GLboolean option=GL_TRUE;



///size of drawing
int tam=5; 
void mouse(int x, int y){
 int windowVertical=480;
 float color[3];
////rgb array
///color pink
 color[0]=1; //red
color[1]=0; //green
 color[2]=.5; //blue
 inserta(x,windowVertical-y,color,tam);
glutPostRedisplay();
}
void keyboard(unsigned char keyletter, int x, int y){
 switch(keyletter) {

 	///switch
 case 's':
option=!option;
//bool; check if option was mouse and set to null or viceversa
glutMotionFunc((option)?mouse:NULL);
glutPassiveMotionFunc((option)?NULL:mouse);
break;
 	///tecla escape termina

 	 case 27: exit(0); 
 }
}
void pageUp_Down(int keyletter, int x, int y) {
 switch(keyletter) {
 case GLUT_KEY_PAGE_UP: tam++;
 break;
 case GLUT_KEY_PAGE_DOWN: tam--;
 break;
 case GLUT_KEY_HOME: inicio=NULL;
 }
}
void dibuja(void){
int i;
Punto *aux=inicio;
glClear(GL_COLOR_BUFFER_BIT);

 while(aux != NULL){
glPointSize(tam);
glColor3fv(aux->color);
glBegin(GL_POINTS);
glVertex2i(aux->cx,aux->cy);
glEnd();
aux= aux->sig;
}

 glFlush();
}

int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
glutInitWindowSize(640,480);
glutInitWindowPosition(0,0);
glutCreateWindow("Draw");
glutDisplayFunc(dibuja);
glutMotionFunc(mouse);
glutKeyboardFunc(keyboard);
glutReshapeFunc(ajusta);
glutPassiveMotionFunc(NULL);
glutMainLoop();
return 0;
}

