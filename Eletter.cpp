#include <GL/glut.h>
void ajusta(int ancho, int alto){
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,640,0,480);
}
void wire(int x, int y){
int i,n=40;
int mi_letra[n][2]=
{{50,50},{50,250},{50,250},{200,250},{200,250},{200,200},{200,200},{100,200},
{100,200},{100,150},{100,150},{150,150},{150,150},{150,135},{150,135},{100,135}
,{100,135},{100,100},{100,100},{200,100},{200,50}, {50,50},{200,100},{200,50}
};


glBegin(GL_LINES);
for(i=0; i<n; i++){
glVertex2i(mi_letra[i][0], mi_letra[i][1]);
}
glEnd();
glFlush();
}
void solid(int x, int y){
int i,n=25;
int mi_letra[n][2]= {
{50,50},{50,250},{100,250},{100,50},
{50,50},{200,50},{200,100},{100,100},
{100,150},{150,150},{150,175},{100,175}
,{100,200},{200,200},{200,250},{100,250}
};
glBegin(GL_QUADS);
for(i=0; i<n; i++){
glVertex2i(mi_letra[i][0]+x, mi_letra[i][1]+y);
}
glEnd();
}
void dibuja(){
float color[3]={1.0, 0.0, 0.5};
glClearColor(1.0, 1.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3fv(color);
glLineWidth(5);
wire(20,20);
solid(200,200);
glFlush();
}
int main(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(100, 150);
glutCreateWindow("Letra");
glutReshapeFunc(ajusta);
glutDisplayFunc(dibuja);
glutMainLoop();
return 0;
}