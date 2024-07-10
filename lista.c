#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef void (*FuncaoImprime)(void*);

typedef struct celula{
    void* conteudo;
    int peso;
    Celula* ant;
    Celula* prox;
}Celula;

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

//insere em ordem crescente os elementos de acordo com o peso do nó. Pode ser acessado usando a função int retornaPesoArvore(Arv* a)
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
        while (atual != NULL && atual->peso < peso) {
            atual = atual->prox;
        }

        if (atual == NULL) { // Insere no final da lista
            novaCelula->ant = l->ult;
            l->ult->prox = novaCelula;
            l->ult = novaCelula;
        } else {
            if (atual->ant == NULL) { // Insere no início da lista
                novaCelula->prox = l->prim;
                l->prim->ant = novaCelula;
                l->prim = novaCelula;
            } else { // Insere no meio da lista
                novaCelula->ant = atual->ant;
                novaCelula->prox = atual;
                atual->ant->prox = novaCelula;
                atual->ant = novaCelula;
            }
        }
    }

    l->TAM++;
}

void retiraLista(Lista* l, void* conteudo){
    if (l->prim == NULL) {
        fprintf(stderr, "Erro: lista vazia, não é possível retirar elementos.\n");
        exit(EXIT_FAILURE);
    }

    Celula* atual = l->prim;
    while (atual != NULL && atual->conteudo != conteudo) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        fprintf(stderr, "Erro: elemento não encontrado na lista.\n");
        return;
    }

    if (atual->ant == NULL && atual->prox == NULL) { // Único elemento na lista
        l->prim = NULL;
        l->ult = NULL;
    } else if (atual->ant == NULL) { // Remover o primeiro elemento
        l->prim = atual->prox;
        l->prim->ant = NULL;
    } else if (atual->prox == NULL) { // Remover o último elemento
        l->ult = atual->ant;
        l->ult->prox = NULL;
    } else { // Remover elemento do meio da lista
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }

    free(atual);
    l->TAM--;
}

void imprimeLista(Lista* l, FuncaoImprime imprimeElemento) {
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

//diz se a lista possui apenas uma célula dentro dela
int ehUnitariaLista(Lista* l){
    return (l->prim != NULL && l->prim == l->ult);
}