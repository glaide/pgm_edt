//GRR 20184567
//Glaide de Lara Oliveira

#ifndef __pgmlbp__
#define __pgmlbp__
#include "struct.h"

int verifica_valor(int a, int b);

int multimatriz(int *m, int *doisN, img_pgm *img);
//int** doisn(int **matriz);
void doisn(int *matriz)
;
//int** calculo(int indiceI, int indiceJ, img_pgm *img, int **matriz);
void calculo(int indiceI, int indiceJ, img_pgm *img, int *matriz)
;
int verifica_valor(int a, int b);
void efeito(img_pgm *img);


#endif 