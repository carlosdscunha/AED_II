/*
[S3AP3] Completando o código
    Analise o fragmento de código a seguir:

        int a = 17;
        int *ptr1 = &a;
        void **ptr2 = (void **) &ptr1;


    Qual operação pode ser feita para, a partir de ptr2, se chegar ao valor da variável a? Complete o código inserindo o
    processo necessário para a obtenção do valor de A e sua impressão na tela como um número inteiro.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a = 17;
    int *ptr1 = &a;

    void **ptr2 = (void **) &ptr1;

    printf("\nValor de A: %d", **((int **) ptr2));

    return 0;
}