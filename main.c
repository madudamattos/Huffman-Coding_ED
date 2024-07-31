#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "compactador.h"
#include "descompactador.h"
#include "bitmap.h"

#define TAM_NOME_CAMINHO 300
#define TAM_ASCII 256
#define MEGA_BYTE 1024 * 1024


int main(int argc, char *argv[])
{
    // etapa de leitura do arquivo e criação da árvore de compactação
    if (argc < 2)
    {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return 0;
    }

    char caminhoArquivo[TAM_NOME_CAMINHO];
    strncpy(caminhoArquivo, argv[1], TAM_NOME_CAMINHO - 1);

<<<<<<< HEAD
    int V[TAM_ASCII] = {0};
    int qtd = contaCaracteres(caminhoArquivo, V, TAM_ASCII);
=======
    int bytes = 0;
    int V[TAM_VETOR];
    int qtd = contaCaracteres(argv[1], V, TAM_VETOR, &bytes);
>>>>>>> 07849ec65b379e6480c852d23fe32a7b984172bb

    Lista *l = iniciaFolhas(V, TAM_ASCII, qtd);

    Arv *a = organizaArvore(l);


    // etapa de criacao da tabela de compactação e realização da compactação do arquivo
    strncpy(caminhoArquivo, argv[1], TAM_NOME_CAMINHO - 1);
    
<<<<<<< HEAD
    bitmap *tabela[256] = {NULL}; 
    bitmap *bm = bitmapInit(MEGA_BYTE);
    criaTabela(tabela, bm, a);

    compactaArquivo(a, tabela, caminhoArquivo);
=======
    compactaArquivo(a, arquivo, bytes);
>>>>>>> 07849ec65b379e6480c852d23fe32a7b984172bb

    printf("Compactação de %s completa\n", caminhoArquivo);


    // etapa de finalização e liberação de memoria do programa 
    bitmapLibera(bm);
    liberaLista(l);
    liberaArvore(a);
    liberaTabela(tabela, TAM_ASCII);

    FILE *compactado = fopen("compactado.bin", "rb");

    descompactaArquivo(compactado, "descompactado.txt");

    fclose(compactado);

    return 0;
}
