#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../TabelaHash/tabelaHash.h"
#include "../Arvore/arvore.h"
#include "../Pilha/pilha.h"
#include "../Noh/noh.h"

#define MAX_LINHA 1024
#define MAX_BUSCA 256

// Estrutura para armazenar tweets
typedef struct {
    int id;
    int opiniao;
    char *texto;
} Tweet;

// Funções auxiliares para manipulação de strings e tweets
char* copiar_string(const char* origem);
char* aparar(char* str);
Tweet* ler_tweets(const char* arquivo, int* linhas_lidas, int n_linhas);
void imprimir_tweets(Tweet* tweets, int n_tweets);

// Função para inserir as palavras dos tweets na tabela hash
void inserir_palavras_na_hash(struct hash* tabela_hash, Tweet* tweets, int n_tweets);

// Função para interpretar a pesquisa
Noh* interpretar_pesquisa(char* pesquisa);

// Funções auxiliates para identificação de operadores
int eh_operador(const char* token);
TipoOperador identificar_operador(const char* token);

#endif // LEITURA_H
