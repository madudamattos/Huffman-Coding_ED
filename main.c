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

    int qtd = contaCaracteres(arquivo, V, TAM_VETOR);

    //imprimeVetorFrequencia(V);

    Lista *l = iniciaFolhas(V, TAM_VETOR, qtd);

    Arv *a = organizaArvore(l);

    //imprimeArvore(a);

    //printf("Altura Arvore: %d", arv_altura(a));

    compactaArquivo(a, arquivo);

    return 0;
}
