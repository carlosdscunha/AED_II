/*
[S8AP3] Controle de clínica
    Você foi designado para desenvolver um sistema de atendimento para uma clínica médica. A clínica deseja organizar a
    fila de pacientes de forma eficiente, usando uma estrutura de dados adequada. Considere as seguintes informações:

        - Cada paciente é representado por um número de registro único e possui informações como nome, idade e motivo da
        consulta.
        - O sistema deve permitir a inserção de novos pacientes na fila de espera.
        - Quando um médico está disponível, o próximo paciente na fila é chamado para a consulta.
        - Durante a consulta, o médico registra o atendimento e libera o paciente, removendo-o da fila.
        - O sistema também deve permitir a consulta do próximo paciente na fila sem removê-lo, caso o médico queira
        antecipar a chamada.
        - O usuário deve ter a opção de encerrar o programa a qualquer momento.

    Sua tarefa é implementar esse sistema de atendimento utilizando uma fila dinâmica em C. Considere a necessidade de
    criar funções para realizar as seguintes operações:

        1. Inserir um novo paciente na fila.
        2. Chamar o próximo paciente para a consulta.
        3. Consultar as informações do próximo paciente sem removê-lo.
        4. Encerrar o programa.

    Lembre-se de gerenciar corretamente a alocação e liberação de memória. Além disso, crie um menu simples para que o
    usuário possa interagir com o sistema de atendimento. Considere a implementação estática, em que a fila armazena no
    máximo 10 pacientes.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef linux
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

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
    PACIENTE *novo = novo_pacient(r);
    if (novo == NULL) return;

    if (f->fim == NULL)
        f->inicio = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
    f->qtde++;
}

PACIENTE *remover(FILA *f) {
    if (f->inicio == NULL) return NULL;

    PACIENTE *aux = f->inicio;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL) f->fim = NULL;

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

void clear_tela() { system(CLEAR); }

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\n\nAperta Enter para continuar....");
    getchar();
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
        clear_tela();
        printf("\n--- CLINICA ---\n\n"
               "Fila: %d/%d\n",
               f.qtde, MAX);
        printf("Selecione opcao:\n"
               " [1]- Novo paciente\n"
               " [2]- Chamar para aconsulta\n"
               " [3]- Consulta do proximo paciente\n"
               " [4]- Encerrar o programa\n-> ");
        scanf("%c", &selec);
        limpar_teclado();

        switch (selec) {
            case '1':
                clear_tela();
                if (f.qtde >= MAX) {
                    printf("AVISO: a fila armazena esta cheio maximo 10 pacientes.\n");
                    pausar();
                    break;
                }
                REGISTRO novo_r = {};
                printf("Novo paciente, representar registrar:\n");
                str_lido("Nome", novo_r.nome);
                int_lido("Idade", &novo_r.idade);
                str_lido("Motivo da consulta", novo_r.m_consulta);

                printf("\n%s por %d numeros de registro na fila de espera\n", novo_r.nome, f.qtde + 1);

                inserir(&f, novo_r);
                pausar();
                break;
            case '2':
                clear_tela();
                PACIENTE *cham = remover(&f);
                if (cham) {
                    printf("Atencao!\n"
                           "    Paciente: %s\n"
                           "    Motivo: %s\n"
                           "    Dirija consultorio",
                           cham->r.nome, cham->r.m_consulta);
                    free(cham);
                } else
                    printf("Ninguem na fila.\n");

                pausar();

                break;
            case '3':
                clear_tela();
                if (f.inicio) {
                    PACIENTE *ini = f.inicio;
                    printf("Consulta do proximo paciente:\n"
                           "    Nome: %s\n"
                           "    Idade: %d\n"
                           "    Motivo: %s",
                           ini->r.nome, ini->r.idade, ini->r.m_consulta);
                } else
                    printf("Ninguem na fila.\n");

                pausar();
                break;
            case '4':
                printf("\nEncerrado...");
                liberar(&f);
                return 0;
            default:
                printf("\nSelecao invalida\n");
                pausar();
                break;
        }
    } while (1);
}