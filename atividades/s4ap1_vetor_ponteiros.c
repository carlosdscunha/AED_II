/*
[S4AP1] Vetor de ponteiros
        Implemente, em C, um programa que declara três variáveis int ou float, sem inicializá-las. Em seguida, o
    programa declara um vetor, com ponteiros para cada uma dessas variáveis criadas anteriormente. Após a criação do
    vetor, são lidos do teclado os valores dessas variáveis. Concluída a leitura, imprima os valores das variáveis,
    percorrendo o vetor com aritmética de ponteiros.
*/

#include <stdio.h>

int main(void) {
    int a, b, c;
    int *ptr_vet[3] = {&a, &b, &c};

    printf("Insira os valores:\n");
    for (int i = 0; i < 3; i++) {
        printf(" ptr_vet[%d] -> ", i);
        scanf("%d", *(ptr_vet + i));
    }

    printf("\n\nExibir os valores:\n");
    for (int i = 0; i < 3; i++) { printf(" ptr_vet[%d] = %d\n", i, **(ptr_vet + i)); }

    return 0;
}
