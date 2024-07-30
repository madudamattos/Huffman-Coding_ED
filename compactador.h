#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"

void compactaArquivo(Arv *a, FILE *arquivo);

int bitmapToInt(bitmap *bm);


#endif