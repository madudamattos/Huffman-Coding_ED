#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "compactador.h"
#include "bitmap.h"

#define TAM_NOME_CAMINHO 100
#define TAM_VETOR 128
#define MEGA_BYTE 1024 * 1024

int contaCaracteres(FILE *arquivo, int *V);
void imprimeVetorFrequencia(int *V);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return 0;
    }

    char caminhoArquivo[TAM_NOME_CAMINHO];

    strncpy(caminhoArquivo, argv[1], TAM_NOME_CAMINHO - 1);

    FILE *arquivo = fopen(caminhoArquivo, "r");

    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoArquivo);
        return 0;
    }

    int V[TAM_VETOR];

    // inicializa o vetor com 0
    for (int i = 0; i < TAM_VETOR; i++)
    {
        V[i] = 0;
    }

    int qtd = contaCaracteres(arquivo, V);

    imprimeVetorFrequencia(V);

    Lista *l = iniciaFolhas(V, TAM_VETOR, qtd);

    // imprimeLista(l, imprimeNo);

    Arv *a = organizaArvore(l);

    imprimeArvore(a);

    compactaArquivo(a, arquivo);

    return 0;
}

// retorna a quantidade de caracteres presentes no vetor
int contaCaracteres(FILE *arquivo, int *V)
{
    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);

    while (1)
    {
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, arquivo);

        if (!bytesLidos)
            break;

        for (size_t i = 0; i < bytesLidos; i++)
        {
            int d = (int)charBuffer[i];
            V[d]++;
        }
    }

    free(charBuffer);

    int qtd = 0;

    for (int i = 0; i < TAM_VETOR; i++)
    {
        if (V[i] != 0)
        {
            qtd++;
        }
    }

    return qtd;
}

void imprimeVetorFrequencia(int *V)
{

    for (int i = 0; i < TAM_VETOR; i++)
    {
        if (V[i] != 0)
        {
            printf("%c: %d\n", i, V[i]);
        }
    }

    printf("\n");
}
