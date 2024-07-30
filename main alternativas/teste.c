// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     FILE *txtFile = fopen("teste.txt", "r");
//     if (txtFile == NULL) {
//         perror("Erro ao abrir arquivo de texto");
//         return 1;
//     }

//     FILE *binFile = fopen("teste.bin", "wb");
//     if (binFile == NULL) {
//         perror("Erro ao criar arquivo binário");
//         fclose(txtFile);
//         return 1;
//     }

//     int ch;
//     while ((ch = fgetc(txtFile)) != EOF) {
//         fputc(ch, binFile);
//     }

//     fclose(txtFile);
//     fclose(binFile);

//     printf("Conversão concluída.\n");
//     return 0;
// }
