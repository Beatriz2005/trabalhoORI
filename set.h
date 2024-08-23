#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>

// Definição do tipo Set
struct set {
    int *rnns;    // Array para armazenar os RNNs
    int qtd;      // Quantidade de elementos no Set
    int capacidade; // Capacidade do array
    int iter;     // Iterador para percorrer o Set
};

#define SIZE 10

typedef struct set Set;

Set* criaSet();
void liberaSet(Set* s);
int insereSet(Set* s, int rrn);
int removeSet(Set* s, int rrn);
int tamanhoSet(Set* s);
void imprimeSet(Set* s);
static int redimensionaSet(Set* s);
int consultaSet(Set* s, int rrn);
Set* uniaoSet(Set* A, Set* B);
Set* interseccaoSet(Set* A, Set* B);
void beginSet(Set *s);
int endSet(Set *s);
void nextSet(Set *s);
void getItemSet(Set *s, int *rrn);

#endif // SET_H