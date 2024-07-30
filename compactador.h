#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"

int contaCaracteres(char* caminhoArquivo, int *V, int tam);

void imprimeVetorFrequencia(int *V, int tam);

void compactaArquivo(Arv *a, bitmap** tabela, char *caminhoArquivo);

#endif