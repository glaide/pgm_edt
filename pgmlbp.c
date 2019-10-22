//GRR 20184567
//Glaide de Lara Oliveira


#include "openimg.h"
#include "struct.h"
#include "pgmlbp.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#define lm 3
#define cm 3
#define indice(n,i,j) (n*i+j) //n é largura 

int main (int argc, char **argv)
{
   
    int option; 
    
    char *entrada=NULL;
    char *saida=NULL;
    
    while((option=getopt(argc,argv,"i:o:")) > 0)
    {
        switch (option)
        {
            case 'i':
                entrada=optarg; //caso tenha a opção -i
            break;
            
            case 'o':
                saida=optarg; //caso tenha a opção -o
            break;

            default:
            fprintf(stderr,"Entrada inválida.\n");
            return (-1);
        }
    }
    // fazer um teste para saber se todos os parametros foram dados
     
    img_pgm *img=malloc(sizeof(img_pgm)); //aloca um espaço de memoria para a matriz que ira receber a imagem
    parametros(img,entrada); //funcao que salva os parametros da imagem
    //efeito lbp

    efeito(img);
    escreve_img(img,saida); //salva a nova imagem invertida
    libera_matriz(img);
}


void efeito(img_pgm *img)
{
    int j, i, c, l;
    l=img->linha;
    c=img->coluna;
    int vetor[9];
    int doisN[9];

    // passar por toda a matriz de 1 até tam-1 chamando a funcao calculo
    for (i=1; i< (l- 1); i++)
    for (j=1; j< (c- 1); j++)
    { 
        calculo(i,j, img, vetor);
        doisn(doisN);
        //recebe os valores 0 e 1
        img->matriz[(i*img->coluna) +j]=multimatriz(vetor,doisN,img);
    }


}

int multimatriz(int *m, int *doisN, img_pgm *img)
{
    //variavel recebera a soma de todos os valores
    int cont=0;
    for (int i=0; i<9; i++)
        cont=m[i]*doisN[i]+cont;   
    return cont;
}


//  valor do pixel sera maior ou menor que o valor do meio
int verifica_valor(int a, int b)
{
    if (a >= b)
        return 1;
    else 
        return 0;
}

//matriz com 0s e 1s
void calculo(int indiceI, int indiceJ, img_pgm *img, int *matriz)
{
    //valor para o meio e os valores ao lado
    int meio, val,k;
    meio=img->matriz[(indiceI* img->coluna) + indiceJ];
    k=0;

    //laço para calcular os 0's e 1's
    for (int i=(indiceI-1); i<(indiceI+2); i++)
    for (int j=(indiceJ-1); j<(indiceJ+2); j++)
    {
        val=img->matriz[indice(img->coluna,i,j)];
        //salva o valor da matriz original
        //calcula se é =0 ou =1
        matriz[k]=verifica_valor(val,meio);
        k++;
    }
   
}


//matriz com 2^n
void doisn(int *matriz)
{
    //variavel usanda para fazer 2^n
    int n=0;
    for (int i=0; i<9; i++)
    {
        //para caso seja o valor do meio
        if (i==5)
            matriz[i]=0;
        else 
        {
            matriz[i]=pow(2,n);
            n++;
        }
    }
}

