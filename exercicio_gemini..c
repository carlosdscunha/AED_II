#include <stdio.h>

int analisar_vetor(int *vetor, int *soma_ptr) {
    int maior = 0;

    for (int i = 0; i < 5; i++) {
        *soma_ptr += *(vetor + i);

        if (maior > *(vetor + i))
            maior = *(vetor + i);
    }

    printf("\n\nMaior é %d", maior);
    return maior;
}

int main() {
    int vetor[5] = {};
    int soma;

    printf("\nInsira 5 números:\n");
    for (int i = 0; i < 5; i++) {
        printf(" %d -> ", i + 1);
        scanf("%d", &vetor[i]);
    }

    analisar_vetor(vetor, &soma);

    return 0;
}
