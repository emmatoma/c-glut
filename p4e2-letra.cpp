#include <gl/glut.h>
#include <math.h>

float theta= 0; //angulo inicial
float escale=1; 
float vRot=1; //velocidad
int xp= 0;
int yp= 0;
GLboolean rotate= GL_FALSE;
	
void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

void teclado(unsigned char tecla, int x, int y) {
 	switch(tecla) {
	 	case 27: exit(0); 
	 	case 'r': 
			rotate=GL_TRUE;
			break;
	}
 	glutPostRedisplay();
}

void raton(int boton, int estado, int x, int y){
	if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xp = x;
		yp= 480 - y;
	}
	glutPostRedisplay();
}

void letra(int x, int y){
	float xc,yc;
	int i,n=20;
	float rosa[3] = {1.0,0.0,0.5};
	
	int letra[n][2]= {{50,50},{50,250},{100,250},{100,50},
{50,50},{200,50},{200,100},{100,100},
{100,150},{150,150},{150,175},{100,175}
,{100,200},{200,200},{200,250},{100,250}
};	
	glColor3fv(rosa);
	glPointSize(2);
	glBegin(GL_QUADS);
	///imprime letra
	for(i=0; i<n; i++){
		yc= letra[i][1]+y;
		xc= letra[i][0]+x;
		xc = xc - xp; 
		yc = yc - yp;
		glVertex2i( ((xc*cos(theta) - yc*sin(theta)) + xp)*escale,
					((xc*sin(theta) + yc*cos(theta)) + yp)*escale);	
	}
		glEnd();
}

void tiempo(int valor){
	if(rotate){	
		theta= theta + M_PI/180 * vRot;
		if(theta<-6*M_PI){ // 6 M_PI son 3 vueltas
			rotate=GL_FALSE;
			theta=0;
		}
	}
   glutPostRedisplay();
   glutTimerFunc(10,tiempo,1);
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);			   
	letra(280,120);		
	glColor3ub(255,0,0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(xp,yp);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Pivote");
	glutDisplayFunc(dibuja);
	glutTimerFunc(10,tiempo,1);
	glutMouseFunc(raton);
	glutKeyboardFunc(teclado);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}
