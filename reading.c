#include "reading.h"

char* copiar_string(const char* origem) {
    // Aloca memória para a nova string (incluindo o terminador nulo)
    char* copia = malloc(strlen(origem) + 1);
    if (!copia) {
        perror("Erro ao alocar memória");
        return NULL;
    }

    // Copia o conteúdo da string origem para a nova memória
    strcpy(copia, origem);
    return copia;
}

Postagem* read_postagens(const char* arquivo, int* linhas_lidas, int n_linhas) {
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Postagem* postagens = NULL;
    char linha[MAX_LINE_LENGTH];
    int n_postagens = 0;

    while (fgets(linha, sizeof(linha), arq) && n_postagens < n_linhas) {
        // Remove o caractere de nova linha no final da linha
        int len = strlen(linha);
        while (len > 0 && (linha[len - 1] == '\n')) {
            linha[len - 1] = '\0';
            len--;
        }

        // Realoca memória para o array de postagens
        Postagem* temp = (Postagem*)realloc(postagens, sizeof(Postagem) * (n_postagens + 1));
        if (!temp) {
            perror("Erro ao alocar memória");
            free(postagens); // Libera memória já alocada
            fclose(arq);
            return NULL;
        }
        postagens = temp;

        // Parse a linha
        char* token = strtok(linha, ",");
        postagens[n_postagens].docId = atoi(token); // Converte o primeiro token para um número inteiro

        token = strtok(NULL, ",");
        postagens[n_postagens].opniao = atoi(token); // Converte o segundo token para um número inteiro

        token = strtok(NULL, ""); // Pega o restante da linha como texto
        postagens[n_postagens].texto = copiar_string(token); // Copia o token como o texto

        if (!postagens[n_postagens].texto) {
            // Erro ao copiar a string
            free(postagens);
            fclose(arq);
            return NULL;
        }

        n_postagens++;
    }

    fclose(arq);
    *linhas_lidas = n_postagens;
    return postagens;
}

void print_postagens(Postagem* postagens, int n_postagem) {
    for (int i = 0; i < n_postagem; i++) {
        printf("Postagem %d:\n", i + 1);
        printf("ID: %d\n", postagens[i].docId);
        printf("Opinião: %d\n", postagens[i].opniao);
        printf("Texto: %s\n", postagens[i].texto);
        printf("----------------------\n");
    }
}
