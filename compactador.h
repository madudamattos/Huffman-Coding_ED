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

/**
 * @brief Abre o arquivo de entrada, conta a frequência dos caracteres no arquivo e também a quantidade total de caracteres no arquivo. 
 *
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @param tam tamanho do vetor V, equivalente ao tamanho da tabela ASCII.
 * @param V vetor que armazena a frequência dos caracteres presentes no texto, onde o índice do vetor é o número do caractere na tabela ASCII. 
 * @param bytes variável que será atualizada na função para armazenar a quantidade de caracteres total presente no arquivo.
 * @return a quantidade de caracteres diferentes no texto.
 */
int contaCaracteres(char* caminhoArquivo, int *V, int tam, int *bytes);


/**
 * @brief Realiza todo o processo de compactação do arquivo, escrevendo o cabeçalho no arquivo de saída, e depois escrevendo todos os bits codificados utilizando a tabela. 
 *
 * @param a a árvore que vai ser usada para escrever o cabeçalho no arquivo.
 * @param tabela tabela de codificação de caracteres.  
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @param bytes quantidade de caracteres total presente no arquivo e entrada.
 */
void compactaArquivo(Arv *a, bitmap** tabela, char *caminhoArquivo, int bytes);

#endif