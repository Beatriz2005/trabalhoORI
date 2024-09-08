#ifndef PILHA_H
#define PILHA_H

#define MAX_TOKENS 256

#include "../Noh/noh.h"

// Estrutura da pilha
typedef struct Pilha {
    Noh* nohs[MAX_TOKENS];
    int topo;
} Pilha;

// Funções para manipulação da pilha
void inicializar_pilha(Pilha* p);
int pilha_vazia(Pilha* p);
void empilhar(Pilha* p, Noh* noh);
Noh* desempilhar(Pilha* p);
Noh* topo_pilha(Pilha* p);

#endif // PILHA_H
