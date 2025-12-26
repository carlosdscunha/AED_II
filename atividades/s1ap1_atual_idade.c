/*
[S1AP1] Atualização da idade
        Escreva um procedimento que utilize ponteiros para calcular quanto tempo falta para uma pessoa se aposentar.
    Esse procedimento deve receber, por ponteiro, duas variáveis do tipo inteiro:

        · idade: representa a idade atual da pessoa;
        · sexo: representa o sexo da pessoa (por exemplo, 1 para masculino e 2 para feminino).

        O procedimento deve atualizar diretamente o valor apontado por idade, substituindo-o pelo tempo restante até a
    aposentadoria, conforme as regras abaixo:

        · Mulheres se aposentam aos 60 anos;
        · Homens se aposentam aos 65 anos.

        Caso a pessoa já tenha atingido a idade de aposentadoria, a variável deve ser atualizada para 0. Ao final, o
    método principal deve exibir o tempo necessário para a aposentadoria.
*/

#include <stdio.h>
#include <string.h>

void atualizar_aposentar(int *ptrs[]) {
    printf("\n\nInsira idade:\n"
           "-> ");
    scanf("%d", ptrs[0]);
    printf("Selecione sexo:\n"
           " 1 - Masculino\n"
           " 2 - Feminino\n-> ");
    scanf("%d", ptrs[1]);
}

void ver_idade_aposentar(int *ptrs[]) {
    printf("%s tem %d anos: ", *ptrs[1] == 1 ? "Homem" : "Mulher", *ptrs[0]);

    char mens[2][100] = {"atingiu a idade de aposentadoria valida.",
                         "idade de aposentadoria inválida nao aceita abaixo de "};
    strcat(mens[1], *ptrs[1] == 1 ? "65 anos." : "60 anos.");

    printf("%s\n\n", *ptrs[1] == 1 ? *ptrs[0] >= 65 ? mens[0] : mens[1] : *ptrs[0] >= 60 ? mens[0] : mens[1]);
}

int main() {
    int idade = 0, sexo = 0;
    int *ponteiros[] = {&idade, &sexo}; // &idade:[0] e &sexo:[1]

    for (int i = 0; i < 4; i++) {
        atualizar_aposentar(ponteiros);
        ver_idade_aposentar(ponteiros);
        idade = 0;
        sexo = 0;
    }

    return 0;
}