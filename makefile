SHELL := /bin/bash

OS := $(shell uname -s)

all:
	make compactador
	make descompactador
	echo "Executáveis "compacta" e "descompacta" criados"

compactador:
	gcc -c compactador.c arvore.c lista.c bitmap.c mainCompacta.c
	gcc -o compacta compactador.o arvore.o lista.o bitmap.o mainCompacta.o

descompactador:
	gcc -c descompactador.c arvore.c lista.c bitmap.c mainDescompacta.c
	gcc -o descompacta descompactador.o arvore.o lista.o bitmap.o mainDescompacta.o

clean:
ifeq ($(OS),Linux)
	rm -rf *.o *.dSYM
else ifeq ($(OS),Darwin)
	rm -rf *.o *.dSYM
else ifeq ($(OS),Windows_NT)
	del /Q *.o *.dSYM
endif
