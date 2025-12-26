/*
[S6AP2] Caso da biblioteca
    Implemente, em C, um programa que usa estruturas de dados para armazenar dados que representem a seguinte ocorrência
    do mundo real:

        Um estudante de graduação pode ir à biblioteca de sua universidade para realizar o empréstimo de um livro. O
        empréstimo pode estar em andamento ou já estar finalizado.

    Registre os dados que possibilitem representar uma ocorrência de um empréstimo, contendo dados do estudante
    envolvido, do livro e o status do empréstimo (em andamento ou finalizado). Depois, imprima os dados desse
    empréstimo, indicando qual livro foi emprestado por um estudante. Por exemplo:

        Joaquim (RGA 1234) emprestou o livro "AED2 é legal" (Autor: Renan).
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { ANDAMENTO, FINALIZADO } Empres;

typedef struct {
    char titulo[20], autor[20];
} Livro;

typedef struct {
    Empres empres;
    Livro livro;
    char nome[20], rga[13];
} Estudante;

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lido_char(char mens[], char *var, size_t tam) {
    printf("    %s: ", mens);
    fgets(var, tam, stdin);

    size_t t = strlen(var);
    if (t > 0 && *(var + (t - 1)) == '\n') {
        *(var + (t - 1)) = '\0';
    } else {
        limpar_teclado();
    }
}

void lido_int(char mens[], int *var) {
    printf("    %s: ", mens);

    if (scanf("%d", var) != 1) {
        *var = 0;
        limpar_teclado(); // Para limpar sujo
    }
}

Livro new_livro() {
    Livro livro;
    lido_char("Titulo do Livro", livro.titulo, 20);
    lido_char("Autor do Livro", livro.autor, 20);

    return livro;
}

void representem(Estudante *etd) {
    printf("\nRepresentem: \n");

    switch (etd->empres) {
        case ANDAMENTO:
            etd->empres = FINALIZADO;
            etd->livro = new_livro();

            printf("%s (RGA %s)"
                   " emprestou o livro '%s'"
                   " (Autor: %s)\n\n",
                   etd->nome, etd->rga, etd->livro.titulo, etd->livro.autor);
            break;
        case FINALIZADO:
            etd->empres = ANDAMENTO;

            printf("%s (RGA %s)"
                   " devolveu o livro '%s'\n\n",
                   etd->nome, etd->rga, etd->livro.titulo);
            break;
    }
}

Estudante cadastro() {
    Estudante new_cad = {ANDAMENTO};

    printf("Cadastro de Estudante:\n");
    lido_char("Nome", new_cad.nome, sizeof(new_cad.nome));
    lido_char("RGA", new_cad.rga, sizeof(new_cad.rga));

    representem(&new_cad);

    return new_cad;
}

int main(void) {

    printf("Size %ld\n", sizeof(Livro));
    printf("Size %ld\n", sizeof(Estudante));

    Estudante estud = cadastro();

    printf("5 dias depois...\n\n");
    representem(&estud);

    return 0;
}