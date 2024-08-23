#include "hash.h"

// Função para criar a tabela hash
Hash* criaHash(int TABLE_SIZE) {
    Hash* ha = (Hash*)malloc(sizeof(Hash));
    if (ha != NULL) {
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->qtd = 0;
        ha->itens = (struct palavra**)malloc(TABLE_SIZE * sizeof(struct palavra*));
        if (ha->itens == NULL) {
            free(ha);
            return NULL;
        }
        for (int i = 0; i < ha->TABLE_SIZE; i++)
            ha->itens[i] = NULL;
    }
    return ha;
}

// Função para liberar a tabela hash
void liberaHash(Hash* ha) {
    if (ha != NULL) {
        for (int i = 0; i < ha->TABLE_SIZE; i++) {
            if (ha->itens[i] != NULL) {
                liberaSet(ha->itens[i]->rrns); // Liberar o conjunto de RNNs
                free(ha->itens[i]->string);    // Liberar a string da palavra
                free(ha->itens[i]);            // Liberar a estrutura palavra
            }
        }
        free(ha->itens);
        free(ha);
    }
}

// Função para calcular o valor de uma string para a hash
int valorString(char* str) {
    int valor = 7;
    int tam = strlen(str);
    for (int i = 0; i < tam; i++)
        valor = 31 * valor + (int)str[i];
    return valor & 0x7FFFFFFF;
}

// Função para cálculo de chave por divisão
int chaveDivisao(int chave, int TABLE_SIZE) {
    return chave % TABLE_SIZE;
}

// Função para sondagem linear
int sondagemLinear(int pos, int i, int TABLE_SIZE) {
    return (pos + i) % TABLE_SIZE;
}

// Função para inserir na tabela hash
int insereHash_EnderAberto(Hash* ha, char* palavra, int rrn) {
    if (ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    int chave = valorString(palavra);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);

    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        int newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL) {
            struct palavra* novaPalavra = (struct palavra*)malloc(sizeof(struct palavra));
            novaPalavra->string = strdup(palavra);  // Copiar a palavra
            novaPalavra->rrns = criaSet();          // Criar o conjunto de RNN's
            insereSet(novaPalavra->rrns, rrn);      // Inserir o RNN no conjunto
            ha->itens[newPos] = novaPalavra;
            ha->qtd++;
            return 1;
        } else if (strcmp(ha->itens[newPos]->string, palavra) == 0) {
            insereSet(ha->itens[newPos]->rrns, rrn);  // Se a palavra já existe, apenas adicionar o RNN
            return 1;
        }
    }
    return 0; // Tabela hash cheia
}

// Função para buscar na tabela hash
int buscaHash_EnderAberto(Hash* ha, char* palavra, Set** rrns) {
    if (ha == NULL)
        return 0;

    int chave = valorString(palavra);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);

    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        int newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if (ha->itens[newPos] == NULL)
            return 0; // Não encontrado

        if (strcmp(ha->itens[newPos]->string, palavra) == 0) {
            *rrns = ha->itens[newPos]->rrns;  // Retorna o ponteiro para o conjunto de RNNs
            return 1; // Encontrado
        }
    }
    return 0;
}
