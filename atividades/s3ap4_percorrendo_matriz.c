/*
[S3AP4] Percorrendo matrizes
    Escreva um programa em C que solicite ao usuário duas informações: a primeira é a quantidade de linhas de uma
    matriz. A segunda informação é a quantidade de colunas. Em seguida, usando aritmética de
    ponteiros(https://ufmt.dev/aed2/alocacao/aritmetica), o programa deve solicitar ao usuário que informe valores para
    preencher essas linhas e colunas.

    Após o preenchimento da matriz, o programa deve exibir o conteúdo da matriz, também percorrendo-a com o uso de
    aritmética de ponteiros.
*/

#include <stdio.h>

int main(void) {
    int linhas = 0, colunas = 0;
    printf("Insira valores para linhas e colunas:\n Linhas: -> ");
    scanf("%d", &linhas);
    printf(" Colunas: -> ");
    scanf("%d", &colunas);

    int matriz[linhas][colunas];

    printf("\n\nSelocionar valores matriz:\n\n");
    for (int i = 0; i < linhas; i++) {
        int *linha = *(matriz + i);
        for (int j = 0; j < colunas; j++) {
            printf("matriz[%d][%d] -> ", i, j);
            scanf("%d", linha + j);
        }
    }

    printf("\n\nExibir o conteudo da matriz:\n\n");
    for (int i = 0; i < linhas; i++) {
        int *linha = *(matriz + i);
        for (int j = 0; j < colunas; j++) { printf("matriz[%d][%d]: %d\n", i, j, *(linha + j)); }
    }

    return 0;
}