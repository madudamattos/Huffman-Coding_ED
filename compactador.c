/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
*
* ALUNAS: BARBARA ALENCAR E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
*
*/


#include "compactador.h"

#define MEGA_BYTE (1024 * 1024)
#define TAM_NOME_CAMINHO 100

// retorna a quantidade de caracteres presentes no vetor
int contaCaracteres(char *caminhoArquivo, int *V, int tam, int *bytes)
{   
    
    char caminhoEntrada[TAM_NOME_CAMINHO];
    strcpy(caminhoEntrada, caminhoArquivo);
    
    FILE *entrada = fopen(caminhoEntrada, "rb");

    if (!entrada)
    {
        printf("Erro ao abrir o arquivo %s\n", caminhoEntrada);
        return 0;
    }

    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);
    int counter = 0;

    while (1)
    {
        // lê 1MB de caracteres por vez do arquivo de entrada e armazena em um buffer
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, entrada);

        if (!bytesLidos)
            break;

        for (size_t i = 0; i < bytesLidos; i++)
        {
            int d = (int)charBuffer[i];
            V[d]++;
            counter++;
        }
    }

    free(charBuffer);
    fclose(entrada);
    *bytes = counter;


    // conta a quantidade de caracteres com frequência diferente de zero estao no vetor
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


void compactaArquivo(Arv *a, bitmap **tabela, char *caminhoArquivo, int bytes) {
    FILE *entrada = fopen(caminhoArquivo, "rb");

    if (!entrada) {
        printf("Erro ao abrir o arquivo %s\n", caminhoArquivo);
        return;
    }

    int tamCaminho = strlen(caminhoArquivo);
    char caminhoSaida[tamCaminho + 6];
    strcpy(caminhoSaida, caminhoArquivo);
    strcat(caminhoSaida, ".comp");

    FILE *compactado = fopen(caminhoSaida, "wb");

    if (!compactado) {
        printf("Erro ao abrir o arquivo compactado.bin\n");
        fclose(entrada);
        return;
    }

    bitmap *bm = bitmapInit(MEGA_BYTE * 10); // iniciar um bitmap grande pra jogar a arvore
    escreveCabecalho(a, bm);

    unsigned int bmSize = bitmapGetLength(bm);
    fwrite(&bmSize, sizeof(unsigned int), 1, compactado); // escreve tamanho do bitmap
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), (bmSize + 7) / 8, compactado); // escrever o conteudo do bitmap

    fwrite(&bytes, sizeof(int), 1, compactado); // escrever o número de bytes originais

    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);
    if (!charBuffer) {
        printf("Erro ao alocar memória para o buffer de caracteres.\n");
        bitmapLibera(bm);
        fclose(entrada);
        fclose(compactado);
        return;
    }

    unsigned char bitBuffer = 0;
    int bitCount = 0;

    // loop que escreve os bits no arquivo compactado
    while (1) {
        // lê 1MB de caracteres por vez do arquivo de entrada e armazena em um buffer
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, entrada);

        if (bytesLidos == 0) {
            break;
        }

        // varre o buffer e busca na tabela de codificação o caractere equivalente 
        for (size_t i = 0; i < bytesLidos; i++) {
            unsigned char caractere = charBuffer[i];
            bitmap *caractereCompactado = tabela[(int)caractere];

            // com o auxilio do bitmap, escreve no arquivo binario a versao compactada do caractere lido
            for (unsigned int j = 0; j < bitmapGetLength(caractereCompactado); j++) {
                unsigned char bit = bitmapGetBit(caractereCompactado, j);
                bitBuffer = (bitBuffer << 1) | bit;
                bitCount++;

                if (bitCount == 8) {
                    fwrite(&bitBuffer, sizeof(unsigned char), 1, compactado);
                    bitBuffer = 0;
                    bitCount = 0;
                }
            }
        }
    }

    // garante que os bits restantes no bitBuffer sejam escritos no arquivo compactado
    if (bitCount > 0) {
        bitBuffer <<= (8 - bitCount);
        fwrite(&bitBuffer, sizeof(unsigned char), 1, compactado);
    }

    free(charBuffer);
    bitmapLibera(bm);
    fclose(entrada);
    fclose(compactado);
}

