/*
[S2AP2] Troca de vetores usando ponteiros
        Crie um programa contendo dois vetores (A e B), de tamanho igual, cujos valores foram lidos do teclado. Em
    seguida, implemente uma função que recebe esses vetores e troque os valores do vetor A com os valores do vetor B.
    Use aritmética de ponteiros(https://ufmt.dev/aed2/alocacao/aritmetica) para efetuar essas operações.
*/

#include <stdio.h>

void cujar_valores(int *vetores) {
    for (int i = 0; i < 3; i++) {
        printf("Insira um valor %d: -> ", i);
        scanf("%d", vetores + i);
    }
}

void exibir_vetores(int *vets) {
    for (int i = 0; i < 3; i++) { printf("    [%d] = %d\n", i, *(vets + i)); }
}

void trocar_valores(int *A, int *B) {

    for (int i = 0; i < 3; i++) {
        int aux = *(A + i);

        *(A + i) = *(B + i);
        *(B + i) = aux;
    }
}

int main(void) {
    int A[3] = {}, B[3] = {};

    printf("\n\nVetores A:\n");
    cujar_valores(A);
    printf("\n\nVetores B:\n");
    cujar_valores(B);

    printf("\n\nExibir vetores:\n");
    printf(" Vetores A = \n");
    exibir_vetores(A);
    printf(" Vetores B = \n");
    exibir_vetores(B);

    printf("\n\nTrocar vetores:\n");
    trocar_valores(A, B);

    printf(" Vetores A = \n");
    exibir_vetores(A);
    printf(" Vetores B = \n");
    exibir_vetores(B);

    return 0;
}