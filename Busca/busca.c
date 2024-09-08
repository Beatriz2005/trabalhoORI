#include <stdio.h>
#include "busca.h"
#include "../Set/set.h"
#include "../TabelaHash/tabelaHash.h"
#include "../Arvore/arvore.h"

// Função auxiliar para avaliar a árvore de busca
Set* avaliar_arvore(Noh* raiz, Hash* tabela_hash) {
    if (!raiz) return criaSet();

    if (raiz->tipo == NOH_PALAVRA) {
        // Buscar na tabela hash pela palavra e retornar o conjunto de tweets associados
        TweetList* lista_tweets = buscaHash(tabela_hash, raiz->palavra);
        Set* resultado = criaSet();
        
        // Converte a lista de tweets em um conjunto
        while (lista_tweets != NULL) {
            insereSet(resultado, lista_tweets->rrn);  // Adiciona o RRN ao conjunto
            lista_tweets = lista_tweets->prox;
        }

        return resultado;
    }

    if (raiz->tipo == NOH_OPERADOR) {
        Set* resultado_esquerda = avaliar_arvore(raiz->esquerda, tabela_hash);
        Set* resultado_direita = avaliar_arvore(raiz->direita, tabela_hash);

        Set* resultado = NULL;

        switch (raiz->operador) {
            case OP_AND:
                resultado = interseccaoSet(resultado_esquerda, resultado_direita);
                break;
            case OP_OR:
                resultado = uniaoSet(resultado_esquerda, resultado_direita);
                break;
            case OP_NOT:
                resultado = diferencaSet(resultado_esquerda, resultado_direita);  // Exclui tweets da direita
                break;
        }

        liberaSet(resultado_esquerda);
        liberaSet(resultado_direita);
        return resultado;
    }

    return criaSet(); // Caso de erro, retorna um conjunto vazio
}

// Função para realizar a busca com base na árvore e na tabela hash
Set* realizar_busca(Noh* arvore, Hash* tabela_hash) {
    return avaliar_arvore(arvore, tabela_hash);
}

// Função para imprimir os tweets resultantes da busca
void imprimir_resultados(Tweet* tweets, int n_tweets, Set* resultado) {
    int tweet_id;
    for (beginSet(resultado); !endSet(resultado); nextSet(resultado)) {
        getItemSet(resultado, &tweet_id);
        // Busca o tweet correspondente pelo ID
        Tweet* tweet = buscaTweetPorID(tweets, n_tweets, tweet_id);
        if (tweet != NULL) {
            printf("Tweet ID: %d\nTexto: %s\n", tweet->id, tweet->texto);
        }
    }
}
