//GRR 20184567
//Glaide de Lara Oliveira

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "openimg.h"
#define lm 3

void parametros(img_pgm *img, char *nome)
{
    FILE *pgm;
    if (nome==NULL)
        pgm=stdin;
    else
        pgm=fopen(nome,"r+");
    verifica(pgm); 
    ignora_comentario(pgm);
    fscanf(pgm,"%s\n",img->tipo);

    ignora_comentario(pgm);
    fscanf(pgm,"%i %i\n", &img->coluna, &img->linha);

    ignora_comentario(pgm);
    fscanf(pgm,"%i\n",&img->cinza);
    
    ignora_comentario(pgm);
    img=aloca(img,pgm);
    fclose(pgm);
}   


void verifica (FILE *pgm)
{
    if (pgm==NULL)
    { 
            printf("Erro, formato invalido!\n");//caso exista algum erro na leitura da imagem
            exit(1); //sai da funcao para nao fazer mais coisas
    }
}


img_pgm  *aloca (img_pgm *img, FILE *pgm)
{
    // aloca um espaço de memoria para a matriz
    img->matriz = calloc( img->linha * img->coluna, sizeof(int));
    if (img->tipo[1]=='2')    
    {
        for (int i=0; i<img->linha;i++)
        for (int j=0; j<img->coluna;j++) //caso seja p2 apenas lê um int
            fscanf(pgm,"%i", &img->matriz[(i*img->coluna)+j]);
      
    }
    else
    {
        for (int i=0; i<img->linha;i++)
        for (int j=0; j<img->coluna;j++)
        { //caso n de dessa forma tentar com fgetc e fputc
            img->matriz[(i*img->coluna)+j]=fgetc(pgm); //matriz recebe o valor do char lido
        }
    }
        

    return img;
}

void libera_matriz(img_pgm *img)
{
    free(img->matriz);
}

void libera_matrizMenor(int **matriz)
{
    for (int i=0; i< lm; i++)
        free(matriz[i]);
    free(matriz);
}

/*aqui vai usar um valor que eu pego da linha de comando*/
void escreve_img (img_pgm *img, char *saida)
{
    FILE *pgm;
    if (saida==NULL) //para caso nao tenha um nome no -o
        pgm=stdout;
    else
        pgm=fopen(saida,"w+"); //abro a imagem e salva em *pgm
    fprintf(pgm,"%s\n",img->tipo); 
    fprintf(pgm,"%i %i\n", img->coluna, img->linha);
    fprintf(pgm,"%i \n",img->cinza);
    
    // verifica qual tipo de imagem deve imprimir 
    if (img->tipo[1]=='2')    
    {
        for (int i=0; i<img->linha; i++)
        for (int j=0; j<img->coluna; j++)
            fprintf(pgm, "%i ", img->matriz[(i*img->coluna) + j]);
    }
    else 
    {
        for (int i=0; i<img->linha; i++)
        for (int j=0; j<img->coluna; j++)
            fputc(img->matriz[(i*img->coluna) + j],pgm);
    }

}

void ignora_comentario(FILE *pgm)
{
    char lixo;
    lixo=fgetc(pgm); //recebe um caracter da imagem 
    do
    { 
        if (lixo == '#') //compara para saber se é um comentario
            while (lixo != '\n') //se for percorre ate o fim da linha
                lixo=fgetc(pgm);

        else 
            ungetc(lixo,pgm); //se nao é um comentario devolve o valor lido
        lixo=fgetc(pgm); //le um novo valor
    }   while (lixo=='#');
    ungetc(lixo,pgm); //devolve o ultimo lido
                
}

int compara (const void* a,const void* b)
{
    int *pa, *pb;
    pa = (int*)a;
    pb = (int*)b;

    if (*pa > *pb) return 1;
    if (*pa < *pb) return -1;
    return 0;

}

