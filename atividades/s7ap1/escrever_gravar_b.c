#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idade;
    char nome[50], rga[13], curso[20];
} Estudante;

int main(void) {
    Estudante rgtros[5] = {{26, "Carlos", "202421901003", "Eng. Comp"},
                           {20, "João", "1542", "Eng. Contr"},
                           {18, "Ana", "8462", "Eng. Quim"},
                           {22, "Vitor", "845", "Eng. Comp"},
                           {24, "Matheus", "1147", "Eng. Comp"}};

    size_t qtde = sizeof(rgtros) / sizeof(Estudante);

    FILE *arqurvo = fopen("arquirvo.text", "wb");
    if (arqurvo == NULL) {
        printf("Erro: abrir arquirvo para escrita.\n");
        return 1;
    }

    fwrite(rgtros, sizeof(Estudante), qtde, arqurvo);

    fclose(arqurvo);

    printf("Foi gravacao.\n");

    return 0;
}