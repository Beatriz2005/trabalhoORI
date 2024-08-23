#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#ifndef LIMPAR_STRING_H
#define LIMPAR_STRING_H

void limpar_string(char* str);
void separarPalavras(char *frase);
char *removeAcentos(char *frase);
void processPost(Hash* ha, char* text, int rrn);

#endif
