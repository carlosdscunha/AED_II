/*
[S9AP2] Editor de texto
    Uma empresa de software está criando um editor de texto simples. Uma das funcionalidades mais críticas solicitadas
    pelos usuários é o recurso de "Desfazer" (Ctrl+Z). O funcionamento é o seguinte: sempre que o usuário digita uma
    frase e pressiona ENTER, essa frase é guardada na memória. Se o usuário cometer um erro, ele pode acionar um comando
    especial que recupera e remove a última frase digitada, depois a penúltima, e assim sucessivamente, permitindo que
    ele volte ao estado anterior do documento.

    Selecione a estrutura dinâmica adequada para esta finalidade. Depois, implemente as seguintes funcionalidades:

        · mplemente as funções fundamentais de inserção e remoção para essa estrutura;

        · implemente uma função exibir_historico que mostre as frases na ordem em que seriam recuperadas (da mais
        recente para a mais antiga).

    Garanta que, ao desfazer uma ação, a memória alocada para aquela frase seja corretamente liberada (free).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef linux
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

typedef struct {
    char *text;
    size_t len;
} STRING;

typedef struct linha {
    struct linha *ant;
    STRING s;
} LINHA;

typedef struct {
    LINHA *topo;
    int qtde;
} PILHA;

void inicializar(PILHA *p) {
    p->topo = NULL;
    p->qtde = 0;
}

// STRING ->

STRING new_string(char *str) {
    size_t len = strlen(str);
    char *new_text = (char *) malloc(len + 1);
    strcpy(new_text, str);
    return (STRING){new_text, len};
}

void str_concat(STRING *s, char *str) {
    size_t len = s->len + strlen(str);

    char *new = (char *) realloc(s->text, len);
    if (new != NULL) {
        strcat(new, str);
        s->text = new;
        s->len = len;
    }
}

void str_set(STRING *s, int c) {
    char *new = (char *) realloc(s->text, s->len + 1);
    if (new == NULL) return;
    s->text = new;
    s->text[s->len] = c;
    s->len++;
}

// <- STRING

LINHA *criar_linha(STRING s) {
    LINHA *new = (LINHA *) malloc(sizeof(LINHA));
    if (new != NULL) {
        new->s = new_string(s.text);
        new->ant = NULL;
    }
    return new;
}

void inserir(PILHA *p, STRING s) {
    LINHA *new = criar_linha(s);
    if (new == NULL) return;

    new->ant = p->topo;
    p->topo = new;
    p->qtde++;
}

LINHA *remover(PILHA *p) {
    if (p->topo == NULL) return NULL;

    LINHA *exc = p->topo;
    p->topo = p->topo->ant;
    p->qtde--;
    return exc;
}

void exibir_historico(const PILHA *p) {
    LINHA *aux = p->topo;
    int i = p->qtde;
    while (aux) {
        printf("%d: %s\n", i--, aux->s.text);
        aux = aux->ant;
    }
}

void liberar_pilha(PILHA *p) {
    LINHA *aux = p->topo;
    while (aux) {
        LINHA *exc = aux;
        aux = aux->ant;
        free(exc);
    }

    p->topo = NULL;
}

void limpar_tela() { system(CLEAR); }

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void) {
    STRING frases = new_string("");

    PILHA historico;
    inicializar(&historico);

    while (1) {
        limpar_tela();
        printf("\n---- Editor de texto ----\n\n\n"
               " [ENTER] - Escreve e salvar frases\n [<] - Desfazer frases\n [=] - Exibir historico\n [@] - Sair:\n\n");
        printf("Texto: %s", frases.text == NULL ? "" : frases.text);
        int c = getchar();

        switch (c) {
            case '<': {
                LINHA *l = remover(&historico);
                if (l != NULL) {
                    free(frases.text);
                    frases = l->s;
                    free(l);
                }

                break;
            }
            case '@':
                liberar_pilha(&historico);
                free(frases.text);
                printf("\nFIM.");

                return 0;
            case '=':
                printf("\n\n----- Historico -----\n\n");
                exibir_historico(&historico);
                limpar_teclado();
                printf("\nAperta [ENTER] para continuar.");
                getchar();

                break;
            case '\n':
                break;
            default:
                inserir(&historico, frases); // quardar letras artigo
                str_set(&frases, c);         // primeira letra

                while ((c = getchar()) != '\n') { str_set(&frases, c); }

                str_set(&frases, '\n'); // ultima letra

                break;
        }
    }
}