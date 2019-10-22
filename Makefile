CC=gcc
#flags para warning, depuração e biblioteca de matematica
CFLAGS=-g -Wall -lm

#regras de ligação
nega = pgmnega.o openimg.o

rota = pgmrot.o openimg.o

lbp = pgmlbp.o openimg.o



%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) 

#variavel geral
all: pgmrotacao pgmnega pgmlbp
#regras de compilação
pgmnega: $(nega)
	$(CC) -o $@ $^ $(CFLAGS) 

pgmlbp: $(lbp)
	$(CC) -o $@ $^ $(CFLAGS)

pgmrotacao: $(rota)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY:	clean
#remove os arquivos temporarios
clean: 

	rm *.o 

#remove os executaveis
purge: 

	rm pgmrotacao pgmnega pgmlbp
