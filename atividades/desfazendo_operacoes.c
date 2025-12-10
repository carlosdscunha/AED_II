#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_O 5
#define TAM_M 10

typedef enum { OPERACOES, MUSICAS } TipoVetor;

typedef struct {
    char nome[50];
} Musica;

typedef union {
    Musica musicas[TAM_M];
    Musica operacoes[TAM_O];
} Itens;

typedef struct {
    Itens itens;
    TipoVetor tipo;
    int topo;
} PILHA;

const Musica m_spotify[TAM_M] = {
        {"Teus Sonho"}, {"Ouvir o Teu Falar"}, {"Jesus Em Tua Presença"}, {"Ainda Que em Figueira"}, {"Test 4"}, {"O Amor Tem Um Nome"},
        {"Yeshua"},     {"Pequeninos"},        {"Em Teus Braços"},        {"Lugar Secreto"},
};

void inicializar(PILHA *p, TipoVetor tipo) {
    p->topo = 0;
    p->tipo = tipo;
}

bool inserir(PILHA *p, Musica m) {
    int tam = p->tipo == OPERACOES ? TAM_O : TAM_M;
    if (p->topo < tam) {
        if (p->tipo == OPERACOES)
            p->itens.operacoes[p->topo] = m;
        else
            p->itens.musicas[p->topo] = m;

        p->topo++;
        return true;
    }

    return false;
}

bool remover(PILHA *p, Musica *i) {
    if (p->topo > 0) {
        if (p->tipo == OPERACOES)
            *i = p->itens.operacoes[p->topo - 1];
        else if (p->tipo == MUSICAS)
            *i = p->itens.musicas[p->topo - 1];

        p->topo--;
        return true;
    }

    return false;
}

void desfeitas(PILHA *p) {
    printf("Desfeita: %s\n", p->itens.operacoes[0].nome);

    for (int i = 1; i < p->topo; i++) {
        printf("[%d]: %s\n", i - 1, p->itens.operacoes[i].nome);
        p->itens.operacoes[i - 1] = p->itens.operacoes[i];
    }
    p->topo--;
}

void imprimir(const PILHA *p) {
    if (p->tipo == MUSICAS) {
        printf("Playlist:\n");
        for (int i = p->topo - 1; i >= 0; i--) {
            printf("    %d - %s\n", i, p->itens.musicas[i].nome);
        }
    }
}

void clear() { printf("\033[H\033[J"); }

int main(void) {
    PILHA p_operacoes, p_playlist;

    inicializar(&p_operacoes, OPERACOES);
    inicializar(&p_playlist, MUSICAS);

    for (size_t i = 0; i < TAM_M; i++) {
        if (inserir(&p_playlist, m_spotify[i]) == false)
            printf("ERRO: Inserir esta cheia de quantidade.\n");
    }

    char s = ' ';
    do {
        if (s == ' ') {
            imprimir(&p_playlist);
            printf("\n\nSelecine um opcao: [1]-Desfazer [2]-Refazer [s]-Sair\n-> ");
            scanf("%c", &s);

            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        switch (s) {
            case '1':
                clear();
                Musica m1;
                if (remover(&p_playlist, &m1)) {
                    printf("Removida a musica: %d - %s\n\n", p_playlist.topo, m1.nome);
                    if (p_operacoes.topo == TAM_O)
                        desfeitas(&p_operacoes);
                    inserir(&p_operacoes, m1);
                } else
                    printf("ERRO: Lista do Playlist vazio.\n\n");

                break;
            case '2':
                clear();
                Musica m2;
                if (remover(&p_operacoes, &m2)) {
                    printf("Musica voltou para playlist: %d - %s\n\n", p_operacoes.topo, m2.nome);
                    inserir(&p_playlist, m2);
                } else
                    printf("ERRO: Lista do Operacoes vazio.\n\n");
                break;
            case 'S':
            case 's':
                printf("\n\nSaindo...");
                return 0;
            default:
                printf("\nINVALIDO selecao!\n");
                sleep(2);
                clear();
                break;
        }

        s = ' ';
    } while (1);
}