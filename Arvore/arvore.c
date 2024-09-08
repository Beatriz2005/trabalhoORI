#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "../Leitura/leitura.h"

// Função auxiliar para criar um novo nó de operador
Noh* criar_noh_operador(TipoOperador operador, Noh* esquerda, Noh* direita) {
    Noh* novo_noh = (Noh*)malloc(sizeof(Noh));
    if (!novo_noh) {
        perror("Erro ao alocar memória para nó de operador");
        return NULL;
    }

    novo_noh->tipo = NOH_OPERADOR;
    novo_noh->operador = operador;
    novo_noh->esquerda = esquerda;
    novo_noh->direita = direita;

    return novo_noh;
}

// Função auxiliar para criar um novo nó de palavra
Noh* criar_noh_palavra(const char* palavra) {
    Noh* novo_noh = (Noh*)malloc(sizeof(Noh));
    if (!novo_noh) {
        perror("Erro ao alocar memória para nó de palavra");
        return NULL;
    }

    novo_noh->tipo = NOH_PALAVRA;
    novo_noh->palavra = copiar_string(palavra); // Usa a função copiar_string do seu código atual

    novo_noh->esquerda = NULL;
    novo_noh->direita = NULL;

    return novo_noh;
}

// Função para liberar a memória da árvore
void liberar_arvore(Noh* raiz) {
    if (!raiz) return;

    // Libera os filhos
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);

    // Libera a memória do conteúdo
    if (raiz->tipo == NOH_PALAVRA) {
        free(raiz->palavra);
    }

    // Libera o nó
    free(raiz);
}

// Função para imprimir a árvore em ordem (para depuração)
void imprimir_arvore(Noh* raiz) {
    imprimir_arvore_indentada(raiz, 0);
}

// Função auxiliar para imprimir a árvore com indentação para mostrar a hierarquia
void imprimir_arvore_indentada(Noh* raiz, int nivel) {
    if (!raiz) return;

    // Imprime a árvore da direita primeiro (para dar a sensação de "desenho" de árvore)
    imprimir_arvore_indentada(raiz->direita, nivel + 1);

    // Indentação para o nível atual
    for (int i = 0; i < nivel; i++) {
        printf("\t");  // Usa tab para criar o nível de indentação
    }

    // Imprime o conteúdo do nó
    if (raiz->tipo == NOH_OPERADOR) {
        switch (raiz->operador) {
            case OP_AND: printf("[AND]\n"); break;
            case OP_OR: printf("[OR]\n"); break;
            case OP_NOT: printf("[NOT]\n"); break;
        }
    } else if (raiz->tipo == NOH_PALAVRA) {
        printf("%s\n", raiz->palavra);
    }

    // Imprime a árvore da esquerda
    imprimir_arvore_indentada(raiz->esquerda, nivel + 1);
}
