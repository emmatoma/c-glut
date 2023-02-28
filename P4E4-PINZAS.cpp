#include <GL/glut.h>
#include <stdio.h>

GLUquadricObj *quadraticObj;
GLboolean pinzabierta = GL_FALSE;

float xc= 0;
float rotate= 0;

void ajusta(int ancho, int alto)
{
	glClearColor(1.,1.,1.,1.);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//agregar
	glEnable(GL_DEPTH_TEST);
	///ESPECIFICACION PROYECCION EN TODOS LOS EJES
	glOrtho(-10,10,-10,10,10,-10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///INSTRUCCIONES
void pageUp_Down(int tecla, int x, int y){
	switch(tecla){
	////rotar
		case GLUT_KEY_F5:
			rotate= rotate + 5;
			break;
			////derecha e izq
		case GLUT_KEY_LEFT:
			xc= xc - 0.5;
			break;
		case GLUT_KEY_RIGHT:
			xc= xc + 0.5;
			break;
		///abre
		case GLUT_KEY_F2:
			pinzabierta= GL_TRUE;
			break;
		///cierra
		case GLUT_KEY_F1: 
			pinzabierta= GL_FALSE;
			break;
	}
	glutPostRedisplay();
}

void dibuja(void)
{
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 	quadraticObj = gluNewQuadric();
	glPushMatrix();
	glRotatef(rotate,0,1,0); //rotar es el angulo
	///PINZAS
	//gris
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
	glTranslatef(xc + 0.2, -4, 0); //agregarle a la x
	glRotatef(pinzabierta?40:0,0,0,1); //40grados
	glTranslatef(0, -1.5, 0); 
	//.25*.7 3 altura
	glScalef(0.25, 3, 0.7);	
	glutSolidCube(1);
	glPopMatrix();	
	//azul
	glPushMatrix();
	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(xc - 0.2, -4, 0); ///quitarle a la x
	glRotatef(pinzabierta?-40:0,0,0,1); //40grados
	glTranslatef(0, -1.5, 0); 
	//.25*.7 3 altura
	glScalef(0.25, 3, 0.7);	
	glutSolidCube(1);
	glPopMatrix();
	
	//Cilindro
	glColor3f(1,0,0);//rojo
	glPushMatrix();
	glTranslatef(0+xc,8,0);
	///vertical
	glRotatef(90,1,0,0); 
	gluQuadricDrawStyle(quadraticObj,GLU_FILL);
	///.5*12 altura
	gluCylinder(quadraticObj,0.5,0.5,12,20,20);
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 	glutInitWindowPosition(50, 50);
 	glutInitWindowSize(480, 480);
 	glutInit(&argc, argv);
 	glutCreateWindow("Pinzas");
 	glutDisplayFunc(dibuja);
 	glutSpecialFunc(pageUp_Down);
 	glutReshapeFunc(ajusta);
 	glutMainLoop();
 	return 0;
}
