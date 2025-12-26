/*
[S4AP3] Alocação dinâmica de vetor - 2
    Agora, continue o exercício anterior. Considere que após a impressão do vetor na função `main()`, o programa
    solicitará ao usuário que informe, via teclado, um número inteiro. Este valor informado pelo usuário definirá a nova
    quantidade de itens a serem armazenados por este vetor alocado dinamicamente, para mais ou para menos.

    Para tanto, você deverá criar uma nova função, específica para reajustar o tamanho do vetor. Após a execução da
    função, na `main()` você deverá analisar se a mudança no tamanho do vetor deu certo. Caso tenha funcionado, você
    deverá ler novos valores que preencherão este vetor. Após a leitura, o vetor completo deve ser impresso, no mesmo
    formato abordado no exercício anterior.
*/

#include <stdio.h>
#include <stdlib.h>

int *entrada(int itens) { return calloc(itens, sizeof(int)); }

int *reajustar_tam(int *vet, int itens) { return (int *) realloc(vet, itens * sizeof(int)); }

void imprimir(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) { printf(" [%d] => %d\n", i, *(vet + i)); }
}

int main(void) {
    int itens = 0;
    int *vet_aloc = NULL;

    printf("Insira capicidade de itens: -> ");
    scanf("%d", &itens);

    vet_aloc = entrada(itens);
    vet_aloc != NULL ? printf("\nVetor foi criado.\n") : printf("\nERRO: Vetor nao foi criado.\n");

    printf("Insire vetor com valores:\n");
    for (int i = 0; i < itens; i++) {
        printf(" [%d] -> ", i);
        scanf("%d", vet_aloc + i);
    }

    printf("Exibir vetor com valores:\n");
    imprimir(vet_aloc, itens);

    // ------- adicionado codigos -------

    int new_itens = 0;
    printf("\nInsira aumetar quantidade de itens: [%d] para: -> ", itens);
    scanf("%d", &new_itens);

    int *new_vet_aloc = reajustar_tam(vet_aloc, new_itens);
    if (new_vet_aloc != NULL) vet_aloc = new_vet_aloc;

    printf("Insire vetor com valores com novos itens:\n");
    for (int i = itens; i < new_itens; i++) { // index receber variavel itens foram lidos no vetor alocado
        printf(" [%d] -> ", i);
        scanf("%d", vet_aloc + i);
    }

    printf("Exibir vetor com valores e novos valores:\n");
    imprimir(vet_aloc, new_itens);

    free(vet_aloc);
    vet_aloc = NULL;

    return 0;
}
