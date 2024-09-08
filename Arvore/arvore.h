#ifndef ARVORE_H
#define ARVORE_H

#include "../Noh/noh.h"

// Funções para manipulação da árvore
Noh* criar_noh_operador(TipoOperador operador, Noh* esquerda, Noh* direita);
Noh* criar_noh_palavra(const char* palavra);
void liberar_arvore(Noh* raiz);
void imprimir_arvore_indentada(Noh* raiz, int nivel);
void imprimir_arvore(Noh* raiz);

#endif // ARVORE_H
