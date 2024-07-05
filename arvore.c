#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef enum{
    FOLHA = 0,
    NO = 1
} TIPO;

struct arvore{
    char caracter;
    int frequencia;
    int tipo;
    Arv* esq;
    Arv* dir;
};


//recebe o vetor com a frequencia dos caracteres, o tamanho máximo desse vetor e quantidade de caracteres com frequencia diferente de zero que serao convertidos em folhas
Arv** iniciaFolhas(int V[], int tam, int qtd)
{
    //vetor que vai armazenar todas as folhas iniciais
    Arv** folhas = calloc(qtd, sizeof(Arv*));
    int j=0;
    char c;

    for(int i=0; i<tam; i++)
    {
        if(V[i] != 0)
        {   
            c = (char)i;
            folhas[j] = arv_cria_folha(c, V[i]);
            j++;
        }
    }

    return folhas;
}

Arv* arv_cria_folha(char caracter, int frequencia)
{
    Arv* folha = calloc(1, sizeof(Arv));

    folha->caracter = caracter;
    folha->frequencia = frequencia;
    folha->tipo = FOLHA;

    folha->esq = NULL;
    folha->dir = NULL;

    return folha;
}

//cria uma árvore com subárvore esquerda e e subárvore direita d
Arv* arv_cria_no(Arv* e, Arv* d){
    Arv* a = calloc(1, sizeof(Arv));
    
    a->caracter = '\0';
    a->tipo = NO;


    //a frequencia do nó vai ser a soma da frequência dos nós inferiores esquerdo e direito
    a->frequencia = 0;
    if(e != NULL)
    {
        a->frequencia += e->frequencia; 
    }

    if(d != NULL)
    {
        a->frequencia += d->frequencia; 
    }

    a->esq = e;
    a->dir = d;

    return a;
}


//essas funções abaixo tem a função de fazer a primeira ordenação do vetor de folhas por frequencia em ordem crescente 
void troca(Arv** nos, int i, int j) {
    Arv* temp = nos[i];
    nos[i] = nos[j];
    nos[j] = temp;
}

int particiona(Arv** nos, int inicio, int fim) {
    int pivot = nos[fim]->frequencia;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (nos[j]->frequencia < pivot) {
            i++;
            troca(nos, i, j);
        }
    }

    troca(nos, i + 1, fim);
    return i + 1;
}

void quickSort(Arv** nos, int inicio, int fim) {
    if (inicio < fim) {
        int pi = particiona(nos, inicio, fim);
        quickSort(nos, inicio, pi - 1);
        quickSort(nos, pi + 1, fim);
    }
}

void ordenaFrequenciaNos(Arv** nos, int qtd) {
    quickSort(nos, 0, qtd - 1);
}

//--------------------------------------------

void imprimeVetorFolhas(Arv** folhas, int qtd)
{
    for(int i=0; i<qtd; i++)
    {
        printf("%c: %d\n", folhas[i]->caracter, folhas[i]->frequencia);
    }
}