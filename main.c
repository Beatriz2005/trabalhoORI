#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Leitura/leitura.h"
#include "Arvore/arvore.h"
#include "Pilha/pilha.h"
#include "TabelaHash/tabelaHash.h"
#include "Busca/busca.h"

int main() {
    int n_linhas;
    int linhas_lidas;
    char str_consulta[MAX_BUSCA] = {0};  // Inicializa a string com zeros

    // Solicita ao usuário o número máximo de linhas a ler
    printf("Digite o número máximo de linhas a ler: ");
    scanf("%d", &n_linhas);

    // Limpa o buffer de entrada após o scanf
    while (getchar() != '\n');

    Tweet* tweets = ler_tweets("./corpus.csv", &linhas_lidas, n_linhas);
    if (!tweets) {
        return 1;
    }

    // Cria a tabela hash
    Hash* tabela_hash = criaHash(100); // Ajuste conforme o tamanho necessário
    inserir_palavras_na_hash(tabela_hash, tweets, linhas_lidas);

    printf("Digite a lista de palavras para a busca (AND, OR e NOT pode ser utilizado para compor a busca): ");
    fgets(str_consulta, MAX_BUSCA, stdin);
    str_consulta[strcspn(str_consulta, "\n")] = 0; 

    Noh* arvore = interpretar_pesquisa(str_consulta);

    // Realiza a busca na árvore
    Set* resultado_busca = realizar_busca(arvore, tabela_hash);

    // Imprime os resultados
    imprimir_resultados(tweets, linhas_lidas, resultado_busca);

    // Libera a árvore após o uso
    liberar_arvore(arvore);

    // Libere a memória alocada para os tweets
    for (int i = 0; i < linhas_lidas; i++) {
        free(tweets[i].texto); // Libere a memória alocada para o texto
    }
    free(tweets); // Libere a memória alocada para o array de tweets

    liberaHash(tabela_hash);

    return 0;
}
