#include <stdio.h>
#include "pilha.h"
#include "../Noh/noh.h"

// Inicializa a pilha
void inicializar_pilha(Pilha* p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int pilha_vazia(Pilha* p) {
    return p->topo == -1;
}

// Empilha um nó
void empilhar(Pilha* p, Noh* noh) {
    if (p->topo < MAX_TOKENS - 1) {
        p->nohs[++(p->topo)] = noh;
    } else {
        fprintf(stderr, "Erro: pilha cheia\n");
    }
}

// Desempilha um nó
Noh* desempilhar(Pilha* p) {
    if (!pilha_vazia(p)) {
        return p->nohs[(p->topo)--];
    }
    return NULL;
}

// Retorna o topo da pilha sem desempilhar
Noh* topo_pilha(Pilha* p) {
    if (!pilha_vazia(p)) {
        return p->nohs[p->topo];
    }
    return NULL;
}
