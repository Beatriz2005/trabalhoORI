#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include "reading.c"

int main() {
    int n_linhas;
    int linhas_lidas;

    // Solicita ao usuário o número máximo de linhas a ler
    printf("Digite o número máximo de linhas a ler: ");
    scanf("%d", &n_linhas);

    // Limpa o buffer de entrada após o scanf
    while (getchar() != '\n');

    Postagem* postagens = read_postagens("corpus.csv", &linhas_lidas, n_linhas);
    if (!postagens) return 1;

    print_postagens(postagens, linhas_lidas);

    // Libere a memória alocada
    for (int i = 0; i < linhas_lidas; i++) {
        free(postagens[i].texto); // Libere a memória alocada para o texto
    }
    free(postagens); // Libere a memória alocada para o array de postagens

    return 0;
}
