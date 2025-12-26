/*
[S5AP2] Realocação de matriz
    Agora, implemente uma função que reajusta o tamanho da matriz, considerando como entrada o número de linhas e
    colunas. Depois, imprima o conteúdo da matriz.
*/

#include <stdio.h>
#include <stdlib.h>

int **criar_matriz(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL;

    int **new_matriz = (int **) calloc(linhas, sizeof(int *));
    if (new_matriz == NULL) return NULL;

    for (int i = 0; i < linhas; i++) { *(new_matriz + i) = (int *) calloc(colunas, sizeof(int)); }

    return new_matriz;
}

int nume = 0;
int numerador() {
    nume += 10;
    return nume;
}

void imprimir(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) { printf(" [%d][%d] => %d\n", i, j, *(*(matriz + i) + j)); }
        printf("\n");
    }
}

int **reajustar_matriz(int **matriz, int new_linhas, int old_linhas, int colunas) {
    if (new_linhas < old_linhas) {
        for (int i = new_linhas; i > old_linhas; i++) { free(*(matriz + i)); }
    }

    int **new_matriz = (int **) realloc(matriz, new_linhas * sizeof(int *));

    if (new_linhas > old_linhas) {
        for (int i = old_linhas; i < new_linhas; i++) { *(new_matriz + i) = (int *) calloc(colunas, sizeof(int)); }
    }

    return new_matriz;
}

void reajustar_colunas(int **matriz, int linhas, int new_colunas, int old_colunas) {
    for (int i = 0; i < linhas; i++) {
        *(matriz + i) = (int *) realloc(*(matriz + i), new_colunas * sizeof(int));

        for (int j = old_colunas; j < new_colunas; j++) { *(*(matriz + i) + j) = 0; }
    }
}

void liberar_matriz(int **matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) { free(*(matriz + i)); }
    free(matriz);
}

int main(void) {
    int quat_linhas = 0, quat_colunas = 0;
    int **matriz_aloc = NULL;

    printf("Insira dois numeros de quatidades de linhas e colunas:\n"
           " Linhas -> ");
    scanf("%d", &quat_linhas);
    printf(" Colunas -> ");
    scanf("%d", &quat_colunas);

    matriz_aloc = criar_matriz(quat_linhas, quat_colunas);

    if (matriz_aloc == NULL) {
        printf("ERRO: Matriz nao foi criado ou quatidade e invalida.\n\n");
        return 0;
    }

    printf("\nGerado os valores cada linha.\n");
    for (int i = 0; i < quat_linhas; i++) {
        int *linha = *(matriz_aloc + i);

        for (int j = 0; j < quat_colunas; j++) { *(linha + j) = numerador(); }
    }

    printf("Exibir os valores cada linha:\n");
    imprimir(matriz_aloc, quat_linhas, quat_colunas);

    // adicionado codigo

    int new_linhas = 0, new_colunas = 0;

    printf("Insira reajustar quatidades de linhas e colunas:\n %d linhas para -> ", quat_linhas);
    scanf("%d", &new_linhas);
    printf(" %d colunas para -> ", quat_colunas);
    scanf("%d", &new_colunas);

    if (new_linhas < 0 || new_colunas < 0) {
        printf("ERRO: Quatidade e negativo!");
        free(matriz_aloc);
        matriz_aloc = NULL;
        return 0;
    } else if (new_linhas != quat_linhas)
        matriz_aloc = reajustar_matriz(matriz_aloc, new_linhas, quat_linhas, quat_colunas);
    else
        printf("Sem alterado as linhas de matriz.\n");

    new_colunas != quat_colunas ? reajustar_colunas(matriz_aloc, quat_linhas, new_colunas, quat_colunas)
                                : printf("Sem alterado as colunas.\n");

    // Gerado novos valores cada linha.
    for (int i = 0; i < new_linhas; i++) {
        int *linha = *(matriz_aloc + i);

        for (int j = 0; j < new_colunas; j++) {
            if (*(linha + j) == 0) { *(linha + j) = numerador(); }
        }
    }

    quat_linhas = new_linhas;
    quat_colunas = new_colunas;

    printf("Exibir novos valores cada linha:\n");
    imprimir(matriz_aloc, quat_linhas, quat_colunas);

    liberar_matriz(matriz_aloc, quat_linhas);
    matriz_aloc = NULL;

    return 0;
}
