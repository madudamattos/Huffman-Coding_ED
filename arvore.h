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
 * @brief Retorna o peso da árvore.
 *
 * @param a A árvore.
 * @return O peso do nó (ou peso da árvore).
 */
int retornaPesoArvore(Arv *a);

/**
 * @brief Retorna o tipo da árvore, se é nó interno ou nó folha.
 *
 * @param a A árvore.
 * @return 1 se for nó interno e 0 se for nó folha.
 */
int retornaTipoArvore(Arv *a);


/**
 * @brief Inicializa as folhas da árvore com base nas frequências dos caracteres.
 *
 * @param V Vetor com as frequências dos caracteres.
 * @param tam Tamanho máximo do vetor.
 * @param qtd Quantidade de caracteres com frequência diferente de zero.
 * @return A lista de folhas inicializadas.
 */
Lista *iniciaFolhas(int V[], int tam, int qtd);

/**
 * @brief Cria uma folha da árvore.
 *
 * @param caracter O caractere da folha.
 * @param frequencia A frequência do caractere.
 * @return A nova folha criada.
 */
Arv *arv_cria_folha(char caracter, int frequencia);

/**
 * @brief Cria um nó da árvore com subárvores esquerda e direita.
 *
 * @param e Subárvore esquerda.
 * @param d Subárvore direita.
 * @return O novo nó criado.
 */
Arv *arv_cria_no(Arv *e, Arv *d);

/**
 * @brief Organiza a árvore a partir de uma lista de folhas.
 *
 * @param l A lista de folhas.
 * @return A árvore organizada.
 */
Arv *organizaArvore(Lista *l);

/**
 * @brief Imprime o nó da árvore.
 *
 * @param ptr Ponteiro para o nó a ser impresso.
 */
void imprimeNo(void *ptr);

/**
 * @brief Imprime a árvore.
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
 * @brief Cria a tabela de códigos a partir da árvore.
 *
 * @param tabela A tabela de códigos.
 * @param bm O bitmap temporário para armazenar o código.
 * @param a A árvore.
 */
void criaTabela(bitmap **tabela, bitmap *bm, Arv *a);

/**
 * @brief Libera a memória alocada para a tabela de códigos.
 *
 * @param tabela A tabela de códigos.
 * @param tam O tamanho da tabela.
 */
void liberaTabela(bitmap** tabela, int tam);

/**
 * @brief Imprime a tabela de códigos.
 *
 * @param tabela A tabela de códigos.
 */
void imprimeTabela(bitmap **tabela);

#endif

