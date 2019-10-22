//GRR 20184567
//Glaide de Lara Oliveira


#ifndef __pgmrot__
#define __pgmtot__
#include "struct.h"

// funcao que acha o novo tamanho da imagem rotacionada
img_pgm* tamanho(img_pgm *img,img_pgm *nova, float angulo);

// funcao que deixa a imagem com fundo branco
void zera_matriz(img_pgm *nova);

// funcao que rotaciona a nova imagem 
void rotacao(img_pgm *img, img_pgm *nova, float angulo, int x, int y);


#endif
