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

    int i;
    printf("\nB ");
    for (i = 0; i < bitmapGetLength(tabela['b']); i++)
    {
        printf("%d", bitmapGetBit(tabela['b'], i));
    }
    printf("\n");

    printf("M ");
    for (i = 0; i < bitmapGetLength(tabela['m']); i++)
    {
        printf("%d", bitmapGetBit(tabela['m'], i));
    }
    printf("\n");

    printf("O ");
    for (i = 0; i < bitmapGetLength(tabela['o']); i++)
    {
        printf("%d", bitmapGetBit(tabela['o'], i));
    }
    printf("\n");

    printf("E ");
    for (i = 0; i < bitmapGetLength(tabela['e']); i++)
    {
        printf("%d", bitmapGetBit(tabela['e'], i));
    }
    printf("\n");

    printf("S ");
    for (i = 0; i < bitmapGetLength(tabela['s']); i++)
    {
        printf("%d", bitmapGetBit(tabela['s'], i));
    }
    printf("\n");

    printf("ESPAÇO ");
    for (i = 0; i < bitmapGetLength(tabela[' ']); i++)
    {
        printf("%d", bitmapGetBit(tabela[' '], i));
    }
    printf("\n");
}
