#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef linux
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif // linux

#define MAX_TITULO 20
#define MAX_TEXT 144

typedef struct {
    char titulo[MAX_TITULO], text[MAX_TEXT];
    size_t len;
} STRING;

typedef struct item {
    struct item *prox;
    STRING s;
} ITEM;

typedef struct {
    ITEM *inicio;
    int qtde;
} LISTA;

void inicializar(LISTA *l) {
    l->inicio = NULL;
    l->qtde = 0;
}

ITEM *crair_item(STRING s) {
    ITEM *new = (ITEM *) malloc(sizeof(ITEM));
    if (new == NULL)
        return NULL;

    new->s = s;
    new->prox = NULL;

    return new;
}

void inserir(LISTA *l, STRING s) {
    ITEM *new = crair_item(s), *pos = l->inicio, *ant = NULL;

    while (pos) {
        ant = pos;
        pos = pos->prox;
    }

    if (ant == NULL)
        l->inicio = new;
    else
        ant->prox = new;

    l->qtde++;
}

bool remover(LISTA *l, STRING *s) {
    if (l->inicio == NULL) {
        strcpy(s->text, "Lista vazia\n");
        return false;
    }

    ITEM *pos = l->inicio, *ant = NULL;

    while (pos && strcmp(pos->s.titulo, s->titulo)) {
        ant = pos;
        pos = pos->prox;
    }

    if (pos == NULL) {
        strcpy(s->text, "Titulo nao existe\n");
        return false;
    }

    if (ant == NULL)
        l->inicio = l->inicio->prox;
    else
        ant->prox = pos->prox;

    free(pos);
    l->qtde--;
    return true;
}

void liberar(LISTA *l) {
    ITEM *pos = l->inicio;

    while (pos) {
        ITEM *exc = pos;
        pos = exc->prox;
        free(exc);
    }
    l->inicio = NULL;
    l->qtde = 0;
}

void imprimir_str(const STRING s) {
    printf("Titulo: %s\n"
           "  Text: %s\n"
           "-----------------\n\n",
           s.titulo, s.text);
}

void imprimir_lista(LISTA *l) {
    ITEM *pos = l->inicio;

    while (pos) {
        imprimir_str(pos->s);
        pos = pos->prox;
    }
}

void limpar_tela() { system(CLEAR); }

void limpar_teclas() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void pausar() {
    printf("\n Aperta [ENTER] para continuar...");
    getchar();
}

void str_lido(char *mens, char *var, int max) {
    printf("%s: ", mens);
    fgets(var, max, stdin);

    size_t tam = strlen(var);
    if (tam > 0 && var[tam - 1] == '\n')
        var[tam - 1] = '\0';
    else
        limpar_teclas();
}

void new_publi(LISTA *l) {
    STRING new = {};
    str_lido("Titulo", new.titulo, MAX_TITULO);
    str_lido("Text", new.text, MAX_TEXT);
    new.len = strlen(new.text);

    inserir(l, new);
    printf("\nFoi puclicado.");
    pausar();
}

void excluir_publi(LISTA *l) {
    STRING exc;

    while (1) {
        limpar_tela();
        printf("------- Excluir Publicacao -------\n\n");
        if (l->inicio == NULL) {
            printf("Lista vazia\n");
            pausar();
            return;
        }

        imprimir_lista(l);
        str_lido("Escreve titulo para excluir uma publicacao", exc.titulo, MAX_TITULO);

        if (remover(l, &exc)) {
            printf("Foi excluido sucesso\n");
            pausar();
            break;
        } else {
            printf("%s", exc.text);
            pausar();
        }
    }
}

int main(void) {
    LISTA publicacoes;

    inicializar(&publicacoes);
    printf("------- -------\n\n");

    while (1) {
        limpar_tela();
        printf("------- Seu Perfil -------\n\n"
               "Suas Publicacoes: %d\n\n",
               publicacoes.qtde);
        printf("Selecione um opcao:\n"
               "   [1] - Nova Publicacao\n"
               "   [2] - Visualizar Publicacoes\n"
               "   [3] - Excluir Publicacao\n"
               "   [S] Fechar app\n"
               "   -> ");

        int selec = getchar();
        limpar_teclas();
        switch (selec) {
            case '1':
                limpar_tela();
                printf("------- Nova Publicacao -------\n\n");
                new_publi(&publicacoes);
                break;
            case '2':
                limpar_tela();
                printf("------- Visualizar Publicacoes -------\n\n");
                imprimir_lista(&publicacoes);

                pausar();
                break;
            case '3':
                excluir_publi(&publicacoes);
                break;
            case 'S':
            case 's':
                liberar(&publicacoes);

                printf("\n\n Fechado App");
                return 0;
            default:
                break;
        }
    }
}