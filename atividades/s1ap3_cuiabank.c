/*
[S1AP3] Cuiabank
        O CuiaBank é um banco digital criado por estudantes da UFMT, incluindo você, que ficou responsável por
    implementar uma função para controle de saques. O banco oferece aos clientes um saldo especial (limite de crédito)
    que pode ser usado quando o saldo da conta não for suficiente para a operação.

        Implemente uma função chamada sacar() que receba, por ponteiro, os endereços das variáveis saldo e
    saldo_especial, além do valor do saque solicitado. Esta função deve:

        · Verificar se o valor do saque é menor ou igual à soma de saldo e saldo_especial;

        · Caso o saque seja possível, atualizar os valores apontados por esses ponteiros, descontando primeiro do saldo
        da conta e, se necessário, do saldo especial;

        · Retornar um valor que indique se o saque foi realizado com sucesso ou não.

        Ao final das operações, o programa principal deve exibir o extrato bancário, mostrando o saldo restante e o
    saldo especial disponível.
*/

#include <stdio.h>

void sacar(float *ptrs[]) {
    printf("Digite o valor do saque, se sair use 0:\n"
           "-> R$");
    if (scanf("%f", ptrs[2]) == 0) {
        printf("\n\x1b[31mERRO:\x1b[0m Digito invalido\n\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (*ptrs[2] == 0) // Sair do bloco
        return;
    else if (*ptrs[2] <= *ptrs[0] + *ptrs[1]) { // (saque <= saldo + saldo_especial)
        *ptrs[0] = *ptrs[0] - *ptrs[2];         // saldo - saque

        if (*ptrs[0] < 0) {                 // Saldo é negativo para subração saldo especial
            *ptrs[1] = *ptrs[1] + *ptrs[0]; // saldo +(-saldo)
            *ptrs[0] = 0;                   // saldo é 0

            printf("\nSaque foi realizado com sucesso.\n\n");
        }
    } else {
        printf("\x1b[31mERRO:\x1b[0m O seu saldo e o seu limite de credito nao sao suficientes!\n\n");
        *ptrs[2] = -1;
    }
}

int main() {
    float saldo = 50, saldo_especial = 500, saque = -1;
    float *ptrs[] = {&saldo, &saldo_especial, &saque}; // [0]: saldo; [1]: saldo_especial; [2]: saque

    do {
        printf("\n\n\nDisponivel Saque:\n"
               "   Saldo: R$%.2f\n"
               "   Limite de Credito: R$%.2f\n\n",
               saldo, saldo_especial);
        sacar(ptrs);

        if (saque == 0) // Sair do bloco
            break;
        else if (saque > 0) {
            printf("------------------------------------------------------------\n\n"
                   "                  AUTOATENDIMENTO CUIABANK                  \n\n"
                   "                    COMPROVANTE DE SAQUE                    \n\n"
                   "------------------------------------------------------------\n\n"
                   "VALOR DO SAQUE: R$ %.2f\n\n"
                   "------------------------ DISPONIVEL ------------------------\n\n"
                   "SALDO: R$ %.2f\n"
                   "LIMITE DE CREDITO: R$ %.2f\n\n"
                   "------------------------------------------------------------\n\n",
                   saque, saldo, saldo_especial);
            return 0;
        }

    } while (1);
}
