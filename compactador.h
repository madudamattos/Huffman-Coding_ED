#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"

int contaCaracteres(FILE *arquivo, int *V, int tam);

void imprimeVetorFrequencia(int *V, int tam);

void compactaArquivo(Arv *a, FILE *arquivo);

#endif