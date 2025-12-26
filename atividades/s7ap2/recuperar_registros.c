#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char titulo[100], nome_canal[60], link[44];
    float duracao;
} Info;

Info *realocar(Info *rgts, int new_qtde) {
    Info *new = (Info *) realloc(rgts, new_qtde * sizeof(Info));

    if (new != NULL) {
        printf("\rRealocado aumetou %d elementos.", new_qtde);
        return new;
    }

    return NULL;
}

void exibir_inf(const Info *inf, int index) {
    printf("\n-----------------\n"
           "Info %d\n"
           "    Titulo: %s\n"
           "    Duracao: %.0f segundo\n"
           "    Nome canal: %s\n"
           "    Link: %s\n",
           index + 1, inf->titulo, inf->duracao, inf->nome_canal, inf->link);
}

void exibir_rgts(const Info *rgts, int qtde) {
    printf("EXIBIR TODOS OS REGISTROS:\n");
    for (int i = 0; i < qtde; i++) {
        exibir_inf(rgts + i, i);
        sleep(2);
    }
}

void limpar_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear() { printf("\033[H\033[J"); }

void menu_opcao(const Info *rgts, int qtde) {
    char opcao = ' ';

    do {
        if (opcao == ' ') {
            printf("\n\n---------- Menu Opcao ----------\n\n"
                   "Selecione um opcao:\n"
                   "    [1]- Listas os videos com longo\n"
                   "    [2]- Listas os videos com curto\n"
                   "    [3]- Exibir todos os registros de video\n"
                   "    [s]- Sair\n"
                   "    -> ");
            scanf("%c", &opcao);
            limpar_teclado();
        }

        switch (opcao) {
            case '1':
                clear();
                printf("UM VIDEO COM LOGO:\n");
                for (int i = 0; i < qtde; i++) {
                    if ((rgts + i)->duracao > 120) exibir_inf((rgts + i), i);
                }
                break;
            case '2':
                clear();
                printf("LISTAS DE VIDEOS CURTOS\n");
                for (int i = 0; i < qtde; i++) {
                    if ((rgts + i)->duracao <= 120) exibir_inf((rgts + i), i);
                }
                break;
            case '3':
                clear();
                exibir_rgts(rgts, qtde);
                break;
            case 's':
            case 'S':
                opcao = '0';
                printf("Saindo\n");
                return;
            default:
                clear();
                printf("Invalido selecao\n");
                break;
        }

        opcao = ' ';
    } while (1);
}

int main(void) {
    Info *rgts = (Info *) calloc(1, sizeof(Info)); // Registros

    FILE *arquivo = fopen("registros.text", "r");
    if (arquivo == NULL) {
        printf("Erro: abrir o arquivo nao existe.\n");
        return 1;
    }

    int qtde = 0;
    while (1) {
        Info *inf = rgts + qtde;
        if (fscanf(arquivo, " %100[^,], %60[^,], %44[^,], %f\n", inf->titulo, inf->nome_canal, inf->link,
                   &inf->duracao) != EOF) {
            Info *tmp = realocar(rgts, ++qtde + 1);

            if (tmp != NULL)
                rgts = tmp;
            else {
                printf("Erro: Relocar sem memoria.\n");
                break;
            }
        } else {
            fclose(arquivo);
            printf("\n\nTERMINOU recuperacao todos os registros.\n\n");

            Info *tmp = realocar(rgts, qtde);
            if (tmp != NULL) rgts = tmp;

            printf("\rRealocado diminiu %d elementos.", qtde);
            break;
        }
    }

    menu_opcao(rgts, qtde);

    printf("\nFIM");

    free(rgts);
    rgts = NULL;

    return 0;
}