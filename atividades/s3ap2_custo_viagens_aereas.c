/*
[S3AP2] Custo de viagens aéreas
    Odete, uma importante empresária brasileira, viaja bastante para diferentes capitais com um jatinho particular
    fretado por uma empresa de táxi aéreo, a Agostinho Transportes Aéreos (ATA). Dentre as capitais que Odete costuma
    visitar, cinco são bastante frequentes: Cuiabá, Goiânia, São Paulo, Curitiba e Rio de Janeiro (nesta ordem, da mais
    frequente para a menos frequente). Joilson, estagiário de Tecnologia da Informação da empresa de Odete preparou um
    programa simples para calcular o custo de cada viagem. Basicamente, ele criou um vetor que armazena o valor cobrado
    pela empresa de táxi aéreo para cada um desses destinos. A cada seis meses, entretanto, o custo é reajustado em um
    determinado percentual. Joilson implementou uma função/procedimento para reajustar todos os valores. Acontece que
    ele foi demitido porque chegou atrasado e, com a revolta, apagou esse recurso do programa. Você, que não sabia de
    toda essa história, entrou inocente na empresa para substituir Joilson e recebeu como primeira missão refazer este
    trabalho.

    Considerando o
    enunciado(https://novoava.ufmt.br/graduacao/pluginfile.php/982056/mod_resource/content/1/enunciado.pdf) apresentado,
    bem como a necessidade de implementação de um recurso, apresente um código em C capaz de atender, com as melhores
    práticas de programação, as demandas do caso apresentado. O programa deve exibir, ao final, os valores reajustados.
    Para percorrer o vetor, use aritmética de ponteiros(https://ufmt.dev/aed2/alocacao/aritmetica).
*/

#include <stdio.h>
#include <stdlib.h>

void exibir(float vet[], int tam) {
    for (int i = 0; i < tam; i++) { printf("    vet[%d] = %.2f\n", i, *(vet + i)); }
}

void reajuste(float *vet, int tam) {
    float aumenta = 0;
    printf("\nDigite para aumenta em por certo: -> ");
    scanf("%f", &aumenta);

    aumenta = (1 + aumenta / 100);

    for (int i = 0; i < tam; i++) { *(vet + i) = *(vet + i) * aumenta; }
}

int main(void) {
    float vet_valores[5] = {100, 400, 700, 200, 100};

    printf("\nExibir Vetores inicial:\n");
    exibir(vet_valores, 5);

    reajuste(vet_valores, 5);

    printf("\nExibir Vetores reajustado:\n");
    exibir(vet_valores, 5);

    return 0;
}