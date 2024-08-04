 /*
*
* TAD REFERENTE AO TRABALHO DA DISCIPLINA DE ESTRUTURA DE DADOS I
* COMPACTADOR DE HUFFMAN
* 
* ALUNAS: BARBARA ALENCAR DE ARAUJO PEREIRA E MARIA EDUARDA NOIA MATTOS DE AZEVEDO
*
* MAIN COMPACTA: RESPONSÁVEL PELA CHAMADA DAS FUNÇÕES DE COMPACTAÇÃO DO ARQUIVO E GERAÇÃO DO ARQUIVO COMPACTADO FINAL .COMP
*
*/ 
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "arvore.h"
 #include "lista.h"
 #include "compactador.h"
 #include "bitmap.h"
 #define TAM_NOME_CAMINHO 300
 #define TAM_ASCII 256
 #define MEGA_BYTE 1024 * 1024

 int main(int argc, char *argv[]) {

     // etapa de leitura do arquivo e criação da árvore de compactação
     if (argc < 2) {
         printf("Uso: %s <nome_arquivo>\n", argv[0]);
         return 0;
     }

     char caminhoArquivo[TAM_NOME_CAMINHO];
     strncpy(caminhoArquivo, argv[1], TAM_NOME_CAMINHO - 1);
     Arv* a = criaArvoreCompactacao(caminhoArquivo);

     // etapa de criacao da tabela de compactação e realização da compactação do arquivo
     bitmap** tabela = iniciaTabelaCodificacao(a);
     int bytes = contaCaracteresTotal(caminhoArquivo);
    
     compactaArquivo(a, tabela, caminhoArquivo, bytes);
     printf("\nCompactação do arquivo %s realizada com sucesso!\n", caminhoArquivo);

     // liberação de memoria do programa 
     liberaArvore(a);
     liberaTabela(tabela, TAM_ASCII);
     return 0;
 }