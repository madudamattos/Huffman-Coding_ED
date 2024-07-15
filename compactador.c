#include "compactador.h"

void compactaArquivo(Arv *a, FILE *arquivo)
{
    FILE *compactado = fopen("compactado.bin", "wb");
    escreveCabecalho(a, compactado);

    int fim = -1;
    fwrite(&fim, sizeof(int), 1, compactado);

    fclose(compactado);
}
