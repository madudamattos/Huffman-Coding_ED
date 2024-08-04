/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
*
* MAIN DESCOMPACTA: RESPONSÁVEL PELA CHAMADA DAS FUNÇÕES DE DESCOMPACTAÇÃO E A GERAÇÃO DO ARQUIVO ANÁLOGO AO ORIGINAL A PARTIR DO COMPACTADO .COMP
*
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "descompactador.h"
#include "bitmap.h"

#define TAM_NOME_CAMINHO 300
#define TAM_ASCII 256
#define MEGA_BYTE 1024 * 1024


int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return 0;
    }

    char caminhoEntrada[TAM_NOME_CAMINHO];
    strncpy(caminhoEntrada, argv[1], TAM_NOME_CAMINHO - 1);

    int tam = strlen(caminhoEntrada);
    unsigned char caminhoSaida[tam];
    strcpy(caminhoSaida, caminhoEntrada);
    caminhoSaida[tam - 5] = '\0';

    FILE *compactado = fopen(caminhoEntrada, "rb");

    if(!compactado) {
        printf("Nao foi possivel abrir o arquivo compactado!\n");
        return 0;
    }

    descompactaArquivo(compactado, caminhoSaida);

    fclose(compactado);

    return 0;
}
