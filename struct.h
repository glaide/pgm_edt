//GRR 20184567
//Glaide de Lara Oliveira


#ifndef __struct__
#define __struct__		

typedef struct img_pgm
{
	char tipo[3];
	int linha;
	int coluna;
	int cinza;
	int *matriz;
}img_pgm;


#endif
