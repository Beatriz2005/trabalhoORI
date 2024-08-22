#ifndef POSTAGENS_H
#define POSTAGENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
    int docId;
    int opniao;
    char *texto;
} Postagem;

char* copiar_string(const char* origem);
Postagem* read_postagens(const char* arquivo, int* linhas_lidas, int n_linhas);
void print_postagens(Postagem* postagens, int n_postagem);

#endif // POSTAGENS_H
