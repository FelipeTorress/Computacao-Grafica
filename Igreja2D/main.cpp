/*###############################################################
	Computacao Grafica usando OpenGL (Atividade Igreja 2D)
	Autor: Felipe da Rocha Torres
################################################################# */

// Bibliotecas utilizadas pelo OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "circulo.h"
#include <stdio.h>

//parametros: R,G,B = parametros das cores do objeto, vertice? = ponto x e y do vertice ?
void drawRectangle(float R,float G,float B, int vertice1[2], int vertice2[2], int vertice3[2],
	int vertice4[2]){
	
	glColor3f(R, G, B);//colorindo o objeto
	glBegin(GL_QUADS);
	glVertex2f(vertice1[0], vertice1[1]);
	glVertex2f(vertice2[0], vertice2[1]);
	glVertex2f(vertice3[0], vertice3[1]);
	glVertex2f(vertice4[0], vertice4[1]);
		
}

//parametros: R,G,B = parametros das cores do objeto, vertice? = ponto x e y do vertice ?
void drawTriangle(int vertice1[2], int vertice2[2], int vertice3[2]){
	
	glColor3f(1.0, 0, 0);//colorindo o objeto
	
	glBegin(GL_TRIANGLES);
	glVertex2f(vertice1[0], vertice1[1]);
	glVertex2f(vertice2[0], vertice2[1]);
	glVertex2f(vertice3[0], vertice3[1]);
		
}

void drawLine(int vertice1[2], int vertice2[2]){
	glColor3f(0, 0, 0);//colorindo o objeto
	glBegin(GL_LINES);
	glVertex2f(vertice1[0], vertice1[1]);
	glVertex2f(vertice2[0], vertice2[1]);
	
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);//Limpa o Buffer de Cores e reinicia a matriz 
	glLoadIdentity();//carrega a matriz identidade
	
	//##Desenhando as retas#############################
	
	//cruz da direita
	int vertice1[2] = {250, 100};
	int vertice2[2] = {250, 200};
	drawLine(vertice1,vertice2);
	
	vertice1[0] = 210;vertice1[1] =  170;
	vertice2[0] = 290; vertice2[1] = 170;
	drawLine(vertice1,vertice2);
	
	//cruz da esquerda
	vertice1[0] = -250; vertice1[1] =  100;
	vertice2[0] = -250; vertice2[1] = 200;
	drawLine(vertice1,vertice2);
	
	vertice1[0] = -210;vertice1[1] =  170;
	vertice2[0] = -290; vertice2[1] = 170;
	drawLine(vertice1,vertice2);
	
	//cruz central
	vertice1[0] = 0; vertice1[1] =  210;
	vertice2[0] = 0; vertice2[1] = 300;
	drawLine(vertice1,vertice2);
	
	vertice1[0] = -40;vertice1[1] =  270;
	vertice2[0] = 40; vertice2[1] = 270;
	drawLine(vertice1,vertice2);
	
	glEnd();
	glFlush();// manda o OpenGl renderizar as primitivas
	
	//##Desenhando os triangulos########################
	
	//direito
	vertice1[0] = 250, vertice1[1] =100;
	vertice2[0] = 150, vertice2[1] = 0;
	int vertice3[2] = {350, 0};
	drawTriangle(vertice1, vertice2, vertice3);//função que desenha o triangulo na tela
	
	//esquerdo
	vertice1[0] = -250; vertice1[1] = 100;
	vertice2[0] = -150; vertice2[1] = 0;
	vertice3[0] = -350; vertice3[1] = 0;
	drawTriangle(vertice1, vertice2, vertice3);//função que desenha o triangulo na tela
	
	//central
	vertice1[0] = 0; vertice1[1] = 210;
	vertice2[0] = -150; vertice2[1] = 0;
	vertice3[0] = 150; vertice3[1] = 0;
	drawTriangle(vertice1, vertice2, vertice3);//função que desenha o triangulo na tela
	
	glEnd();
	glFlush();
	
	//##Desenhando os retangulos####################
	
	//direito
	vertice1[0] = 150; vertice1[1] = -300;
	vertice2[0] = 150; vertice2[1] = 0;
	vertice3[0] = 350; vertice3[1] = 0;
	int vertice4[2] = {350, -300};
	drawRectangle(0, 0, 1.0, vertice1, vertice2, vertice3, vertice4);
 	
 	//esquerdo
	vertice1[0] = -150; vertice1[1] = -300;
	vertice2[0] = -150; vertice2[1] = 0;
	vertice3[0] = -350; vertice3[1] = 0;
	vertice4[0] = -350, vertice4[1] = -300; 
	drawRectangle(0, 0, 1.0, vertice1, vertice2, vertice3, vertice4);
	
	//central
	vertice1[0] = 150; vertice1[1] = -300;
	vertice2[0] = 150; vertice2[1] = 0;
	vertice3[0] = -150; vertice3[1] = 0;
	vertice4[0] = -150, vertice4[1] = -300; 
	drawRectangle(1.0, 1.0, 0, vertice1, vertice2, vertice3, vertice4);
	
	//dentro do central
	vertice1[0] = 60; vertice1[1] = -300;
	vertice2[0] = 60; vertice2[1] = -100;
	vertice3[0] = -60; vertice3[1] = -100;
	vertice4[0] = -60, vertice4[1] = -300;  
	drawRectangle(0, 0, 0, vertice1, vertice2, vertice3, vertice4);
	
	glEnd();
	glFlush();
	
	//##Desenhando circulos#############################
	
	//direita
    desenhaCirculo(70,30,true,250,-100);
    
    //esquerda
    desenhaCirculo(70,30,true,-500,0);
    
    glEnd();
	glFlush();
	
}

//parametros: w= largura da tela, h=altura da tela
void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);// Reinicializa o sistema de coordenadas
	glLoadIdentity();//carrega a matriz identidade
	glViewport(0, 0, w, h);// Definindo o Viewport para o tamanho da janela
	glOrtho (-(w/2), (w/2),-(h/2),(h/2), -1 ,1);//utiliza largura e altura para dinamizar a projeção de acordo com o tam da janela
	glMatrixMode(GL_MODELVIEW);//desenhar no display
}

int main(int argc, char** argv){
    glutInit(&argc, argv);// Passagens de parametros C para o glut
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
    glutInitWindowSize (1000, 600);  // Tamanho da janela do OpenGL
    glutInitWindowPosition (150, 100); //Posicao inicial da janela do OpenGL
    glutCreateWindow ("Igreja 2D"); // Da nome para uma janela OpenGL
    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
    glutDisplayFunc(display); //funcao callback de desenho
	glutMainLoop(); // executa o loop do OpenGL
    return 0; // retorna 0 para o tipo inteiro da funcao main();
}
