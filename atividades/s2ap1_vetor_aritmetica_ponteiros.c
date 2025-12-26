/*
[S2AP1] Preenchendo um vetor com aritmética de ponteiros
        Implemente um programa que leia 5 valores do teclado, armazenando-os em um vetor. Para alocar os valores nas
    posições do vetor, não use índices, use aritmética de ponteiros(https://ufmt.dev/aed2/alocacao/aritmetica).
*/

#include <stdio.h>

void armazenar(int *vetores) {
    for (int i = 0; i < 5; i++) {
        printf("Endereço valor %d: %p\n\n"
               "Insira valor do teclado:\n"
               "   -> ",
               i, vetores + i);
        scanf("%d", vetores + i);
    }
}

int main(void) {
    int valores_teclado[5] = {};

    armazenar(valores_teclado);

    for (int j = 0; j < 5; j++) printf("Valor %d: %d\n", j, *(valores_teclado + j));

    return 0;
}