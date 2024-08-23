#ifndef HASH_H
#define HASH_H
#include "Set.h" // Necessário para utilizar a estrutura Set
#include <stdio.h>
#include <stdlib.h>

typedef char* String;

typedef struct hash Hash;

// Estrutura para armazenar uma palavra e os RRN's associados
struct palavra {
    char* string;
    Set* rrns;  // Estrutura de conjunto que armazena os RRN's
};

// Estrutura da tabela hash
struct hash{
    int qtd, TABLE_SIZE;
    struct palavra** itens;
};
// Função para criar uma nova tabela hash
Hash* criaHash(int TABLE_SIZE);

// Função para liberar a memória alocada pela tabela hash
void liberaHash(Hash* ha);

// Função para calcular o valor de hash de uma string
int valorString(char* str);

// Função para inserir uma nova palavra na tabela hash com tratamento de colisões
int insereHash_EnderAberto(Hash* ha, char* palavra, int rrn);

// Função para buscar uma palavra na tabela hash e recuperar os RNNs associados
int buscaHash_EnderAberto(Hash* ha, char* palavra, Set** rrns);

#endif // HASH_H
