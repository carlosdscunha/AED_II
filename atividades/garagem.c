#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_M 5

typedef struct {
    int apartamento;
    char placa[10];

} REGISTRO;

typedef struct {
    REGISTRO carros[TAM_M];
    int topo;
} PILHA;

void inicialzar_pilha(PILHA *p) { p->topo = 0; }

bool empilhar(PILHA *p, REGISTRO r) {
    if (p->topo < TAM_M) {
        p->carros[p->topo] = r;
        p->topo++;
        return true;
    }

    return false;
}

bool despilhar(PILHA *p, REGISTRO *r) {
    if (p->topo > 0) {
        *r = p->carros[p->topo - 1];
        p->topo--;
        return true;
    }
    return false;
}

void imprimir(PILHA *p) {
    for (int i = p->topo - 1; i >= 0; i--) {
        REGISTRO c = *(p->carros + i);
        printf("%d - Placa: %s Apartmt: %d\n", i, c.placa, c.apartamento);
    }
}

int main(void) {
    const REGISTRO carros[] = {{12, "ABC-12845"}, {14, "IDR-75146"}, {30, "PEF-34624"}, {1, "LRT-96042"},
                               {5, "PLR-32757"},  {8, "LEB-00624"},  {12, "LHR-36594"}};

    PILHA garegem;

    inicialzar_pilha(&garegem);

    for (size_t i = 0; i < sizeof(carros) / sizeof(REGISTRO); i++) {
        const REGISTRO carro = *(carros + i);
        empilhar(&garegem, carro) ? printf("%s estacionado e %d quantidade de veículos.\n", carro.placa, garegem.topo)
                                  : printf("\n%s passagem está bloquedo espaço não suficiente.\n", carro.placa);
    }

    REGISTRO c;
    despilhar(&garegem, &c) ? printf("\n%s saiu , retirado %d quantidade de veículo.\n\n", c.placa, garegem.topo)
                            : printf("Nenhuma quantidade de veículo.");

    imprimir(&garegem);

    char placa_morador[10] = "PEF-34624";
    int retirados = 0;

    for (int i = garegem.topo - 1; i >= 0; i--) {
        despilhar(&garegem, &c);
        if (strcmp(placa_morador, c.placa) == 0)
            break;

        else {
            printf("\n%s saiu, retirado %d quantidade de veículo.\n\n", c.placa, garegem.topo);
            retirados++;
        }
    }

    printf("\nNúmeros apartamentos dos veículos envolvidos:\n");
    imprimir(&garegem);

    return 0;
}