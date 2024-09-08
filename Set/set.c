#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

// Definição do tipo Set
struct set {
    int* elementos;
    int qtd;
    int capacidade;
    int iterador;
};

Set* criaSet() {
    Set* s = (Set*) malloc(sizeof(Set));
    if (s != NULL) {
        s->capacidade = 10;
        s->elementos = (int*) malloc(s->capacidade * sizeof(int));
        s->qtd = 0;
        s->iterador = 0;
    }
    return s;
}

void liberaSet(Set* s) {
    if (s != NULL) {
        free(s->elementos);
        free(s);
    }
}

int insereSet(Set* s, int num) {
    if (s == NULL)
        return 0;

    // Evita inserir duplicatas
    if (consultaSet(s, num))
        return 0;

    // Realoca memória se necessário
    if (s->qtd == s->capacidade) {
        s->capacidade *= 2;
        s->elementos = (int*) realloc(s->elementos, s->capacidade * sizeof(int));
    }

    // Insere o elemento no final do vetor
    s->elementos[s->qtd++] = num;
    return 1;
}

int removeSet(Set* s, int num) {
    if (s == NULL)
        return 0;

    // Encontra o elemento
    for (int i = 0; i < s->qtd; i++) {
        if (s->elementos[i] == num) {
            // Move os elementos seguintes uma posição para trás
            for (int j = i; j < s->qtd - 1; j++) {
                s->elementos[j] = s->elementos[j + 1];
            }
            s->qtd--;
            return 1;
        }
    }
    return 0;
}

int tamanhoSet(Set* s) {
    if (s == NULL)
        return 0;
    return s->qtd;
}

int consultaSet(Set* s, int num) {
    if (s == NULL)
        return 0;

    // Verifica se o número está no conjunto
    for (int i = 0; i < s->qtd; i++) {
        if (s->elementos[i] == num)
            return 1;
    }
    return 0;
}

void imprimeSet(Set* s) {
    if (s == NULL)
        return;

    printf("{ ");
    for (int i = 0; i < s->qtd; i++) {
        printf("%d ", s->elementos[i]);
    }
    printf("}\n");
}

// Funções para iteração
void beginSet(Set *s) {
    if (s != NULL)
        s->iterador = 0;
}

int endSet(Set *s) {
    if (s == NULL || s->iterador >= s->qtd)
        return 1;
    return 0;
}

void nextSet(Set *s) {
    if (s != NULL && s->iterador < s->qtd)
        s->iterador++;
}

void getItemSet(Set *s, int *num) {
    if (s != NULL && s->iterador < s->qtd)
        *num = s->elementos[s->iterador];
}

// Função para união de conjuntos
Set* uniaoSet(Set* A, Set* B) {
    if (A == NULL || B == NULL)
        return NULL;

    Set* C = criaSet();
    int x;

    for (beginSet(A); !endSet(A); nextSet(A)) {
        getItemSet(A, &x);
        insereSet(C, x);
    }

    for (beginSet(B); !endSet(B); nextSet(B)) {
        getItemSet(B, &x);
        insereSet(C, x);
    }

    return C;
}

// Função para interseção de conjuntos
Set* interseccaoSet(Set* A, Set* B) {
    if (A == NULL || B == NULL)
        return NULL;

    Set* C = criaSet();
    int x;

    for (beginSet(A); !endSet(A); nextSet(A)) {
        getItemSet(A, &x);
        if (consultaSet(B, x))
            insereSet(C, x);
    }

    return C;
}

// Função para diferença de conjuntos (A - B)
Set* diferencaSet(Set* A, Set* B) {
    if (A == NULL || B == NULL)
        return NULL;

    Set* C = criaSet();
    int x;

    for (beginSet(A); !endSet(A); nextSet(A)) {
        getItemSet(A, &x);
        if (!consultaSet(B, x))
            insereSet(C, x);
    }

    return C;
}
