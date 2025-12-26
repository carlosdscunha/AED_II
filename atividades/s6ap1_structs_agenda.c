/*
[S6AP1] Introdução ao uso de structs
    Imagine que você tenha sido contratado(a) por uma empresa que produz celulares para desenvolver o sistema de
    controle da agenda telefônica. Como o dispositivo a ser lançado é de baixo custo, a agenda telefônica armazena
    apenas nome e sobrenome do contato, além do número de telefone e do endereço de e-mail. Mostre como a linguagem C
    poderia ser utilizada para implementar essa solução, considerando o uso adequado de estruturas de dados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[20], sobrenome[40], telefone[10], email[30];
} Contato; // 100 Bytes

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lido(char *mens, char *varia, int max) {
    printf("   %s: ", mens);
    fgets(varia, max, stdin);

    size_t tam = strlen(varia);

    if (tam > 0 && *(varia + (tam - 1)) == '\n')
        varia[tam - 1] = '\0';
    else
        limpar_teclado();
}

void criar_agenda(Contato *agenda, int max) {
    limpar_teclado();

    for (int i = 0; i < max; i++) {
        Contato *cont = (agenda + i);

        printf("Contato %d:\n", i + 1);
        lido("Nome", cont->nome, 20);
        lido("Sobrenome", cont->sobrenome, 40);
        lido("Numero de telefone", cont->telefone, 10);
        lido("E-mail", cont->email, 30);

        printf("\n");
    }
}

void exibir_agenda(Contato *agenda, int max) {
    for (int i = 0; i < max; i++) {
        Contato *cont = (agenda + i);
        printf("Contanto %d:\n"
               "   Nome: %s\n"
               "   Sobrenome: %s\n"
               "   Numero de telefone: %s\n"
               "   E-mail: %s\n",
               i + 1, cont->nome, cont->sobrenome, cont->telefone, cont->email);

        printf("\n");
    }
}

int main(void) {
    int max_contatos = 1;

    printf("Insira maximo de contatos para agendar: -> ");
    scanf("%d", &max_contatos);

    Contato *agenda = (Contato *) calloc(max_contatos, sizeof(Contato));

    printf("\nCriar cada contato:\n ");
    criar_agenda(agenda, max_contatos);

    printf("\nExibir cada contato:\n ");
    exibir_agenda(agenda, max_contatos);

    free(agenda);
    agenda = NULL;

    return 0;
}