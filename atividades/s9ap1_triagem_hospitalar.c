/*
[S9AP1] Triagem hospitalar
    Você foi contratado para desenvolver o módulo de atendimento de um Pronto Socorro. A regra de negócio estabelecida
    pela direção do hospital é estrita quanto à ordem de chegada: pacientes que chegam para triagem devem ser atendidos
    exatamente na sequência em que foram registrados, sem exceções de prioridade nesta etapa específica do software. O
    sistema deve ser capaz de registrar um número indefinido de pacientes, visto que em dias de epidemia a demanda é
    imprevisível e não se pode limitar o tamanho da lista em tempo de compilação.

    O registro de cada paciente deve conter o nome do paciente (string), seu CPF (string) e o sintoma principal
    (string).

    A partir do enunciado(https://novoava.ufmt.br/graduacao/pluginfile.php/982056/mod_resource/content/1/enunciado.pdf),
    identifique qual estrutura de dados é adequada para modelar este cenário, justificando a sua escolha em um
    comentário no início do código. Implemente a estrutura escolhida utilizando alocação dinâmica de
    memória(https://ufmt.dev/aed2/alocacao/alocacao-dinamica).

    Crie uma função adicionar_paciente e uma função chamar_proximo (que imprime os dados do paciente e libera a memória
    ocupada por ele). Na main, simule a chegada de 3 pacientes e o atendimento de 2 deles.
*/

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
    if (new == NULL) return;

    if (f->fim == NULL)
        f->inicio = new;
    else { f->fim->prox = new; }

    f->fim = new;
}

void chamar_prox(FILA *f) {
    if (f->inicio != NULL) {
        PACIENTE *aux = f->inicio;
        f->inicio = f->inicio->prox;
        if (f->inicio == NULL) f->fim = NULL;

        printf("Proxima %d dados do paciente:\n"
               "    Nome: %s\n"
               "    CPF: %s\n"
               "    Sintoma: %s\n",
               aux->r.index, aux->r.nome, aux->r.cpf, aux->r.sintoma_p);
        free(aux);
    } else
        printf("Fila esta vazio\n");
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
        while ((c = getchar()) != '\n' && c != EOF);
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

        adicionar_paciente(&pacientes, r);
    }

    chamar_prox(&pacientes);
    chamar_prox(&pacientes);

    liberar(&pacientes);

    return 0;
}