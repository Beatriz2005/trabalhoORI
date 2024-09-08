#include "leitura.h"
#include "../TabelaHash/tabelaHash.h"
#include "../Pilha/pilha.h"
#include "../Arvore/arvore.h"

// Função para copiar string
char* copiar_string(const char* origem) {
    char* copia = malloc(strlen(origem) + 1);
    if (!copia) {
        perror("Erro ao alocar memória");
        return NULL;
    }
    strcpy(copia, origem);
    return copia;
}

// Função para aparar espaços
char* aparar(char* str) {
    char* fim;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    fim = str + strlen(str) - 1;
    while (fim > str && isspace((unsigned char)*fim)) fim--;
    *(fim + 1) = 0;
    return str;
}

// Função para ler os tweets do arquivo CSV
Tweet* ler_tweets(const char* arquivo, int* linhas_lidas, int n_linhas) {
    FILE *arq = fopen(arquivo, "r");
    if (!arq) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Tweet* tweets = NULL;
    char linha[MAX_LINHA];
    int n_tweets = 0;

    while (fgets(linha, sizeof(linha), arq) && n_tweets < n_linhas) {
        int len = strlen(linha);
        while (len > 0 && (linha[len - 1] == '\n')) {
            linha[len - 1] = '\0';
            len--;
        }

        Tweet* temp = (Tweet*)realloc(tweets, sizeof(Tweet) * (n_tweets + 1));
        if (!temp) {
            perror("Erro ao alocar memória");
            free(tweets);
            fclose(arq);
            return NULL;
        }
        tweets = temp;

        char* token = strtok(linha, ",");
        tweets[n_tweets].id = atoi(token);
        token = strtok(NULL, ",");
        tweets[n_tweets].opiniao = atoi(token);
        token = strtok(NULL, "");
        tweets[n_tweets].texto = copiar_string(aparar(token));

        if (!tweets[n_tweets].texto) {
            free(tweets);
            fclose(arq);
            return NULL;
        }

        n_tweets++;
    }

    fclose(arq);
    *linhas_lidas = n_tweets;
    return tweets;
}

// Função para inserir palavras dos tweets na tabela hash
void inserir_palavras_na_hash(Hash* tabela_hash, Tweet* tweets, int n_tweets) {
    for (int i = 0; i < n_tweets; i++) {
        char* texto = strdup(tweets[i].texto);
        char* palavra = strtok(texto, " ,.!?;:");

        while (palavra != NULL) {
            insereHash(tabela_hash, palavra, i);  // Insere cada palavra na tabela hash
            palavra = strtok(NULL, " ,.!?;:");
        }

        free(texto);
    }
}

// Função para verificar se o token é um operador
int eh_operador(const char* token) {
    return strcmp(token, "AND") == 0 || strcmp(token, "OR") == 0 || strcmp(token, "NOT") == 0;
}

// Função para identificar o operador
TipoOperador identificar_operador(const char* token) {
    if (strcmp(token, "AND") == 0) return OP_AND;
    if (strcmp(token, "OR") == 0) return OP_OR;
    if (strcmp(token, "NOT") == 0) return OP_NOT;
    return -1;  // Valor inválido se não for um operador reconhecido
}

// Função para interpretar e construir a árvore de busca
Noh* interpretar_pesquisa(char* pesquisa) {
    Pilha operadores;
    Pilha operandos;
    inicializar_pilha(&operadores);
    inicializar_pilha(&operandos);

    int i = 0;
    while (pesquisa[i] != '\0') {
        if (pesquisa[i] == ' ') {
            i++;
            continue;
        }

        if (pesquisa[i] == '(') {
            i++;
        } else if (pesquisa[i] == ')') {
            while (!pilha_vazia(&operadores) && topo_pilha(&operadores)->tipo == NOH_OPERADOR) {
                Noh* operador = desempilhar(&operadores);
                if (operador->operador == OP_NOT) {
                    Noh* filho = desempilhar(&operandos);
                    operador->direita = filho;
                    empilhar(&operandos, operador);
                } else {
                    Noh* direita = desempilhar(&operandos);
                    Noh* esquerda = desempilhar(&operandos);
                    operador->esquerda = esquerda;
                    operador->direita = direita;
                    empilhar(&operandos, operador);
                }
            }
            i++;
        } else if (pesquisa[i] == 'A' || pesquisa[i] == 'O' || pesquisa[i] == 'N') {
            char token[4] = {0};
            int j = 0;
            while (pesquisa[i] != ' ' && pesquisa[i] != '\0' && j < 3) {
                token[j++] = pesquisa[i++];
            }
            token[j] = '\0';

            if (eh_operador(token)) {
                Noh* operador = criar_noh_operador(identificar_operador(token), NULL, NULL);
                empilhar(&operadores, operador);
            }
        } else {
            char palavra[100] = {0};
            int j = 0;
            while (pesquisa[i] != ' ' && pesquisa[i] != ')' && pesquisa[i] != '\0') {
                palavra[j++] = pesquisa[i++];
            }
            palavra[j] = '\0';

            Noh* no_palavra = criar_noh_palavra(palavra);
            empilhar(&operandos, no_palavra);
        }
    }

    while (!pilha_vazia(&operadores)) {
        Noh* operador = desempilhar(&operadores);
        if (operador->operador == OP_NOT) {
            Noh* filho = desempilhar(&operandos);
            operador->direita = filho;
            empilhar(&operandos, operador);
        } else {
            Noh* direita = desempilhar(&operandos);
            Noh* esquerda = desempilhar(&operandos);
            operador->esquerda = esquerda;
            operador->direita = direita;
            empilhar(&operandos, operador);
        }
    }

    return desempilhar(&operandos);
}
