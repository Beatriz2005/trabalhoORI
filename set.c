#include "Set.h"

// Função para criar um novo Set
Set* criaSet() {
    Set* s = (Set*) malloc(sizeof(Set));
    if (s != NULL) {
        s->rnns = (int*) malloc(SIZE * sizeof(int));
        if (s->rnns == NULL) {
            free(s);
            return NULL;
        }
        s->qtd = 0;
        s->capacidade = SIZE;
        s->iter = -1; // Inicia o iterador como inválido
    }
    return s;
}

// Função para liberar a memória alocada pelo Set
void liberaSet(Set* s) {
    if (s != NULL) {
        free(s->rnns);
        free(s);
    }
}

// Função para inserir um RNN no Set (não permite duplicatas)
int insereSet(Set* s, int rrn) {
    if (s == NULL) return 0;

    // Verifica se o RNN já está no Set
    for (int i = 0; i < s->qtd; i++) {
        if (s->rnns[i] == rrn) {
            return 1; // RNN já está no Set
        }
    }

    // Se necessário, redimensiona o array
    if (s->qtd == s->capacidade) {
        if (!redimensionaSet(s)) {
            return 0; // Falha ao redimensionar
        }
    }

    // Insere o novo RNN
    s->rnns[s->qtd] = rrn;
    s->qtd++;
    return 1;
}

// Função para redimensionar o array de RNNs
static int redimensionaSet(Set* s) {
    int nova_capacidade = s->capacidade * 2;
    int *nova_rnns = (int*) realloc(s->rnns, nova_capacidade * sizeof(int));
    if (nova_rnns == NULL) {
        return 0;
    }
    s->rnns = nova_rnns;
    s->capacidade = nova_capacidade;
    return 1;
}


// Função para consultar se um RNN está no Set
int consultaSet(Set* s, int rrn) {
    if (s == NULL) return 0;

    for (int i = 0; i < s->qtd; i++) {
        if (s->rnns[i] == rrn) {
            return 1; // RNN encontrado
        }
    }
    return 0; // RNN não encontrado
}

void imprimeSet(Set* s) {
    if (s == NULL) {
        return;
    }
    printf("RNNs no Set:\n");
    for (int i = 0; i < s->qtd; i++) {  // Corrigido de 'tamanho' para 'qtd'
        printf("%d\n", s->rnns[i]);
    }
}

// Função para remover um RNN do Set
int removeSet(Set* s, int rrn) {
    if (s == NULL) return 0;

    for (int i = 0; i < s->qtd; i++) {
        if (s->rnns[i] == rrn) {
            s->rnns[i] = s->rnns[s->qtd - 1]; // Substitui pelo último
            s->qtd--;
            return 1; // RNN removido
        }
    }
    return 0; // RNN não encontrado
}

// Função para obter o tamanho do Set
int tamanhoSet(Set* s) {
    if (s == NULL) return 0;
    return s->qtd;
}

// Função para iniciar o iterador do Set
void beginSet(Set *s) {
    if (s != NULL) {
        s->iter = 0;
    }
}

// Função para verificar se o iterador chegou ao fim
int endSet(Set *s) {
    if (s == NULL || s->iter >= s->qtd) {
        return 1;
    }
    return 0;
}

// Função para avançar o iterador para o próximo elemento
void nextSet(Set *s) {
    if (s != NULL && s->iter < s->qtd) {
        s->iter++;
    }
}

// Função para obter o item atual apontado pelo iterador
void getItemSet(Set *s, int *rrn) {
    if (s != NULL && s->iter < s->qtd) {
        *rrn = s->rnns[s->iter];
    }
}

// Função para unir dois conjuntos em um novo Set
Set* uniaoSet(Set* A, Set* B) {
    if (A == NULL || B == NULL) return NULL;

    Set* C = criaSet();
    if (C == NULL) return NULL;

    int rrn;
    for (beginSet(A); !endSet(A); nextSet(A)) {
        getItemSet(A, &rrn);
        insereSet(C, rrn);
    }

    for (beginSet(B); !endSet(B); nextSet(B)) {
        getItemSet(B, &rrn);
        insereSet(C, rrn);
    }

    return C;
}

// Função para encontrar a interseção de dois conjuntos em um novo Set
Set* interseccaoSet(Set* A, Set* B) {
    if (A == NULL || B == NULL) return NULL;

    Set* C = criaSet();
    if (C == NULL) return NULL;

    int rrn;
    for (beginSet(A); !endSet(A); nextSet(A)) {
        getItemSet(A, &rrn);
        if (consultaSet(B, rrn)) {
            insereSet(C, rrn);
        }
    }

    return C;
}
