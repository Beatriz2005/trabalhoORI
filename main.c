#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.c"
#include "hash.c"
#include "cleaning.c"
#include "set.c"

int main() {
    int n_linhas = 3;
    int linhas_lidas;

    // Solicita ao usuário o número máximo de linhas a ler
    printf("Digite o número máximo de linhas a ler: ");
    scanf("%d", &n_linhas);

    // Limpa o buffer de entrada após o scanf
    while (getchar() != '\n');

    Postagem* postagens = read_postagens("corpus.csv", &linhas_lidas, n_linhas);

    int TABLE_SIZE = 10;
    Hash* tabelaHash = criaHash(TABLE_SIZE);

    if (!postagens || !tabelaHash) return 1;

    print_postagens(postagens, linhas_lidas);

    printf("----------------\n");
    printf("Separando as palavras\n");

    for (int i = 0; i < linhas_lidas; i++) {
        char* palavraTeste = postagens[i].texto;
        processPost(tabelaHash, palavraTeste, postagens[i].docId);
    }

    // Libere a memória alocada
    for (int i = 0; i < linhas_lidas; i++) {
        free(postagens[i].texto);  // Libere a memória alocada para o texto
    }
    free(postagens);  // Libere a memória alocada para o array de postagens
    liberaHash(tabelaHash);  // Libere a memória da tabela hash

    return 0;
}