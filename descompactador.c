/*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
*
*/ 

#include "descompactador.h"

#define MEGA_BYTE (1024 * 1024)

void descompactaArquivo(FILE *arquivo, char *caminhoSaida) {
    FILE *arquivoSaida = fopen(caminhoSaida, "wb");

    if (!arquivoSaida) {
        printf("Erro ao abrir o arquivo %s\n", caminhoSaida);
        return;
    }

    // le o tamanho do bitmap
    unsigned int bmSize;
    if (fread(&bmSize, sizeof(unsigned int), 1, arquivo) != 1) {
        printf("Erro ao ler o tamanho do bitmap.\n");
        fclose(arquivoSaida);
        return;
    }

    // calcular o tamanho do bitmap em bytes
    unsigned int bmSizeInBytes = (bmSize + 7) / 8;

    // aqui ele cria o contents do bitmap pra jogar nele depois
    unsigned char *bmContents = (unsigned char *)malloc(bmSizeInBytes);
    if (!bmContents) {
        printf("Erro ao alocar memória para o bitmap.\n");
        fclose(arquivoSaida);
        return;
    }

    // le o conteúdo do bitmap
    if (fread(bmContents, sizeof(unsigned char), bmSizeInBytes, arquivo) != bmSizeInBytes) {
        printf("Erro ao ler o conteúdo do bitmap.\n");
        free(bmContents);
        fclose(arquivoSaida);
        return;
    }

    // inicializa o bitmap com o conteudo que foi lido
    bitmap *bm = bitmapInit(bmSize);
    for (unsigned int i = 0; i < bmSize; i++) {
        unsigned char bit = (bmContents[i / 8] >> (7 - (i % 8))) & 0x01;
        bitmapAppendLeastSignificantBit(bm, bit);
    }
    free(bmContents);

    // le a arvore de volta do bitmap
    unsigned int bitIndex = 0;
    Arv *a = leCabecalho(bm, &bitIndex);

    if (!a) {
        printf("Erro ao ler o cabeçalho\n");
        bitmapLibera(bm);
        fclose(arquivoSaida);
        return;
    }

    // le o numero de bytes originais pra nao acessar o resto
    int bytes;
    if (fread(&bytes, sizeof(int), 1, arquivo) != 1) {
        printf("Erro ao ler o número de bytes originais.\n");
        bitmapLibera(bm);
        fclose(arquivoSaida);
        return;
    }

    Arv *noAtual = a;
    unsigned char byte;
    int bytesEscritos = 0;
    unsigned char bitBuffer = 0;

    // passa pelo arquivo bit a bit
    while (fread(&byte, sizeof(unsigned char), 1, arquivo) == 1) {
        for (int bit = 7; bit >= 0; bit--) {
            unsigned char mask = 1 << bit;
            unsigned char bitValue = (byte & mask) >> bit;

            // se escreveu todos os bytes, para
            if (bytesEscritos == bytes)
                break;
            
            // navega na arvore com base no bit
            noAtual = percorreArvore(noAtual, bitValue);

            // se achou folha escreve o caractere
            if (ehFolhaArvore(noAtual)) {
                unsigned char c = retornaCaracterArvore(noAtual);
                fwrite(&c, sizeof(unsigned char), 1, arquivoSaida);
                noAtual = a; // retorna pro inicio da arvore para o próximo caractere
                bytesEscritos++;
            }
        }
    }

    bitmapLibera(bm);
    liberaArvore(a);
    fclose(arquivoSaida);
}
