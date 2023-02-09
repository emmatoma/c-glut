#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "pixelheart.h"
void ajusta(int ancho, int alto){
	
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);

}
void cuadros(){
	
	float negro[3]={0.0, 0.0, 0.0};
	
	glLineWidth(3);
	glColor3fv(negro);
	glBegin(GL_LINES);
	glVertex2i(210,0);
	glVertex2i(210,480);
	glVertex2i(420,0);
	glVertex2i(420,480);
	glVertex2i(0,240);
	glVertex2i(640,240);
	glEnd();
	
}

int polilinea(){
	
	float azul[3]={0.5,0.0,1.0};
	int x,y;
	int i,j;
	int nLineas,nVertices;
	
	FILE *fp;
	
	fp = fopen("Heart.dat", "r");
	if (fp == NULL){
		puts("archivo error");
		return 1;
	}
	
	fscanf(fp, "%d", &nLineas);
	
	glColor3fv(azul);
	
	for (i=0; i<nLineas; i++){
			fscanf(fp, "%d", &nVertices);
			glBegin(GL_LINE_STRIP);
			for (j = 0; j<nVertices; j++){
					fscanf(fp,"%d", &x);
					fscanf(fp,"%d", &y);
					glVertex2f(x+5,y+270);
			}
			glEnd();
	}
	fclose(fp);
	
	char c[10]="Alvarez";
	glRasterPos2i(50,250);
	for(i=0; i< strlen(c); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
	
	return 0;
	
}
void circunferencia(int r){
	
	float morado[3]={1.0,0.0,1.0};
	int centro[2]={315, 360};
	int coord[15][2];
	
	int x, y, c, i, j, theta;
	float rad= M_PI/180;
	
	c=0;
	//Fijar puntos
//valor de r cambia para la circunferencia
	for(theta=0; theta<360; theta+=(360/15)){
		
		x= centro[0] + (r*(cos(theta*rad)));
		y= centro[1] + (r*(sin(theta*rad)));
		coord[c][0]= x;
		coord[c][1]= y;
		c++;
	}
		///Lineas
	glColor3fv(morado);
	glLineWidth(1);
	for(i=0;i<15;i++){
		///siguiente
		c=i+1; 
		for(j=0;j<15;j++){
			
			if(c>=15){
				c=0;
			}
			glBegin(GL_LINES);
			glVertex2i(coord[i][0],coord[i][1]);
			glVertex2i(coord[c][0],coord[c][1]);
			glEnd();
			c++;
		}
	}
	
}
float coseno(int x){
	float rad= M_PI/180;
	
	return cos(x*rad*2);
}

void cosenoGrafica(){
	
	float negro[3]={0.0, 0.0, 0.0};
	float rojo[3]={1.0,0.0,0.0};
	int i,x,y;
	
	glLineWidth(2);
	glColor3fv(negro);
	glBegin(GL_LINES);
	glVertex2i(440,360);
	glVertex2i(620,360);
	glVertex2i(530,270);
	glVertex2i(530,450);
	glEnd();
	
	glLineWidth(3);
	glColor3fv(rojo);
	glBegin(GL_LINE_STRIP);
	//90 centro
	for(i=-90; i<=90; i++){ 
		x = i+530;
		//100 de largo, el 360 centro
		y = (coseno(i)*100)+360;
		glVertex2i(x,y);
	}
	glEnd();
}

void letra(){
	
	int i;
	int n=30;
	
	float rojo[3]={1.0,0.0,0.2};
	
	int mi_letra[30][2]= {{50,50},{50,250},{50,250},{200,250},{200,250},{200,200},{200,200},{100,200},
{100,200},{100,150},{100,150},{150,150},{150,150},{150,135},{150,135},{100,135}
,{100,135},{100,100},{100,100},{200,100},{200,50}, {50,50},{200,100},{200,50}
};
;
	
	
	glColor3fv(rojo);
	glLineWidth(5);
	glBegin(GL_LINES);
	
	for(i=0; i<n; i++){
		glVertex2i(mi_letra[i][0], mi_letra[i][1]-20);
	}
	glEnd();
	
}

void lineas(int sz){
	
	float rosa[3]={1.0, 0.0, 0.5};
	///x y inf xy superior
	int x1= 400;
	int y1= 200;
	int x0= 250;
	int y0= 50;
	int i;
	
	int rango= x1-x0;
	
	glColor3fv(rosa);
	glLineWidth(2);
	glBegin(GL_LINES);

	for(i=0; i<=rango; i+=sz){
		glVertex2i(x0,y0+i);
		glVertex2i(x0+i,y1);
		
		glVertex2i(x1,y0+i);
		glVertex2i(x1-i,y1);
	}
	for(i=0; i<=rango; i+=sz){
		glVertex2i(x0,y1-i);
		glVertex2i(x0+i,y0);
		
		glVertex2i(x1,y1-i);
		glVertex2i(x1-i,y0);
	}
	glEnd();
}

void pixelart(){
	int i,j;
	///punto
	int tam=5; 
	glPointSize(tam);
	glBegin(GL_POINTS);
	
	for(i=0 ; i< ALTO; i++){
		for(j=0 ; j< ANCHO; j++){
			glColor3ubv(paleta[pixelheart[i][j]]);
			glVertex2i(500+j*tam,180-i*tam);
		}	
	}
	glEnd();
}

void dibuja(){
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	cuadros();
	polilinea();
	circunferencia(100);
	cosenoGrafica();
	letra();
	lineas(10);
	pixelart();
	glFlush();

}

int main(int argc, char** argv){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Tarea 2");
	glutReshapeFunc(ajusta);
	glutDisplayFunc(dibuja);
	glutMainLoop();
	return 0;

}
////matriz
//						
//								  {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
//                                {0,0,0,0,2,1,1,2,0,0,2,2,1,1,2,2,0,0,0,0,0},
//                                {0,0,0,0,2,1,1,1,2,2,1,1,1,1,1,2,2,0,0,0,0},
//                                {0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0},
//                                {0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0},
//                                {0,0,0,0,0,0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,2,1,1,1,1,1,2,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,0,2,1,2,0,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
//                                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},};

