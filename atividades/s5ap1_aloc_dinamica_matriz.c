/*
[S5AP1] Alocação dinâmica de matriz
    Implemente um programa em C que, ao iniciar, leia na função main() dois números inteiros do teclado. O primeiro
    representa a quantidade de linhas e o segundo a quantidade de colunas de uma matriz que será alocada dinamicamente.
    Assim como feito no exercício dos vetores, implemente uma função que recebe esses dois números inteiros como
    parâmetro e aloca dinamicamente uma matriz. A matriz deve, obrigatoriamente, ser iniciada com zero.
*/

#include <stdio.h>
#include <stdlib.h>

int **criar_matriz(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL;

    int **new_matriz = (int **) calloc(linhas, sizeof(int *));

    for (int i = 0; i < linhas; i++) { *(new_matriz + i) = (int *) calloc(colunas, sizeof(int)); }

    return new_matriz;
}

int main(void) {
    int quat_linhas = 0, quat_colunas = 0;
    int **matriz_aloc = NULL;

    printf("Insira dois numeros de quatidades de linhas e colunas:\n Linhas -> ");
    scanf("%d", &quat_linhas);
    printf(" Colunhas -> ");
    scanf("%d", &quat_colunas);

    matriz_aloc = criar_matriz(quat_linhas, quat_colunas);

    if (matriz_aloc == NULL) {
        printf("ERRO: Matriz nao foi criado ou quantidade e invalida.\n\n");
        free(matriz_aloc);
        return 0;
    }

    printf("Insira os valores cada linha:\n");
    for (int i = 0; i < quat_linhas; i++) {
        int *linha = *(matriz_aloc + i);

        for (int j = 0; j < quat_colunas; j++) {
            printf(" [%d][%d] -> ", i, j);
            scanf("%d", linha + j);
        }
        printf("\n");
    }

    printf("Exibir os valores cada linha:\n");
    for (int i = 0; i < quat_linhas; i++) {
        int *linha = *(matriz_aloc + i);

        for (int j = 0; j < quat_colunas; j++) { printf(" [%d][%d] => %d\n", i, j, *(linha + j)); }
        printf("\n");
    }

    for (int i = 0; i < quat_linhas; i++) { free(*(matriz_aloc + i)); }

    free(matriz_aloc);
    matriz_aloc = NULL;

    return 0;
}
