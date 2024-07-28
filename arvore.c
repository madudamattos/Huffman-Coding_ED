#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "lista.h"

typedef enum
{
    FOLHA = 0,
    NO = 1
} TIPO;

struct arvore
{
    unsigned char caracter;
    int peso;
    int tipo;
    Arv *esq;
    Arv *dir;
};

// recebe o vetor com a frequencia dos caracteres, o tamanho máximo desse vetor e quantidade de caracteres com frequencia diferente de zero que serao convertidos em folhas
Lista *iniciaFolhas(int V[], int tam, int qtd)
{
    // vetor que vai armazenar todas as folhas iniciais
    Lista *lista = criaLista();
    char c;

    for (int i = 0; i < tam; i++)
    {
        if (V[i] != 0)
        {
            c = (char)i;
            Arv *a = arv_cria_folha(c, V[i]);
            insereLista(lista, a, V[i]);
        }
    }

    return lista;
}

Arv *arv_cria_folha(char caracter, int frequencia)
{
    Arv *folha = calloc(1, sizeof(Arv));

    folha->caracter = caracter;
    folha->peso = frequencia;
    folha->tipo = FOLHA;

    folha->esq = NULL;
    folha->dir = NULL;

    return folha;
}

// cria uma árvore com subárvore esquerda e e subárvore direita d
Arv *arv_cria_no(Arv *e, Arv *d)
{
    Arv *a = calloc(1, sizeof(Arv));

    a->caracter = '\0';
    a->tipo = NO;

    // o peso do nó vai ser a soma do peso dos nós inferiores esquerdo e direito
    a->peso = 0;
    if (e != NULL)
    {
        a->peso += e->peso;
    }

    if (d != NULL)
    {
        a->peso += d->peso;
    }

    a->esq = e;
    a->dir = d;

    return a;
}

void imprimeNo(void *ptr)
{
    Arv *a = (Arv *)ptr;
    printf("%d %c %d", a->tipo, a->caracter, a->peso);
}

char retornaCaracterArvore(Arv *a)
{
    return a->caracter;
}

int retornaPesoArvore(Arv *a)
{
    return a->peso;
}

int retornaTipoArvore(Arv *a)
{
    return a->tipo;
}

Arv *organizaArvore(Lista *l)
{
    while (!ehUnitariaLista(l))
    {
        Arv *e = (Arv *)retiraLista(l);
        Arv *d = (Arv *)retiraLista(l);
        Arv *a = arv_cria_no(e, d);
        insereLista(l, a, a->peso);
    }

    Arv *arvore = (Arv *)retiraLista(l);

    return arvore;
}

void imprimeArvore(Arv *a)
{
    if (!a)
    {
        return;
    }
    if (a->tipo == 1)
    {
        printf("<%d", a->peso);
    }
    else
    {
        printf("<%c", a->caracter);
    }

    imprimeArvore(a->esq);
    imprimeArvore(a->dir);
    printf(">");
}

void escreveCabecalho(Arv *a, FILE *arquivo)
{
    if (!a)
    {
        int nulo = 1;
        fwrite(&nulo, sizeof(int), 1, arquivo);
        return;
    }
    else
    {
        int valido = 0;
        fwrite(&valido, sizeof(int), 1, arquivo);
        fwrite(&a->tipo, sizeof(int), 1, arquivo);
        fwrite(&a->peso, sizeof(int), 1, arquivo);

        if (a->tipo == 0)
            fwrite(&a->caracter, sizeof(char), 1, arquivo);
    }

    escreveCabecalho(a->esq, arquivo);
    escreveCabecalho(a->dir, arquivo);
}

Arv *leCabecalho(Arv *a, FILE *arquivo)
{
    int nulo;

    fread(&nulo, sizeof(int), 1, arquivo);

    if (nulo == -1)
        return a;
    else if (!nulo)
    {
        int tipo, peso;
        char caracter;

        fread(&tipo, sizeof(int), 1, arquivo);
        fread(&peso, sizeof(int), 1, arquivo);

        if (tipo == FOLHA)
        {
            fread(&caracter, sizeof(char), 1, arquivo);
            a = arv_cria_folha(caracter, peso);
        }
        else
        {
            a = arv_cria_folha('\0', peso);
            a->tipo = NO;
        }

        a->esq = leCabecalho(a->esq, arquivo);
        a->dir = leCabecalho(a->dir, arquivo);
    }

    return a;
}

void criaTabela(bitmap **tabela, bitmap *bm, Arv *a)
{
    if (!a)
        return;

    // entra na esquerda, insere 0 no bitmap apos encerrar recursao remove o ultimo bit
    if (a->esq)
    {
        bitmapAppendLeastSignificantBit(bm, 0);
        criaTabela(tabela, bm, a->esq);
        bitmapReduceLength(bm);
    }

    // entra na direita, insere 1 no bitmap apos encerrar recursao remove o ultimo bit
    if (a->dir)
    {
        bitmapAppendLeastSignificantBit(bm, 1);
        criaTabela(tabela, bm, a->dir);
        bitmapReduceLength(bm);
    }

    // se encontrar caractere (folha), escreve codigo ate o momento no indice adequado
    if (a->tipo == FOLHA)
    {
        bitmap *codigo = bitmapInit(8);

        for (int i = 0; i < bitmapGetLength(bm); i++)
        {
            bitmapAppendLeastSignificantBit(codigo, bitmapGetBit(bm, i));
        }

        tabela[(int)a->caracter] = codigo;
        printf(" %c ", a->caracter);
    }

    return;
}