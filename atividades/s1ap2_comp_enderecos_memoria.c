/*
[S1AP2] Comparação de endereços de memória
        Implemente, na linguagem de programação C, um programa que contenha duas variáveis:
    uma do tipo inteiro e outra com ponto flutuante. Compare os endereços dessas variáveis e exiba, de uma só vez, o
    maior endereço de memória, junto ao valor que ele armazena.
*/

#include <stdio.h>

int main() {
    int inteiro = 5;
    float flutuante = 6.2;

    int *inteiro_ptr = &inteiro;
    float *flutuante_ptr = &flutuante;

    printf("Exiba os enderecos:\n "
           "    Inteiro  : %p\n "
           "    Flutuante: %p\n\n",
           inteiro_ptr, flutuante_ptr);

    printf("Comparacao de enderecos de memoria:\n");
    if (inteiro_ptr > flutuante_ptr)
        printf("  Maior endereco: %p\n"
               "      Valor: %d\n\n",
               inteiro_ptr, *inteiro_ptr);
    else
        printf("  Maior endereco: %p\n"
               "      Valor: %.2f\n",
               flutuante_ptr, *flutuante_ptr);

    return 0;
}