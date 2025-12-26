/*
[S2AP3] Preenchendo três vetores
        Crie um programa contendo três vetores (A, B e C), de tamanho igual. Para os vetores A e B, os valores devem ser
    lidos do teclado.

        Em seguida, implemente uma função que recebe os três vetores. Cada posição do vetor C deve ser preenchido com o
    maior valor do vetor A ou B naquela mesma posição.

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
    for (int i = 0; i < 3; i++) { printf("    [%i] = %d\n", i, *(vets + i)); }
}

void maior_valor_vetor(int *A, int *B, int *C) {
    for (int i = 0; i < 3; i++) { *(C + i) = (*(A + i) > *(B + i)) ? *(A + i) : *(B + i); }
}

int main(void) {
    int A[3] = {}, B[3] = {}, C[3] = {};

    printf("\n\nVetores A:\n");
    cujar_valores(A);
    printf("\n\nVetores B:\n");
    cujar_valores(B);

    printf("\n\nExibir vetores A e B:\n");
    printf(" vetores A = \n");
    exibir_vetores(A);
    printf(" vetores B = \n");
    exibir_vetores(B);

    printf("\n\nO maior valor do vetor A ou B:\n"
           " vetores C = \n");
    maior_valor_vetor(A, B, C);
    exibir_vetores(C);

    return 0;
}