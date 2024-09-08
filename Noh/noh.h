#ifndef NOH_H
#define NOH_H

typedef enum { NOH_OPERADOR, NOH_PALAVRA } TipoNoh;
typedef enum { OP_AND, OP_OR, OP_NOT } TipoOperador;

typedef struct Noh {
    TipoNoh tipo;
    union {
        TipoOperador operador; // Se for um operador
        char *palavra;         // Se for uma palavra
    };
    struct Noh *esquerda;
    struct Noh *direita;
} Noh;

#endif //NOH_H