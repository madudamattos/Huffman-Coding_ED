#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>


typedef struct lista Lista;

typedef struct celula Celula;

typedef void (*FuncaoImprime)(void*);


Lista* criaLista();

void insereLista(Lista* l, void* a, int peso);

void* retiraLista(Lista* l);

void imprimeLista(Lista* l, FuncaoImprime imprimeElemento);

int ehVaziaLista(Lista* l);

int ehUnitariaLista(Lista* l);

void liberaLista(Lista* l);

#endif