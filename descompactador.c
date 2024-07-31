#include "descompactador.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEGA_BYTE (1024 * 1024)

void descompactaArquivo(FILE *arquivo, char *caminhoSaida)
{
    FILE *arquivoSaida = fopen(caminhoSaida, "wb");

    if (!arquivoSaida)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoSaida);
        return;
    }

    Arv *a = leCabecalho(a, arquivo);

    int qtdChar;
    fread(&qtdChar, sizeof(int), 1, arquivo);

    printf("Quantidade de caracteres: %d\n", qtdChar);

    if (!a)
    {
        printf("Erro ao ler o cabeçalho\n");
        fclose(arquivoSaida);
        return;
    }

    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);
    if (!charBuffer)
    {
        printf("Erro ao alocar memória\n");
        fclose(arquivoSaida);
        return;
    }

    Arv *noAtual = a;
    size_t bytesLidos;
    int contaChar = 0;
    unsigned char byte;
    unsigned char mask;
    unsigned char bitValue;

    while ((bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, arquivo)) > 0)
    {
        for (size_t i = 0; i < bytesLidos; i++)
        {
            byte = charBuffer[i];
            for (int bit = 7; bit >= 0; bit--)
            {
                if (contaChar == qtdChar)
                    break;

                mask = 1 << bit;
                bitValue = (byte & mask) >> bit;

                // Navegar na árvore com base no bit
                noAtual = percorreArvore(noAtual, bitValue);

                // Se chegamos a uma folha, escrevemos o caractere no arquivo de saída
                if (ehFolhaArvore(noAtual))
                {
                    unsigned char c = retornaCaracterArvore(noAtual);
                    fwrite(&c, sizeof(unsigned char), 1, arquivoSaida);
                    contaChar++;
                    noAtual = a; // Retornar ao início da árvore para o próximo caractere
                }
            }
        }
    }

    free(charBuffer);
    fclose(arquivoSaida);
}
