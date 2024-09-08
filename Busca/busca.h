#ifndef BUSCA_H
#define BUSCA_H

#include "../Set/set.h"
#include "../TabelaHash/tabelaHash.h"
#include "../Arvore/arvore.h"

// Funções para realizar a busca com base na árvore e na tabela hash
Set* realizar_busca(Noh* arvore, Hash* tabela_hash);

// Função para imprimir os tweets resultantes da busca
void imprimir_resultados(Tweet* tweets, int n_tweets, Set* resultado);

#endif // BUSCA_H
