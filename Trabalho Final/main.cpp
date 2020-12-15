//*********************************************************************
//  Codigo exemplo para aula pratica de Computacao Grafica
//  Assunto: Rasterizacao e Transformacoes Geometricas
//
//  Autor: Felipe da Rocha Torres
//*********************************************************************

// Bibliotecas utilizadas pelo OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Biblioteca com funcoes matematicas
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

//incluindo o arquivo de estruturas
#include "estruturas.h"


//constantes----------------------------------------------------
#define RETA 1
#define QUADRADO 2
#define TRIANGULO 3
#define POLIGONO 4
#define CIRCULO 5

// Variaveis Globais------------------------------------------------------------
bool click1 = false, click2 = false, click3 = false;
bool dois_pontos = true; //controlar se sera utilizdos dois pontos ou tres
bool desenhar = false; //controlar se sera feito o desenho ou pegar os pontos
bool poligono = false; //controlar se sera desenhado um poligono
double x_1, y_1, x_2, y_2, x_3, y_3;//variaveis das coordenadas
double  x_backup_poligono = -1.0, y_backup_poligono = -1.0, inicial[2] = { -1, -1};// variaveis de backup
int state = 0;//variavel para selecionar os desenhos a se fazer
int contador = 0;//contador de pontos
int ultimoDesenhado = 0;//variavel que guarda o identificador da ultima figura desenhada
int width = 800, height = 600; //Largura e altura da janela

// Lista encadeada de pontos------------------------------------------------------
// indica o primeiro elemento da lista
ponto * pontos = NULL;
ponto * pontosReta = NULL;


// Funcao para armazenar um ponto na lista---------------------------------
// Armazena como uma Pilha (empilha)
ponto * pushPonto(int x, int y, bool tipo)
{
	ponto * pnt;
	pnt = new ponto;
	pnt->x = x;
	pnt->y = y;
	pnt->tipo = tipo;
	pnt->prox = pontos;
	pontos = pnt;
	contador++;
	return pnt;
}

// Funcao para desarmazenar um ponto na lista
// Desarmazena como uma Pilha (desempilha)
ponto * popPonto()
{
	ponto * pnt;
	pnt = NULL;
	if(pontos != NULL)
	{
		pnt = pontos->prox;
		delete pontos;
		pontos = pnt;
	}
	return pnt;
}


// Declaracoes forward das funcoes utilizadas
void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void retaImediata(double x1, double y1, double x2, double y2);
void reducao_primeiro_octante(double x0, double y0, double x1, double y1);
void bresenham(double x1, double y1, double x2, double y2);
void drawPontos();


//importando cabeçalhos
#include "figuras.h"
#include "transformacoes.h"
#include "interface.h"


// Funcao Principal do C
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Passagens de parametro C para o glut
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
	glutInitWindowSize (width, height);  // Tamanho da janela do OpenGL
	glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
	glutCreateWindow ("Paint Felipe"); // Da nome para uma janela OpenGL
	init(); // Chama funcao init();
	glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
	glutKeyboardFunc(keyboard); //funcao callback do teclado
	glutMouseFunc(mouse); //funcao callback do mouse
	glutDisplayFunc(display); //funcao callback de desenho
	glutMainLoop(); // executa o loop do OpenGL
	return 0; // retorna 0 para o tipo inteiro da funcao main();
}

// Funcao com alguns comandos para a inicializacao do OpenGL;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
}

void reshape(int w, int h)
{
	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);

	width = w;
	height = h;
	glOrtho (0, w, 0, h, -1 , 1);

	// muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
	// quando estivermos a desenhar na tela)
	glMatrixMode(GL_MODELVIEW);
	click1 = true; //Para redesenhar os pixels selecionados
	click2 = true;
	click3 = true;
}

// Funcao usada na funcao callback para utilizacao das teclas normais do teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key)   // key - variavel que possui valor ASCII da tecla precionada
	{
	case 27: // codigo ASCII da tecla ESC
		exit(0); // comando pra finalizacao do programa
		break;
	}
}

//resetar o poligono para iniciar um novo desenho
void poligonoOFF()
{
	poligono = false;
	x_backup_poligono = -1.0;
	y_backup_poligono = -1.0;
}

