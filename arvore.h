/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
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
 * @brief Struct que representa uma árvore binária de caracteres. Em seu conteúdo armazena o caractere, o peso dele, e se a árvore é um nó ou uma folha.
 */
typedef struct arvore Arv;

/**
 * @brief Retorna o caractere contido na árvore.
 *
 * @param a A árvore.
 * @return O caractere da árvore.
 */
char retornaCaracterArvore(Arv *a);

/**
 * @brief Retorna o peso da árvore, que  corresponde a frequência do caracter em um arquivo.
 *
 * @param a A árvore.
 * @return O peso do nó (ou peso da árvore).
 */
int retornaPesoArvore(Arv *a);

/**
 * @brief Verifica se o nó da árvore é nó folha ou nó interno.
 *
 * @param a o nó da árvore.
 * @return retorna 0 se o nó em questão for um nó folha e retorna 1 se for nó interno.
 */
int ehFolhaArvore(Arv *a);


/**
 * @brief Inicializa as folhas da árvore com base nas frequências dos caracteres.
 *
 * @param V Vetor com as frequências dos caracteres.
 * @param tam Tamanho máximo do vetor.
 * @param qtd Quantidade de caracteres com frequência diferente de zero.
 * @return Uma lista de nós-folhas com os caracteres inicializados, ordenada de forma crescente de acordo com o peso de cada nó.
 */
Lista *iniciaFolhas(int V[], int tam, int qtd);

/**
 * @brief Cria uma árvore do tipo folha inicializada com o caractere e a frequência dele.
 *
 * @param caracter O caractere da folha.
 * @param frequencia A frequência do caractere.
 * @return A nova folha criada.
 */
Arv *arv_cria_folha(char caracter, int frequencia);

/**
 * @brief Cria um nó interno da árvore com subárvores esquerda e direita.
 *
 * @param e Subárvore esquerda.
 * @param d Subárvore direita.
 * @return O novo nó criado.
 */
Arv *arv_cria_no(Arv *e, Arv *d);

/**
 * @brief Cria uma árvore binária a partir lista de folhas já inicializadas.
 *
 * @param l A lista de folhas.
 * @return Uma árvore binária de caracteres organizada pela frequência dos caracteres em um arquivo (peso).
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
 * @param ptr Ponteiro para o nó a ser impresso.
 */
void imprimeNo(void *ptr);

/**
 * @brief Imprime a árvore com a notação textual <a<sae><sad>>.
 *
 * @param a A árvore a ser impressa.
 */
void imprimeArvore(Arv *a);

/**
 * @brief Libera a memória alocada para a árvore.
 *
 * @param a A árvore a ser liberada.
 */
void liberaArvore(Arv* a);

/**
 * @brief Retorna a altura da árvore.
 *
 * @param a A árvore.
 * @return A altura da árvore.
 */
int arv_altura (Arv* a);

/**
 * @brief Escreve o cabeçalho da árvore em um arquivo.
 *
 * @param a A árvore.
 * @param arquivo O arquivo onde o cabeçalho será escrito.
 */
void escreveCabecalho(Arv *a, FILE *arquivo);

/**
 * @brief Lê o cabeçalho da árvore de um arquivo.
 *
 * @param a A árvore.
 * @param arquivo O arquivo de onde o cabeçalho será lido.
 * @return A árvore lida do cabeçalho.
 */
Arv *leCabecalho(Arv *a, FILE *arquivo);

/**
 * @brief Cria a tabela de codificação dos caracteres a partir da árvore da árvore binária de caracteres.
 *
 * @param tabela A tabela de códigos.
 * @param bm O bitmap temporário para armazenar o código.
 * @param a A árvore.
 */
void criaTabela(bitmap **tabela, bitmap *bm, Arv *a);

/**
 * @brief Libera a memória alocada para a tabela de códificação.
 *
 * @param tabela A tabela de códigos.
 * @param tam O tamanho da tabela.
 */
void liberaTabela(bitmap** tabela, int tam);

/**
 * @brief Imprime a tabela de codificação.
 *
 * @param tabela A tabela de codificação.
 */
void imprimeTabela(bitmap **tabela);

#endif

