#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


struct celula{
    void* conteudo;
    int peso;
    Celula* ant;
    Celula* prox;
};

struct lista{
  int TAM; 
  Celula* prim;
  Celula* ult;  
};

Lista* criaLista(){
    Lista* novaLista = (Lista*) calloc(1, sizeof(Lista));
    if (novaLista != NULL) {
        novaLista->TAM = 0;
        novaLista->prim = NULL;
        novaLista->ult = NULL;
    }
    return novaLista;
}

void insereLista(Lista* l, void* a, int peso){
    Celula* novaCelula = (Celula*) calloc(1,sizeof(Celula));

    if (novaCelula == NULL) {
        fprintf(stderr, "Erro: não foi possível alocar memória para nova célula.\n");
        exit(EXIT_FAILURE);
    }

    novaCelula->conteudo = a;
    novaCelula->peso = peso;
    novaCelula->ant = NULL;
    novaCelula->prox = NULL;

    if (l->prim == NULL) { // Lista vazia
        l->prim = novaCelula;
        l->ult = novaCelula;
    } else {
        Celula* atual = l->prim;
        // Varre a lista até encontrar a última célula cujo peso seja menor ou igual a do objeto a ser inserido
        while (atual != NULL && atual->peso <= peso) {
            atual = atual->prox;
        }

        if (atual == NULL) { // Caso a inserção seja no final da lista
            novaCelula->ant = l->ult;
            l->ult->prox = novaCelula;
            l->ult = novaCelula;
        } else {
            if (atual->ant == NULL) { // Caso a inserção seja no início da lista
                novaCelula->prox = l->prim;
                l->prim->ant = novaCelula;
                l->prim = novaCelula;
            } else { // Caso a inserção seja no meio da lista
                novaCelula->ant = atual->ant;
                novaCelula->prox = atual;
                atual->ant->prox = novaCelula;
                atual->ant = novaCelula;
            }
        }
    }

    l->TAM++;
}

void* retiraLista(Lista* l){
    if (l->prim == NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }

    Celula* atual = l->prim;
    void* elemento = atual->conteudo;

    l->prim = l->prim->prox;

    if(!l->prim){
        l->ult = NULL;
    } else {
        l->prim->ant = NULL;
    }
    
    free(atual);

    l->TAM--;

    return elemento;
}

void imprimeLista(Lista* l, void (*imprimeElemento)(void*)) {
    if (l->prim == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Celula* atual = l->prim;
    while (atual != NULL) {
        imprimeElemento(atual->conteudo);
        printf("\n");
        atual = atual->prox;
    }
    printf("\n");
}

int ehVaziaLista(Lista* l){
    return (l->prim == NULL);
}

int ehUnitariaLista(Lista* l){
    return (l->prim != NULL && l->prim == l->ult);
}

void liberaLista(Lista* l) {
    Celula* atual = l->prim;
    while (atual != NULL) {
        Celula* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(l);
}
