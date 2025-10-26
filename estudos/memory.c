#include <stdio.h>


void atualizar(int *num_ptr) { *num_ptr = *num_ptr * 2; }

void voltar_valor(int *num_ptr) { *num_ptr = *num_ptr / 2; }


int main() {
    int numero;
    int *numero_ptr = &numero;

    scanf("%d", numero_ptr);
    atualizar(numero_ptr);
    printf("%d\n", numero);
    voltar_valor(numero_ptr);
    printf("%d", numero);


    return 0;
}
