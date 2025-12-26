/*
[S4AP2] Alocação dinâmica de vetor - 1
    Implemente, em C, uma função que recebe um número inteiro como entrada. Este valor representará a quantidade de
    itens que serão armazenados em um vetor. Esta função deve alocar na memória, de forma dinâmica, espaço suficiente
    para armazenar essa quantidade de itens. Mesmo que o vetor tenha sido criado por uma função que não seja a main(),
    ele deve ser acessível e manipulável por qualquer outra função do programa. Também é necessário que as demais
    funções tenham alguma forma (via programação) de saber se o vetor foi criado com sucesso ou não.

    Na função main(), caso o vetor tenha sido alocado corretamente na memória, você deve preencher o vetor com valores
    lidos pelo teclado. Após o preenchimento do vetor, imprima o seu conteúdo considerando o seguinte formato:

        [0] => 20
        [1] => 10

    É importante lembrar que este vetor deve ser alocado de forma dinâmica pela função criada neste exercício, não
    podendo ser alocado automaticamente.
*/

#include <stdio.h>
#include <stdlib.h>

int *entrada(int itens) { return calloc(itens, sizeof(int)); }

int main(void) {
    int itens = 0;
    int *vet_aloc = NULL;

    printf("Insira capicidade de itens: -> ");
    scanf("%d", &itens);

    vet_aloc = entrada(itens);
    vet_aloc != NULL ? printf("\nVetor foi criado, endereco: %p\n", vet_aloc)
                     : printf("\nERRO: Vetor nao foi criado: NULL\n");

    printf("Insire vetor com valores:\n");
    for (int i = 0; i < itens; i++) {
        printf(" [%d] -> ", i);
        scanf("%d", vet_aloc + i);
    }

    printf("Exibir vetor com valores:\n");
    for (int i = 0; i < itens; i++) { printf(" [%d] => %d\n", i, *(vet_aloc + i)); }

    free(vet_aloc);
    vet_aloc = NULL;

    return 0;
}
