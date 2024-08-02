/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
* 
* ARQUIVO: TAD ARVORE
* INFO: RESPONSÁVEL PELA MANIPULAÇÃO DE ARVORE FEITA NO CODIGO. RESPONSÁVEL TAMBÉM PELA ESCRITA E LEITURA DE CABEÇALHO DE ÁRVORE NOS ARQUIVOS, ALÉM DA CRIAÇÃO DA TABELA DE CODIFICAÇÃO.
*
*/

#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "bitmap.h"

/**
 * @brief Struct que representa uma árvore binária de caracteres. Em seu conteúdo armazena o caractere, o peso do nó, e se a árvore é um nó ou uma folha.
 */
typedef struct arvore Arv;

/**
 * @brief Retorna o caractere contido na árvore.
 *
 * @param a a árvore.
 * @return o caractere contido na árvore.
 */
char retornaCaracterArvore(Arv *a);

/**
 * @brief Retorna o peso da árvore, que  corresponde a frequência do caracter em um arquivo.
 *
 * @param a a árvore.
 * @return o peso do nó (ou peso da árvore).
 */
int retornaPesoArvore(Arv *a);

/**
 * @brief Verifica se o nó da árvore é nó folha.
 *
 * @param a o nó da árvore.
 * @return retorna 0 se o nó em questão for um nó folha e retorna 1 se for nó interno.
 */
int ehFolhaArvore(Arv *a);

/**
 * @brief Inicializa as folhas da árvore com base na frequência dos caracteres no arquivo.
 *
 * @param V vetor com as frequências dos caracteres.
 * @param tam tamanho máximo do vetor.
 * @param qtd quantidade de caracteres com frequência diferente de zero.
 * @return uma lista de nós-folhas com os caracteres inicializados, ordenada de forma crescente de acordo com o peso de cada nó.
 */
Lista *iniciaFolhas(int V[], int tam, int qtd);

/**
 * @brief Cria uma árvore do tipo folha inicializada com o caractere e a frequência dele.
 *
 * @param caracter o caractere da folha.
 * @param frequencia a frequência do caractere.
 * @return a nova folha criada.
 */
Arv *arv_cria_folha(char caracter, int frequencia);

/**
 * @brief Cria um nó interno da árvore com subárvores esquerda e direita.
 *
 * @param e subárvore esquerda.
 * @param d subárvore direita.
 * @return o novo nó criado.
 */
Arv *arv_cria_no(Arv *e, Arv *d);

/**
 * @brief Cria uma árvore binária a partir lista de folhas já inicializadas.
 *
 * @param l a lista de folhas.
 * @return uma árvore binária de caracteres organizada pela frequência dos caracteres em um arquivo (peso).
 */
Arv *organizaArvore(Lista *l);

/**
 * @brief Anda na árvore para direita ou para a esquerda dependendo do bit de entrada.
 *
 * @param a o nó da árvore em questão.
 * @param bit o bit de input que dita a descida na árvore.
 * @return retorna o nó filho da esquerda da árvore caso o bit de entrada seja 0, e retorna o nó filho da direita da árvore caso o bit de entrada seja 1.
 */
Arv* percorreArvore(Arv *a, unsigned char bit);

/**
 * @brief Imprime o nó da árvore, com as seguintes informações: o caractere contido na árvore, a frequência do caractere (peso do nó) e o tipo do nó (se é nó-folha ou nó interno).
 *
 * @param ptr ponteiro para o nó a ser impresso.
 */
void imprimeNo(void *ptr);

/**
 * @brief Imprime a árvore com a notação textual <a<sae><sad>>.
 *
 * @param a a árvore a ser impressa.
 */
void imprimeArvore(Arv *a);

/**
 * @brief Libera a memória alocada para a árvore.
 *
 * @param a a árvore a ser liberada.
 */
void liberaArvore(Arv* a);

/**
 * @brief Escreve o cabeçalho da árvore em um arquivo.
 *
 * @param a a árvore.
 * @param bm o bitmap onde o cabeçalho será escrito.
 */
void escreveArvoreCabecalho(Arv *a, bitmap *bm);

/**
 * @brief Lê o cabeçalho da árvore de um arquivo.
 *
 * @param bm a bitmap de onde o cabeçalho será lido.
 * @param index o índice atual do bitmap.
 * @return a árvore lida do cabeçalho.
 */
Arv* leArvoreCabecalho(bitmap* bm, unsigned int* index);

/**
 * @brief Cria a tabela de codificação dos caracteres a partir da árvore da árvore binária de caracteres.
 *
 * @param tabela a tabela de códigos.
 * @param bm o bitmap temporário para armazenar o código.
 * @param a a árvore.
 */
void criaTabelaCodificacao(bitmap **tabela, bitmap *bm, Arv *a);

/**
 * @brief Libera a memória alocada para a tabela de códificação.
 *
 * @param tabela a tabela de códigos.
 * @param tam o tamanho da tabela.
 */
void liberaTabela(bitmap** tabela, int tam);

#endif

