#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"

int contaCaracteres(char* caminhoArquivo, int *V, int tam, int *bytes);

void imprimeVetorFrequencia(int *V, int tam);

<<<<<<< HEAD
void compactaArquivo(Arv *a, bitmap** tabela, char *caminhoArquivo);
=======
void compactaArquivo(Arv *a, FILE *arquivo, int qtd);
>>>>>>> 07849ec65b379e6480c852d23fe32a7b984172bb

#endif