/*
Justificativa: Escolhi uma estrutura de fila dinâmica porque numero indefinido de pacientes.
O primeiro paciente registrado na fila será o primeiro atendido.

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50], cpf[12], sintoma_p[50];
    int index;
} REGISTRO;

typedef struct paciente {
    REGISTRO r;
    struct paciente *prox;
} PACIENTE;

typedef struct {
    PACIENTE *inicio, *fim;
} FILA;

void inicializar(FILA *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

PACIENTE *criar_paciente(REGISTRO r) {
    PACIENTE *new = (PACIENTE *) calloc(1, sizeof(PACIENTE));
    if (new != NULL) {
        new->r = r;
        new->prox = NULL;
    }
    return new;
}

void adicionar_paciente(FILA *f, REGISTRO r) {
    PACIENTE *new = criar_paciente(r);
    if (new == NULL)
        return;

    if (f->fim == NULL)
        f->inicio = new;
    else {
        f->fim->prox = new;
    }

    f->fim = new;
}

void chamar_prox(FILA *f) {
    if (f->inicio != NULL) {
        PACIENTE *aux = f->inicio;
        f->inicio = f->inicio->prox;
        if (f->inicio == NULL)
            f->fim = NULL;

        printf("Proxima %d dados do paciente:\n"
               "    Nome: %s\n"
               "    CPF: %s\n"
               "    Sintoma: %s\n",
               aux->r.index, aux->r.nome, aux->r.cpf, aux->r.sintoma_p);
        free(aux);
    } else
        printf("Fila  esta vazio\n");
}

void liberar(FILA *f) {
    PACIENTE *aux = f->inicio;
    while (aux) {
        PACIENTE *exc = aux;
        aux = aux->prox;
        free(exc);
    }
    inicializar(f);
}

void str_lido(char *msm, char *var, int max) {
    printf("    %s: ", msm);
    fgets(var, max, stdin);

    size_t tam = strlen(var);
    if (tam > 0 && var[strlen(var) - 1] == '\n')
        var[strlen(var) - 1] = '\0';
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

int main(void) {
    FILA pacientes;

    inicializar(&pacientes);

    for (int i = 0; i < 3; i++) {
        REGISTRO r;
        printf("Registrar %d dados do paciente:\n", i + 1);
        r.index = i + 1;
        str_lido("Nome", r.nome, 50);
        str_lido("CPF", r.cpf, 12);
        str_lido("Sintoma", r.sintoma_p, 50);

        printf("\nTest: %s\n", r.nome);
        printf("%s\n", r.cpf);
        printf("%s\n\n", r.sintoma_p);
        adicionar_paciente(&pacientes, r);
    }

    chamar_prox(&pacientes);
    chamar_prox(&pacientes);

    liberar(&pacientes);

    return 0;
}