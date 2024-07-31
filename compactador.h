#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"

int contaCaracteres(char* caminhoArquivo, int *V, int tam, int *bytes);

void imprimeVetorFrequencia(int *V, int tam);

void compactaArquivo(Arv *a, FILE *arquivo, int qtd);

#endif