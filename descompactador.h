/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
* 
* ARQUIVO: TAD DESCOMPACTADOR
* INFO: RESPONSÁVEL PELA DESCOMPACTAÇÃO DO ARQUIVO COMPACTADO PELO TAD COMPACTADOR.H
*
*/


#ifndef DESCOMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Recebe o caminho do arquivo de entrada compactado, e gera um arquivo descompactado equivalente ao original antes da compactação.
 *
 * @param arquivo arquivo de entrada a ser descompactado.
 * @param caminhoSaida caminho do diretório onde o arquivo de saída  vai ser gerado.
 */
void descompactaArquivo(FILE *arquivo, char *caminhoSaida);

#endif