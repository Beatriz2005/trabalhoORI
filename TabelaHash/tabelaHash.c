#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaHash.h"

// Cria e inicializa uma tabela hash com o tamanho fornecido
Hash* criaHash(int TABLE_SIZE) {
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if (ha != NULL) {
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->itens = (HashItem**) malloc(TABLE_SIZE * sizeof(HashItem*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        for (int i = 0; i < TABLE_SIZE; i++) {
            ha->itens[i] = NULL;
        }
    }
    return ha;
}

// Libera a memória alocada para a tabela hash
void liberaHash(Hash* ha) {
    if (ha != NULL) {
        for (int i = 0; i < ha->TABLE_SIZE; i++) {
            HashItem* atual = ha->itens[i];
            while (atual != NULL) {
                HashItem* temp = atual;
                TweetList* lista = atual->lista_tweets;
                while (lista != NULL) {
                    TweetList* temp_lista = lista;
                    lista = lista->prox;
                    free(temp_lista);
                }
                atual = atual->prox;
                free(temp->palavra);
                free(temp);
            }
        }
        free(ha->itens);
        free(ha);
    }
}

// Função de hashing que converte uma string em um valor inteiro
int valorString(char* str) {
    int valor = 7;
    int tam = strlen(str);
    for (int i = 0; i < tam; i++) {
        valor = 31 * valor + (int)str[i];
    }
    return (valor & 0x7FFFFFFF);
}

// Insere uma palavra e seu RRN na tabela hash, tratando colisões
int insereHash(Hash* ha, char* palavra, int rrn) {
    int pos = valorString(palavra) % ha->TABLE_SIZE;

    // Procura se a palavra já existe na lista de colisão
    HashItem* atual = ha->itens[pos];
    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        // A palavra já existe, insere o RRN na lista de tweets
        TweetList* novoTweet = (TweetList*) malloc(sizeof(TweetList));
        novoTweet->rrn = rrn;
        novoTweet->prox = atual->lista_tweets;
        atual->lista_tweets = novoTweet;
    } else {
        // Palavra não existe, cria novo item
        HashItem* novoItem = (HashItem*) malloc(sizeof(HashItem));
        novoItem->palavra = strdup(palavra);
        novoItem->lista_tweets = (TweetList*) malloc(sizeof(TweetList));
        novoItem->lista_tweets->rrn = rrn;
        novoItem->lista_tweets->prox = NULL;

        // Insere na lista de colisão
        novoItem->prox = ha->itens[pos];
        ha->itens[pos] = novoItem;
    }
    return 1;
}

// Busca uma palavra na tabela hash e retorna a lista de RRNs dos tweets onde ela aparece
TweetList* buscaHash(Hash* ha, char* palavra) {
    int pos = valorString(palavra) % ha->TABLE_SIZE;

    HashItem* atual = ha->itens[pos];
    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        return atual->lista_tweets;  // Retorna a lista de RRNs ou tweets
    }
    return NULL;  // Palavra não encontrada
}
