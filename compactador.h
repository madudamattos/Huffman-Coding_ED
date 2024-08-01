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
 * @brief Abre o arquivo de entrada e conta a frequência dos caracteres no arquivo.
 *
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @param tam tamanho do vetor V, equivalente ao tamanho da tabela ASCII.
 * @param V vetor que armazena a frequência dos caracteres presentes no texto, onde o índice do vetor é o número do caractere na tabela ASCII. 
 * @return a quantidade de caracteres diferentes arquivo.
 */
int contaFrequenciaCaracteres(char* caminhoArquivo, int *V, int tam);

/**
 * @brief Conta a quantidade total de caracteres no arquivo.
 *
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @return a quantidade total de caracteres no arquivo.
 */
int contaCaracteresTotal(char *caminhoArquivo);

/**
 * @brief Cria a árvore de compatação de huffman com o arquivo de entrada. Conta a frequencia dos caracteres de entrada e monta uma árvore binária com base neles. 
 *
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @return a arvore de compactação.
 */
Arv* criaArvoreCompactacao(char* caminhoEntrada);

/**
 * @brief Inicializa a tabela de codificação e chama a função de criar tabela para preenche-la. 
 *
 * @param caminhoArquivo caminho do arquivo de entrada.
 * @return a tabela de codificação.
 */
bitmap** iniciaTabelaCodificacao(Arv* a);

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