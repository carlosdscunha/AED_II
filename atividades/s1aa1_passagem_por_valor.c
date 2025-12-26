/*
[S1AA1] Passagem por valor
        Implemente, em C, um programa que lê, na main(), um número inteiro informado pelo usuário e armazena este valor
    em uma variável. Após a leitura, o programa imprime (ainda na main()) o valor lido. Em seguida, aciona um
    procedimento (função sem retorno de parâmetro) que recebe uma variável do tipo inteiro e executa as seguintes
    operações:

        · atualiza o valor da variável recebida, duplicando este valor;
        · imprime o valor da variável após a duplicação;

        Terminada a execução do procedimento, a main() deve imprimir o valor da variável. Veja os exemplos de entrada e
    de saída:

    Exemplo	    Entrada	    Saída
    -------------------------------
       1	      5	          5
                              10
                              5
    -------------------------------
       2	      7	          7
                              14
                              7
    -------------------------------
*/

#include <stdio.h>

void atualizar(int num) {
    num = num * 2;
    printf("%d\n", num);
}

int main() {
    int numero;

    printf("Numero: ");
    scanf("%d", &numero);

    printf("%d\n", numero);
    atualizar(numero);
    printf("%d\n", numero);

    return 0;
}