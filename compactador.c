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
#define TAM_ASCII 256

int contaFrequenciaCaracteres(char *caminhoArquivo, int *V, int tam) {   
    char caminhoEntrada[TAM_NOME_CAMINHO];
    strcpy(caminhoEntrada, caminhoArquivo);
    
    FILE *entrada = fopen(caminhoEntrada, "rb");

    if (!entrada) {
        printf("Erro ao abrir o arquivo %s\n", caminhoEntrada);
        return 0;
    }

    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);

    while (1) {
        // lê 1MB de caracteres por vez do arquivo de entrada e armazena em um buffer
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, entrada);

        if (!bytesLidos)
            break;

        for (size_t i = 0; i < bytesLidos; i++) {
            int d = (int)charBuffer[i];
            V[d]++;
        }
    }

    free(charBuffer);
    fclose(entrada);

    // conta a quantidade de caracteres com frequência diferente de zero estao no vetor
    int qtd = 0;

    for (int i = 0; i < tam; i++) {
        if (V[i] != 0) {
            qtd++;
        }
    }

    return qtd;
}

int contaCaracteresTotal(char *caminhoArquivo) {
    char caminhoEntrada[TAM_NOME_CAMINHO];
    strcpy(caminhoEntrada, caminhoArquivo);
    
    FILE *entrada = fopen(caminhoEntrada, "rb");

    if (!entrada) {
        printf("Erro ao abrir o arquivo %s\n", caminhoEntrada);
        return 0;
    }

    int counter = 0;
    unsigned char *charBuffer = (unsigned char *)malloc(MEGA_BYTE);

    while (1) {
        // le 1MB de caracteres por vez do arquivo de entrada e armazena em um buffer
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, entrada);

        if (!bytesLidos)
            break;

        for (size_t i = 0; i < bytesLidos; i++){
            counter++;
        }
    }

    free(charBuffer);
    fclose(entrada);

    return counter;
}

Arv* criaArvoreCompactacao(char* caminhoEntrada) {
    char caminhoArquivo[TAM_NOME_CAMINHO];
    strncpy(caminhoArquivo, caminhoEntrada, TAM_NOME_CAMINHO - 1);

    int V[TAM_ASCII] = {0};
    int qtd = contaFrequenciaCaracteres(caminhoEntrada, V, TAM_ASCII);

    Lista *l = iniciaFolhas(V, TAM_ASCII, qtd);

    Arv *a = organizaArvore(l);

    liberaLista(l);

    return a;
}

bitmap** iniciaTabelaCodificacao(Arv* a) {
    bitmap **tabela = malloc(TAM_ASCII * sizeof(bitmap*)); 
    bitmap *bm = bitmapInit(MEGA_BYTE);

    for(int i=0; i< TAM_ASCII; i++) {
        tabela[i] = NULL;
    }

    criaTabelaCodificacao(tabela, bm, a);

    bitmapLibera(bm);

    return tabela;
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

    bitmap *bm = bitmapInit(MEGA_BYTE * 10); // inicia um bitmap grande pra jogar a arvore
    escreveArvoreCabecalho(a, bm);

    unsigned int bmSize = bitmapGetLength(bm);
    fwrite(&bmSize, sizeof(unsigned int), 1, compactado); // escreve tamanho do bitmap
    fwrite(bitmapGetContents(bm), sizeof(unsigned char), (bmSize + 7) / 8, compactado); // escreve o conteudo do bitmap

    fwrite(&bytes, sizeof(int), 1, compactado); // escreve o numero de bytes originais

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
        // le 1MB de caracteres por vez do arquivo de entrada e armazena em um buffer
        size_t bytesLidos = fread(charBuffer, sizeof(unsigned char), MEGA_BYTE, entrada);

        if (bytesLidos == 0) {
            break;
        }

        // varre o buffer e busca o caractere na tabela de codificacao
        for (size_t i = 0; i < bytesLidos; i++) {
            unsigned char caractere = charBuffer[i];
            bitmap *caractereCompactado = tabela[(int)caractere];

            // escreve no arquivo binario a versao compactada do caractere
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

