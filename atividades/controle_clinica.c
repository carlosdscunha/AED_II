#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 10

typedef struct {
    char nome[50], m_consulta[50];
    int idade;
} REGISTRO;

typedef struct paciente {
    REGISTRO r;
    struct paciente *prox;
} PACIENTE;

typedef struct {
    PACIENTE *inicio, *fim;
    int qtde;
} FILA;

void inicializar(FILA *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->qtde = 0;
}

PACIENTE *novo_pacient(REGISTRO r) {
    PACIENTE *novo = (PACIENTE *) calloc(1, sizeof(PACIENTE));
    if (novo) {
        novo->r = r;
        novo->prox = NULL;
    }
    return novo;
}

void inserir(FILA *f, REGISTRO r) {
    if (f->qtde >= MAX) {
        printf("AVISO: a fila armazena esta cheio máximo 10 pacientes.\n");
        return;
    }

    PACIENTE *novo = novo_pacient(r);
    if (novo == NULL)
        return;

    if (f->fim == NULL)
        f->inicio = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
    f->qtde++;
}

PACIENTE *remover(FILA *f) {
    if (f->inicio == NULL)
        return NULL;

    PACIENTE *aux = f->inicio;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL)
        f->fim = NULL;

    f->qtde--;

    return aux;
}

void liberar(FILA *f) {
    PACIENTE *aux = f->inicio;
    while (aux) {
        PACIENTE *ecx = aux;
        aux = aux->prox;
        free(ecx);
    }
    inicializar(f);
}

void imprimir(FILA *f) {
    PACIENTE *aux = f->inicio;
    while (aux) {
        printf("    Nome: %s", aux->r.nome);
        aux = aux->prox;
    }
}

void clear_tela() { printf("\033[H\033[J"); }

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void str_lido(char *mens, char *var) {
    printf("    %s: ", mens);
    scanf("%49[^\n]", var);
    limpar_teclado();
}

void int_lido(char *mens, int *var) {
    printf("    %s: ", mens);
    scanf("%d", var);
    limpar_teclado();
}

int main(void) {
    FILA f;
    inicializar(&f);

    char selec = ' ';
    do {
        if (selec == ' ') {
            printf("\n--- CLINICA ---\n\n");
            printf("Selecione opção:\n"
                   " [1]- Novo paciente\n"
                   " [2]- Chamar para aconsulta\n"
                   " [3]- Consultar as informacoes\n"
                   " [4]- Encerrar o programa\n-> ");
            scanf("%c", &selec);
            limpar_teclado();
        }

        switch (selec) {
            case '1':
                clear_tela();
                REGISTRO novo_r = {};
                printf("Novo paciente, representar registrar:\n");
                str_lido("Nome", novo_r.nome);
                int_lido("Idade", &novo_r.idade);
                str_lido("Motivo da consulta", novo_r.m_consulta);

                printf("\n%s por %d numeros de registro na fila de espera\n", novo_r.nome, f.qtde);

                inserir(&f, novo_r);
                break;
            case '2':
                clear_tela();
                PACIENTE *cham = remover(&f);
                if (cham) {
                    printf("Proximo, paciente %s. Dirija consultorio", cham->r.nome);
                    free(cham);
                } else
                    printf("Ninguem na fila.\n");

                break;
            case '3':
                break;
            case '4':
                printf("\nEncerrado...");
                liberar(&f);
                return 0;
            default:
                printf("\nSelecao invalida\n");
                clear_tela();
                sleep(1);
                break;
        }
        selec = ' ';
    } while (1);
}