//GRR 20184567
//Glaide de Lara Oliveira	

#include "struct.h"
#include <stdlib.h>
#include "pgmrot.h"
#include <math.h>
#include <string.h>
#include "openimg.h"
#include <getopt.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#define tam 4
#define pi 3.1415926
#define rad(a) ((a*pi)/180)

#define angx(angulo,x,y) (x*cos(angulo) - y*sin(angulo)) 
#define angy(angulo,x,y) (x*sin(angulo) + y*cos(angulo))



//ENTENDER O QUE EH A DIFERENÇA ENTRE AS IMAGENS
int main (int argc, char **argv)
{	
	int option;
	float angulo;
	char *entrada=NULL;
	char *saida=NULL;	
	
	while((option=getopt(argc,argv,"i:o:a:")) > 0)
	{
	    switch (option)
	    {
			/******MUDAR AS OPÇÕES DE LEITURA*******/
	        case 'i':
	            entrada=optarg; //caso tenha a opção -i
	        break;	

	        case 'o':
	            saida=optarg; //caso tenha a opção -o
	        break;

			case 'a': 
			{	//caso n seja passado um valor
				if (optarg==NULL)
					angulo=30; 
				 
				else //converte para ser tratado como int
					angulo=atoi(optarg);
			}
			
	    }
	}


	if (angulo<0)
		angulo=angulo+360;
	
    img_pgm *img=malloc(sizeof(img_pgm));
    parametros(img,entrada);

	/*FAZER TODAS AS FUNÇÕES RELACIONADAS A ANGULOS*/
	//aloca um espaço para a nova matriz	
	img_pgm *nova=malloc(sizeof(img_pgm));
	if (nova==NULL)
	{
		printf("Erro na alocação. Tente novamente!\n");
		exit(-1);
	}
	// achar o novo tamanho da matriz
	nova=tamanho(img,nova,angulo);


	//função que ira calcular cada novo pixel
    
	escreve_img(nova,saida);
    libera_matriz(img);
    libera_matriz(nova);
}

img_pgm* tamanho(img_pgm *img,img_pgm *nova, float angulo)
{	
	// ira salvos os novos angulos
	int vl[tam];
	int vc[tam];
	int altura, largura;
	int vlin[tam]={0,0,img->linha,img->linha};
	int vcol[tam]={0,img->coluna,0,img->coluna};
	
	
	//calculo pq é em radianos
	float x=rad(angulo);
	//ate aqui ok

	
	// calcula o novo angulo de cada coordenada 
	for (int i=0; i<tam; i++)
	{
		vl[i]=(angx(x,vlin[i],vcol[i]));
		vc[i]=(angy(x,vlin[i],vcol[i]));
	}
	
	/*o maior e menor valor dira qual eh o novo tamamho da imagem*/

	qsort(vl,4,sizeof(int),compara);
	qsort(vc,4,sizeof(int),compara);

	/*fazer a diferença de do maior para ter os novos tamanhos
	diferença de x é a nova altura e de y é a nova largura
	o primeiro w o último pq são o menor e maior valor*/
	altura=vl[3]-vl[0];
	largura=vc[3]-vc[0];
	
	// seta os novos valores de altura e largura
	nova->linha=altura;
	nova->coluna=largura;
	nova->cinza=img->cinza;
	strcpy(nova->tipo,img->tipo);

	//aloca um espaço para a nova matriz rotacionada
	// com mais espaço para não dar problema com alguns angulos
	nova->matriz=calloc(nova->linha * nova->coluna + (img->linha/2), sizeof(int));

	if (nova->matriz==NULL)
	{
		printf("Erro na alocação!\n");
		exit (-1);
	}
	
	// deixa a matriz em branco	
	zera_matriz(nova);
	
	//função que rotaciona todos os valores da matriz
	rotacao(img,nova,x,vl[0],vc[0]);
	
	// precisa retornar uma nova img alocada
	return nova;

}

void rotacao(img_pgm *img, img_pgm *nova, float angulo, int x, int y)
{
//rotacao conta feita x'=x*cos()-y*sin() e y'=x*sin()+y*cos()
	// novas variaveis de indice
	int indI, indJ;

	// vai caminhar por toda a matriz original
	for (int i=0; i<img->linha; i++)
	for (int j=0; j<img->coluna; j++)
	// o que eu recebo sao os indices rotacionados
	{
		//faz o calculo do novo angulo
		indI=angx(angulo,i,j)-x;
		indJ=angy(angulo,i,j)-y;

		// salvo nos indices rotacionados o valor na matriz dos indices originais
		//é necessário calcular a diferença do minimo para o novo indice, para que todos os valores caiam dentro do plano
		nova->matriz[((indI)*nova->coluna)+(indJ)]=img->matriz[(i*img->coluna)+j];
	}
}

void zera_matriz(img_pgm *nova)
{
	//zera todos os valores da matriz para que tenha o fundo branco
	for (int i=0; i<nova->linha; i++)
	for (int j=0; j<nova->coluna; j++)
		nova->matriz[(i* nova->coluna)+j]=255;

}