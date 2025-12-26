#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char titulo[100], nome_canal[60], link[44];
    float duracao;
} Info;

const Info registros[5] = {
        {"A prova inclui ponteiros em C", "Programação Descomplicada | Linguagem C",
         "https://www.youtube.com/shorts/2GqKiiGEU-o", 6.0},
        {"TODOS contra C em 97 SEGUNDOS", "Jarvis BR", "https://www.youtube.com/watch?v=BlDgaeIbVGs", 84.6},
        {"Vale a Pena APRENDER C para Microcontroladores?", "Eletrônica Fácil",
         "https://www.youtube.com/watch?v=UHzll_wytKg", 267.6},
        {"Python vs C/C++ vs Assembly side-by-side comparison", "xmdi", "https://www.youtube.com/watch?v=3PcIJKd1PKU",
         60.0},
        {"Domine a programação de microcontroladores PIC em C embarcado", "Dark I",
         "https://www.youtube.com/watch?v=l5-ce5m8vaE", 120.4}};

int main(void) {
    FILE *arquivo = fopen("registros.text", "w");
    if (arquivo == NULL) {
        printf("Erro: abrir o arquivo para escrito.\n");
        return 1;
    }

    size_t qtde = sizeof(registros) / sizeof(Info);
    for (size_t i = 0; i < qtde; i++) {
        const Info *inf = registros + i;
        if (fprintf(arquivo, " %s, %s, %s, %.2f\n", inf->titulo, inf->nome_canal, inf->link, inf->duracao) != EOF)
            printf("Salvo info %ld\n", i);
        else {
            printf("Erro: nao foi salvo, arquivo nao esta 'w' de modo para escrito.\n");
            fclose(arquivo);
            return 1;
        }
    }

    printf("Terminou de salvar todos os registros");
    fclose(arquivo);

    return 0;
}