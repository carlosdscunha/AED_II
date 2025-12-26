#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idade;
    char nome[50], rga[13], curso[20];
} Estudante;

int main(void) {
    Estudante rgtros[5];
    size_t qtde = sizeof(rgtros) / sizeof(Estudante);

    FILE *arqurvo = fopen("arquirvo.text", "rb");
    if (arqurvo == NULL) {
        printf("Erro: abrir arquirvo para escrita.\n");
        return 1;
    }

    fread(rgtros, sizeof(Estudante), qtde, arqurvo);
    fclose(arqurvo);

    printf("Exibir leitura do arquirvo de binario:\n");
    for (size_t i = 0; i < qtde; i++) {
        printf("%ld :\n"
               "    Nome: %s\n"
               "    Idade: %d\n"
               "    RGA: %s\n"
               "    Curso: %s\n\n",
               i + 1, (rgtros + i)->nome, (rgtros + i)->idade, (rgtros + i)->rga, (rgtros + i)->curso);
    }

    return 0;
}