//Funcao usada na funcao callback para a utilizacao do mouse
void mouse(int button, int state, int x, int y)
{
	int yc = height - y;
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//acessando menu
			if(yc >= 566 && yc <= 590 && x <= 34 && x >= 4)  
			{//fazer reta
				setEstado(1);//reta
				ultimoDesenhado =RETA;
				poligonoOFF();
			}
			else if(yc >= 536 && yc <= 560 && x <= 34 && x >= 4)
			{//fazer triangulo
				setEstado(3);//triangulo
				ultimoDesenhado =TRIANGULO;
				poligonoOFF();
			}
			else if(yc >= 506 && yc <= 530 && x <= 34 && x >= 4)
			{//fazer quadrilatero
				setEstado(2);//quadrilatero
				ultimoDesenhado =QUADRADO;
				poligonoOFF();
			}
			else if(yc >= 476 && yc <= 500 && x <= 34 && x >= 4)
			{//fazer poligono
				setEstado(4);//poligono
				ultimoDesenhado =POLIGONO;
				poligono = true;
			}
			else if(yc >= 446 && yc <= 470 && x <= 34 && x >= 4)
			{//fazer circulo
				setEstado(5);//circulo
				ultimoDesenhado =CIRCULO;
				poligono = true;
			}
			else if(yc >= 416 && yc <= 440 && x <= 34 && x >= 4)
			{//apagar os desenhos
				system("cls");
				printf("Desenhos apagados!\n\n");
				int i;
				for(i = 0; i <= contador; i++)
				{
					pontos = popPonto();
				}
				contador = 0;
				glutPostRedisplay();
			}
			else if(yc >= 356 && yc <= 380 && x <= 34 && x >= 4)
			{//transladar
				printf("Digite o valor da translacao em X e Y [ valorX valorY + enter]: ");
				double xt = 0, yt = 0;
				scanf("%lf %lf", &xt, &yt);
				translacao(xt, yt);
				glutPostRedisplay();
			}
			else if(yc >= 326 && yc <= 350 && x <= 34 && x >= 4)
			{//realizar escala
				printf("Digite o valor da escala: ");
				double xt = 0;
				scanf("%lf", &xt);
				escala(xt,ultimoDesenhado);
				glutPostRedisplay();
			}
			else if(yc >= 296 && yc <= 320 && x <= 34 && x >= 4)
			{//realizar cisalhamneto
				char resp = 'p';
				printf("%c\n",resp);
				while(resp != 'y' && resp != 'Y' && resp != 'x' && resp != 'X'){
					printf("Digite o eixo do cizalhamento:[y ou x]:");
					scanf(" %c",&resp);
				}
				double xt = 0;
				printf("Digite o valor do cizalhamento:");
				scanf("%lf", &xt);
				cisalhamento(xt,resp,ultimoDesenhado);
				glutPostRedisplay();
			}
			else if(yc >= 266 && yc <= 290 && x <= 34 && x >= 4)
			{//fazer a reflexao da figura
				char resp = 'p';
				while(resp != 'y' && resp != 'Y' && resp != 'x' && resp != 'X'){
					printf("Digite o eixo da reflexao:[y ou x]:");
					scanf(" %c",&resp);
				}
				reflexao(resp,ultimoDesenhado);
				glutPostRedisplay();
			}
			else if(yc >= 236 && yc <= 260 && x <= 34 && x >= 4)
			{//rotacionar a figura
				rotacao();
				glutPostRedisplay();
			}
			else   
			{ //desenhar as figuras

				if(dois_pontos && !desenhar && !poligono) //bresenham, quadrilatero,reta_imediata
				{
					switch (button)
					{
					case GLUT_LEFT_BUTTON:
						if (state == GLUT_DOWN)
						{
							if(click1)
							{
								click2 = true;
								x_2 = x;
								y_2 = height - y;
								printf("x2y2(%.0f,%.0f)\n", x_2, y_2);
								printf("----------------------\n");
								desenhar = true;
								glutPostRedisplay();
							}
							else
							{
								click1 = true;
								x_1 = x;
								y_1 = height - y;
								printf("x1y1(%.0f,%.0f)\n", x_1, y_1);
							}
						}
						break;

					default:
						break;
					}
				}
				//-------------------------------------------------------------------------
				if(!dois_pontos && !desenhar && !poligono) //triangulo
				{
					switch (button)
					{
					case GLUT_LEFT_BUTTON:
						if (state == GLUT_DOWN)
						{
							if(click1 && !click3)
							{
								click3 = true;
								x_2 = x;
								y_2 = height - y;
								printf("x2y2(%.0f,%.0f)\n", x_2, y_2);
							}
							else if(click3)
							{
								click2 = true;
								x_3 = x;
								y_3 = height - y;
								printf("x3y3(%.0f,%.0f)\n", x_3, y_3);
								printf("----------------------\n");
								desenhar = true;
								glutPostRedisplay();
							}
							else
							{
								click1 = true;
								x_1 = x;
								y_1 = height - y;
								printf("x1y1(%.0f,%.0f)\n", x_1, y_1);
							}
						}
						break;
					default:
						break;
					}
				}
				//-----------------------------------------------------------------------------
				if(dois_pontos && !desenhar && poligono)  //poligono
				{

					switch (button)
					{
					case GLUT_RIGHT_BUTTON:
						if (state == GLUT_DOWN)
						{
							click1 = true;
							x_1 = inicial[0];
							y_1 = inicial[1];
							printf("x1y1(%.0f,%.0f)\n", x_1, y_1);
							glutPostRedisplay();
						}
						break;

					case GLUT_LEFT_BUTTON:
						if (state == GLUT_DOWN)
						{
							click1 = true;
							x_1 = x;
							y_1 = height - y;
							printf("x1y1(%.0f,%.0f)\n", x_1, y_1);
							glutPostRedisplay();
						}
						break;

					default:
						break;
					}
				}
				//-----------------------------------------------------------------------------
				desenho(x, yc);
			}
		}
		break;
	default:
		break;
	}
}

// Funcao usada na funcao callback para desenhar na tela
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer de cores e reinicia a matriz
	glLoadIdentity();

	glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto

	desenhar_interface();
	
	glutSwapBuffers(); // manda o OpenGl renderizar as primitivas

}

//Funcao que desenha os pontos contidos em uma lista de pontos
void drawPontos()
{
	ponto * pnt;
	pnt = pontos;
	glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar
	while(pnt != NULL)
	{
		glVertex2i(pnt->x, pnt->y);
		pnt = pnt->prox;
	}
	glEnd();  // indica o fim do desenho
}
