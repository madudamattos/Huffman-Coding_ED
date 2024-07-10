#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct arvore Arv;

Lista* iniciaFolhas(int V[], int tam, int qtd);

Arv* arv_cria_folha(char caracter, int frequencia);

Arv* arv_cria_no(Arv* e, Arv* d);

void ordenaFrequenciaNos(Arv** nos, int qtd);

void imprimeVetorFolhas(Arv** folhas, int qtd);

void imprimeNo(void* ptr);

char retornaCaracterArvore(Arv* a);

int retornaPesoArvore(Arv* a);

int retornaTipoArvore(Arv* a);

#endif
