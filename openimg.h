//GRR 20184567
//Glaide de Lara Oliveira


#ifndef __openimg__
#define __openimg__
#include "struct.h"
#include <stdio.h>

//funcao que obtem os valores da imagem
void parametros(img_pgm *img, char *nome);
//funcao que verifica se a img nao é nula
void verifica (FILE *pgm);
//funcao que aloca o tamanho da matriz
img_pgm *aloca (img_pgm *img, FILE *pgm);
//desaloca o espaço da matriz
void libera_matriz(img_pgm *img);
//funcao que salva a imagem 
void escreve_img (img_pgm *img, char *saida);
//funcao que ignora comentario
void ignora_comentario(FILE *pgm);
//funcao que libera o espaço de uma matriz3x3
void libera_matrizMenor(int **matriz);
int compara (const void* a,const void* b);




#endif
