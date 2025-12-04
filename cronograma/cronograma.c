#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { SEGUNDA, TERÇA, QUARTA, QUINTA, SEXTA } Dia;

typedef struct {
    int r, b, g;
    char nome[10];
} Color;

Color color(int r, int b, int g) { return (Color) {r, b, g}; }

char *dia(Dia d) {
    switch (d) {
        case SEGUNDA:
            return "Segunda";
            break;
        case TERÇA:
            return "Terça";
            break;
        case QUARTA:
            return "Quarta";
            break;
        case QUINTA:
            return "Quinta";
            break;
        case SEXTA:
            return "Sexta";
            break;
    }

    return "";
}

typedef struct {
    char inicio[6], fim[6];
} Horario;

typedef struct {
    int id;
    Dia dia;
    Color cor_rgb;
    Horario horario;
    char nome[50], sala[20];
} Disciplina;

int inp_num() {
    int tam;
    printf("Insira os numeros: ->");
    scanf("%d", &tam);
    printf("\n");
    return tam;
}

size_t num(const Disciplina *ptr) { return sizeof(ptr) / sizeof(Disciplina); }

int hm(const char *ptr) {
    int h, m;
    sscanf(ptr, "%d:%d", &h, &m);
    return h * 60 + m;
}

int vrfc_cft(Disciplina *ptr) {
    for (size_t i = 0; i < num(ptr); i++) {
        for (size_t j = i + 1; j < num(ptr); j++) {
            if ((ptr + i)->dia != (ptr + j)->dia)
                continue;

            if (hm((ptr + i)->horario.inicio) < hm((ptr + j)->horario.fim) && hm((ptr + j)->horario.inicio) < hm((ptr + i)->horario.fim)) {
                printf("\033[1;31m"
                       "\n!!! CONFLITO DE HORARIO ENCONTRADO !!!\n"
                       "Disciplina: '%s' (%s - %s)\n"
                       "Conflita com: '%s' (%s - %s)\n"
                       "No dia: %s\n"
                       "\033[0m\n",
                       (ptr + i)->nome, (ptr + i)->horario.inicio, (ptr + i)->horario.fim,

                       (ptr + j)->nome, (ptr + j)->horario.inicio, (ptr + j)->horario.fim,

                       dia((ptr + i)->dia));

                return 1;
            }
        }
    }

    return 0;
}

void liberar(Disciplina *ptr) {
    for (size_t i = 0; i < num(ptr); i++)
        free(ptr + i);

    free(ptr);
    ptr = NULL;
}

char *gerar_tabela_latex(Disciplina *dclns) {
    char *text = "\\documentclass[a4paper,12pt]{article}\n\n"

                 "%% --- PACOTES ---\n"
                 "\\usepackage[brazil]{babel}\n"
                 "\\usepackage[utf8]{inputenc}\n"
                 "\\usepackage[T1]{fontenc}\n"
                 "\\usepackage[table]{xcolor}\n"
                 "\\usepackage{array}\n"
                 "\\usepackage{geometry}\n"
                 "\\usepackage{tabularx}\n"
                 "\\geometry{margin=0cm}\n"
                 "\\renewcommand{\n"
                 "\\familydefault}{\\sfdefault}\n\n";

    char *text_color = "%% --- Definição de cores personalizadas ---\n"
                       "\\definecolor{textcolor}{HTML}{27408B}\n"
                       "\\definecolor{cinza}{RGB}{220, 220, 220}\n";

    for (size_t i = 0; i < num(dclns); i++) {
    }

    strcat(text, text_color);

    strcat(text,
           "\\begin{document}\n\n"

           "\\begin{center}\n"
           "    {\\LARGE\\color{textcolor} \\textbf{Meu Cronograma de Aulas}} \\\[0.8cm]\n\n"

           "    \\renewcommand{\\arraystretch}{1.7}\n\n"

           "    \\begin{tabularx}{\\textwidth}{|>{\\centering\\arraybackslash}m{2.5cm}|>{\\centering\\arraybackslash}m{3cm}|>{\\centering\\arraybackslash}X|>{\\centering\\arraybackslash}m{3cm}|}\n"
           "        \\hline\n"
           "        \\rowcolor{cinza}\n"
           "        \\textbf{Dia} & \\textbf{Horário} & \\textbf{Disciplina}\n"
           "        \\hline\n");

    char *text_tabela = "";

    strcat(text, text_tabela);

    strcat(text, "    \\end{tabularx}\n"
                 "\\end{center}\n"
                 "\\end{document}");

    return "";
}

int main(void) {
    int max_dcpn = inp_num();
    Disciplina *disciplinas = (Disciplina *) calloc(max_dcpn, sizeof(Disciplina));

    if (vrfc_cft(disciplinas) != 1) {
        printf("\nPor favor, ajuste os conflitos no código antes de gerar a tabela.\n");
        liberar(disciplinas);
        return 1;
    }

    printf("Nenhum conflito encontrado. Gerando código LaTeX...\n\n");
    char texto[] = gerar_tabela_latex(disciplinas);

    return 0;
}