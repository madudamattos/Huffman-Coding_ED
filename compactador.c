#include "compactador.h"
#include <stdio.h>
#include <stdlib.h>

#define MEGA_BYTE (1024 * 1024)

void compactaArquivo(Arv *a, FILE *arquivo) {
    FILE *compactado = fopen("compactado.bin", "wb");
    escreveCabecalho(a, compactado);

    int fim = -1;
    fwrite(&fim, sizeof(int), 1, compactado);

    bitmap *tabela[256];
    bitmap *bm = bitmapInit(8);

    criaTabela(tabela, bm, a);

    // Abre o arquivo base, faz a leitura novamente e armazena no buffer
    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);

    while (1) {
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, arquivo);

        if (!bytesLidos)
            break;

        // Completa com um pseudocaracter no buffer quando terminar de ler, para indicar o final do conteúdo
        if (bytesLidos < MEGA_BYTE) {
            charBuffer[bytesLidos] = '\0';
        }

        // Consome o conteúdo do buffer e escreve no arquivo compactado
        for (size_t i = 0; i < bytesLidos; i+= 8) {
            // Verifica se há 8 bits restantes
            if (i + 8 > bytesLidos) {
                break;
            }

            // Forma um caractere de 8 bits a partir dos 8 caracteres (0s e 1s) no buffer
            bitmap *caractere = bitmapInit(8);

            for (int j = 0; j < 8; j++)
            {
                bitmapAppendLeastSignificantBit(caractere, charBuffer[i+j]);
            }

            // Converte o bitmap para um inteiro
            int indice = bitmapToInt(caractere);

            // Busca na tabela o bitmap equivalente ao caractere
            bitmap *caractereCompactado = tabela[indice];

            // Escreve o bitmap no arquivo compactado
            for (int j = 0; j < bitmapGetLength(caractereCompactado); j++) {
                unsigned char bit = bitmapGetBit(caractereCompactado, j);
                fwrite(&bit, sizeof(unsigned char), 1, compactado);
            }

            bitmapLibera(caractere);
        }
    }

    free(charBuffer);
    fclose(compactado);
}

int bitmapToInt(bitmap *bm) {
    int value = 0;
    for (int i = 0; i < bitmapGetLength(bm); i++) {
        value <<= 1; // Desloca os bits para a esquerda
        value |= bitmapGetBit(bm, i); // Adiciona o bit atual
    }
    return value;
}