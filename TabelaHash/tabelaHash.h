#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "../Leitura/leitura.h"

// Estrutura para armazenar a lista de tweets onde a palavra aparece
typedef struct tweet_list {
    int rrn;  // Índice ou posição do tweet no arquivo
    struct tweet_list* prox;  // Próximo tweet na lista
} TweetList;

// Estrutura para armazenar o item da tabela hash
typedef struct hash_item {
    char* palavra;  // Palavra (chave)
    TweetList* lista_tweets;  // Lista de RRNs ou identificadores dos tweets onde a palavra aparece
    struct hash_item* prox;  // Próximo item na lista de colisão
} HashItem;

// Estrutura da tabela hash
typedef struct hash {
    int TABLE_SIZE;
    HashItem** itens;  // Tabela hash que aponta para listas de colisão
} Hash;

// Funções da tabela hash
Hash* criaHash(int TABLE_SIZE);
void liberaHash(Hash* ha);
int valorString(char *str);
int insereHash(Hash* ha, char* palavra, int rrn);
TweetList* buscaHash(Hash* ha, char* palavra);

#endif // TABELA_HASH_H
