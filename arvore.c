/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
*
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
* 
*/

#include "arvore.h"

#define KILO_BYTE 1024

typedef enum {
    FOLHA = 0,
    NO = 1
} TIPO;

struct arvore {
    unsigned char caracter;
    int peso;
    int tipo;
    Arv *esq;
    Arv *dir;
};


char retornaCaracterArvore(Arv *a) {
    return a->caracter;
}

int retornaPesoArvore(Arv *a) {
    return a->peso;
}

int ehFolhaArvore(Arv *a) {
    return a->tipo == FOLHA;
}

Lista *iniciaFolhas(int V[], int tam, int qtd) {
    // vetor que vai armazenar todas as folhas iniciais
    Lista *lista = criaLista();
    char c;

    for (int i = 0; i < tam; i++) {
        if (V[i] != 0) {
            c = (char)i;
            Arv *a = arv_cria_folha(c, V[i]);
            insereLista(lista, a, V[i]);
        }
    }

    return lista;
}

Arv *arv_cria_folha(char caracter, int frequencia) {
    Arv *folha = calloc(1, sizeof(Arv));

    folha->caracter = caracter;
    folha->peso = frequencia;
    folha->tipo = FOLHA;

    folha->esq = NULL;
    folha->dir = NULL;

    return folha;
}

Arv *arv_cria_no(Arv *e, Arv *d) {
    Arv *a = calloc(1, sizeof(Arv));

    a->caracter = '\0';
    a->tipo = NO;

    // o peso do nó vai ser a soma do peso dos nós inferiores esquerdo e direito
    a->peso = 0;

    if (e != NULL)
        a->peso += e->peso;

    if (d != NULL)
        a->peso += d->peso;

    a->esq = e;
    a->dir = d;

    return a;
}

Arv *organizaArvore(Lista *l) {
    while (!ehUnitariaLista(l)) {
        Arv *e = (Arv *)retiraLista(l);
        Arv *d = (Arv *)retiraLista(l);
        Arv *a = arv_cria_no(e, d);
        insereLista(l, a, a->peso);
    }

    Arv *arvore = (Arv *)retiraLista(l);

    return arvore;
}

Arv* percorreArvore(Arv *a, unsigned char bit) {
    if (!a)
        return NULL;
    
    if (bit == 0)
        return a->esq;
    else
        return a->dir;
}

void imprimeArvore(Arv *a) {
    if (!a)
        return;
    if (a->tipo == 1)
        printf("<%d", a->peso);
    else
        printf("<%c", a->caracter);

    imprimeArvore(a->esq);
    imprimeArvore(a->dir);
    printf(">");
}

void imprimeNo(void *ptr) {
    Arv *a = (Arv *)ptr;
    printf("%d %c %d", a->tipo, a->caracter, a->peso);
}

void liberaArvore(Arv* a) {
    if(!a) 
        return;

    liberaArvore(a->esq);
    liberaArvore(a->dir);
    free(a);
}

void escreveArvoreCabecalho(Arv *a, bitmap *bm) {
    if (!a) {
        bitmapAppendLeastSignificantBit(bm, 1); // indica que o no eh nulo entao nao escreve nada
        return;
    } else {
        bitmapAppendLeastSignificantBit(bm, 0); // indica que o no eh valido
        bitmapAppendLeastSignificantBit(bm, a->tipo); // indica o tipo do no

        if (a->tipo == FOLHA) {
            for (int i = 0; i < 8; i++) {
                bitmapAppendLeastSignificantBit(bm, (a->caracter >> i) & 1); // escreve o caractere se for folha
            }
        }
    }

    escreveArvoreCabecalho(a->esq, bm);
    escreveArvoreCabecalho(a->dir, bm);
}

Arv* leArvoreCabecalho(bitmap* bm, unsigned int* index) {
    if (bitmapGetBit(bm, *index) == 1) { // ja começa lendo o bit que indica se o no eh nulo e so continua se for valido
        *index += 1;
        return NULL;
    }

    *index += 1;

    Arv *a = calloc(1, sizeof(Arv));
    a->tipo = bitmapGetBit(bm, *index); // le o tipo do no sempre no indice passado
    *index += 1;

    if (a->tipo == FOLHA) {
        a->caracter = 0;
        for (int i = 0; i < 8; i++) {
            a->caracter |= bitmapGetBit(bm, *index) << i; // le bit a bit do caractere se for folha
            *index += 1;
        }
    }

    a->esq = leArvoreCabecalho(bm, index);
    a->dir = leArvoreCabecalho(bm, index);

    return a;
}


void criaTabelaCodificacao(bitmap **tabela, bitmap *bm, Arv *a) {
    if (!a)
        return;

    // entra na esquerda, insere 0 no bitmap apos encerrar recursao remove o ultimo bit
    if (a->esq) {
        bitmapAppendLeastSignificantBit(bm, 0);
        criaTabelaCodificacao(tabela, bm, a->esq);
        bitmapReduceLength(bm);
    }

    // entra na direita, insere 1 no bitmap apos encerrar recursao remove o ultimo bit
    if (a->dir) {
        bitmapAppendLeastSignificantBit(bm, 1);
        criaTabelaCodificacao(tabela, bm, a->dir);
        bitmapReduceLength(bm);
    }

    // se encontrar caractere (folha), escreve codigo ate o momento no indice adequado
    if (a->tipo == FOLHA) {
        bitmap *codigo = bitmapInit(KILO_BYTE);

        for (int i = 0; i < bitmapGetLength(bm); i++) {
            bitmapAppendLeastSignificantBit(codigo, bitmapGetBit(bm, i));
        }

        tabela[(int)a->caracter] = codigo;
    }

    return;
}

void liberaTabela(bitmap **tabela, int tam) {
    for (int i = 0; i < tam; i++) {
        if (tabela[i] != NULL) {
            bitmapLibera(tabela[i]);
            tabela[i] = NULL;
        }
    }
}

