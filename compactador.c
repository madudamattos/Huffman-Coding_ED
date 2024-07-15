#include "compactador.h"

void compactaArquivo(Arv *a, FILE *arquivo)
{
    FILE *compactado = fopen("compactado.bin", "wb");
    escreveCabecalho(a, compactado);

    int fim = -1;
    fwrite(&fim, sizeof(int), 1, compactado);

    bitmap *tabela[256];
    bitmap *bm = bitmapInit(8);

    criaTabela(tabela, bm, a);

    bitmap *texto[100000000];

    fclose(compactado);
}
