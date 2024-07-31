/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* ALUNAS: BARBARA ALENCAR E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
* 
* ARQUIVO 1/10: TAD LISTA
* INFO: RESPONSÁVEL PELA MANIPULAÇÃO DAS LISTAS ENCADEADAS UTILIZADAS NO CÓDIGO
*/


#ifndef LISTA_H
#define LISTA_H


#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Struct que representa a lista.
 */
typedef struct lista Lista;

/**
 * @brief Struct que representa a célula, o elemento unitário da lista, que armazena o conteúdo desejado. 
 */
typedef struct celula Celula;

/**
 * @brief Cria uma lista vazia, já alocando seu espaço de memória e inicializa com zero.
 *
 * @return A nova lista.
 */
Lista* criaLista();


/**
 * @brief Insere os elementos na lista em ordem crescente, de acordo com o peso da célula. Pode ser acessado usando a função int retornaPesoArvore(Arv* a)
 *
 * @param l A lista onde o elemento vai ser inserido.
 * @param a o elemento a ser inserido na lista. 
 * @param peso o peso do nó.
 */
void insereLista(Lista* l, void* a, int peso);

/**
 * @brief Retira o primeiro elemento da lista.
 *
 * @param l a lista de elementos.
 * @return o elemento retirado da lista.
 */
void* retiraLista(Lista* l);

/**
 * @brief Imprime a lista, utilizando a função de parâmetro para imprimir individualmente cada elemento contido na lista.
 *
 * @param l a lista de elementos.
 * @param FuncaoImprime a função de impressão dos elementos individuais da lista.
 */
void imprimeLista(Lista* l, void (*FuncaoImprime)(void*));

/**
 * @brief Verifica se a lista é vazia.
 *
 * @param nome a Lista a ser inspecionada.
 * @return retorna 1 se a lista for vazia e 0 caso contrário.
 */
int ehVaziaLista(Lista* l);

/**
 * @brief Verifica se a lista possui apenas 1 elemento.
 *
 * @param nome a Lista a ser inspecionada.
 * @return retorna 1 se a lista for unitária, e 0 caso contrário. 
 */
int ehUnitariaLista(Lista* l);

/**
 * @brief Libera toda a memória alocada para a lista, mas não libera os elementos da lista.
 *
 * @param l lista a ser liberada.
 */
void liberaLista(Lista* l);


#endif