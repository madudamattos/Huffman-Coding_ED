#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct arvore Arv;

Arv** iniciaFolhas(int V[], int tam, int qtd);

Arv* arv_cria_folha(char caracter, int frequencia);

Arv* arv_cria_no(Arv* e, Arv* d);

void ordenaFrequenciaNos(Arv** nos, int qtd);

void imprimeVetorFolhas(Arv** folhas, int qtd);


#endif
