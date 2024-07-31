/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
*
* ALUNAS: BARBARA ALENCAR E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
* 
* ARQUIVO: TAD COMPACTADOR
* INFO: RESPONSAVEL POR ABRIR O ARQUIVO DE ENTRADA E FAZER A CONTAGEM DE CARACTERES, ASSIM COMO TAMBÉM UTILIZA DOS OUTROS TADS PARA GERAR O ARQUIVO BINARIO COMPACTADO
*
*/


#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contaCaracteres(char* caminhoArquivo, int *V, int tam, int *bytes);

void imprimeVetorFrequencia(int *V, int tam);

void compactaArquivo(Arv *a, bitmap** tabela, char *caminhoArquivo, int bytes);

#endif