#include "compactador.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

#define MEGA_BYTE (1024 * 1024)


// retorna a quantidade de caracteres presentes no vetor
int contaCaracteres(FILE *arquivo, int *V, int tam)
{
    // inicializa o vetor com 0
    for (int i = 0; i < tam; i++)
    {
        V[i] = 0;
    }

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

    for (int i = 0; i < tam; i++)
    {
        if (V[i] != 0)
        {
            qtd++;
        }
    }

    return qtd;
}

void imprimeVetorFrequencia(int *V, int tam)
{

    for (int i = 0; i < tam; i++)
    {
        if (V[i] != 0)
        {
            printf("%c: %d\n", i, V[i]);
        }
    }

    printf("\n");
}


// VERSAO CHATGPT, NAO TA FUNCIONANDO MAS DA PRA APROVEITAR
// void compactaArquivo(Arv *a, FILE *arquivo) {
//     FILE *compactado = fopen("compactado.bin", "wb");
//     escreveCabecalho(a, compactado);

//     int fim = -1;
//     fwrite(&fim, sizeof(int), 1, compactado);

//     bitmap *tabela[256];
//     bitmap *bm = bitmapInit(MEGA_BYTE);

//     criaTabela(tabela, bm, a);

//     unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);
//     unsigned char bitBuffer = 0;
//     int bitCount = 0;

//     while (1) {
//         size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, arquivo);

//         if (!bytesLidos)
//             break;

//         for (size_t i = 0; i < bytesLidos; i++) {
//             unsigned char caractere = charBuffer[i];
//             bitmap *caractereCompactado = tabela[(int)caractere];

//             printf("Caractere original: %c\n", caractere);
//             for (unsigned int j = 0; j < bitmapGetLength(caractereCompactado); j++) {
//                 unsigned char bit = bitmapGetBit(caractereCompactado, j);
//                 printf("%d", bit);
//                 bitBuffer = (bitBuffer << 1) | bit;
//                 bitCount++;

//                 if (bitCount == 8) {
//                     fwrite(&bitBuffer, sizeof(unsigned char), 1, compactado);
//                     bitBuffer = 0;
//                     bitCount = 0;
//                 }
//             }
//             printf("\n");
//         }
//     }

//     if (bitCount > 0) {
//         bitBuffer <<= (8 - bitCount);
//         fwrite(&bitBuffer, sizeof(unsigned char), 1, compactado);
//     }

//     free(charBuffer);
//     fclose(compactado);
// }


// minha versao teste mas nao ta funcionando tbm kkkkkkkkkk

void compactaArquivo(Arv *a, FILE *arquivo) {
    FILE *compactado = fopen("compactado.bin", "wb");
    escreveCabecalho(a, compactado);

    int fim = -1;
    fwrite(&fim, sizeof(int), 1, compactado);

    bitmap *tabela[256];
    bitmap *bm = bitmapInit(MEGA_BYTE);

    criaTabela(tabela, bm, a);

    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);

    while (1) {
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, arquivo);

        if (!bytesLidos)
            break;

        for (size_t i = 0; i < bytesLidos; i++) {
            unsigned char caractere = charBuffer[i];
            fwrite(&caractere, sizeof(unsigned char), 1, compactado);
        }
    }

    free(charBuffer);
    fclose(compactado);
}


