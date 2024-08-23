#include "cleaning.h"

// Função para remover pontuações e espaços em excesso
void limpar_string(char* str) {
    int i, j = 0;
    int n = strlen(str);
    int espaco_anterior = 1; // Para rastrear espaços em branco

    for (i = 0; i < n; i++) {
        if (ispunct(str[i]) && str[i] != ':') {
            continue;  // Ignora pontuações, exceto ':'
        }
        
        if (isspace(str[i])) {
            if (espaco_anterior) {
                continue;  // Ignora espaços em excesso
            }
            str[j++] = ' ';  // Mantém um único espaço
            espaco_anterior = 1;
        } else {
            str[j++] = str[i];  // Copia o caractere não-espacial
            espaco_anterior = 0;
        }
    }
    
    // Remove espaços ao final da string
    if (j > 0 && isspace(str[j - 1])) {
        j--;
    }
    
    str[j] = '\0';  // Finaliza a string com '\0'
}

char *removeAcentos(char *word) {
    char *p = word;
    char *q = word;
    while (*p) {
        unsigned char ch = *p;
        // Verifica caracteres acentuados comuns e substitui por não acentuados
        if (ch == 0xE1 || ch == 0xE0 || ch == 0xE2 || ch == 0xE3 || ch == 0xE4) *q++ = 'a';  // á à â ã ä
        else if (ch == 0xC1 || ch == 0xC0 || ch == 0xC2 || ch == 0xC3 || ch == 0xC4) *q++ = 'a';  // Á À Â Ã Ä
        else if (ch == 0xE9 || ch == 0xE8 || ch == 0xEA || ch == 0xEB) *q++ = 'e';  // é è ê ë
        else if (ch == 0xC9 || ch == 0xC8 || ch == 0xCA || ch == 0xCB) *q++ = 'e';  // É È Ê Ë
        else if (ch == 0xED || ch == 0xEC || ch == 0xEE || ch == 0xEF) *q++ = 'i';  // í ì î ï
        else if (ch == 0xCD || ch == 0xCC || ch == 0xCE || ch == 0xCF) *q++ = 'i';  // Í Ì Î Ï
        else if (ch == 0xF3 || ch == 0xF2 || ch == 0xF4 || ch == 0xF5 || ch == 0xF6) *q++ = 'o';  // ó ò ô õ ö
        else if (ch == 0xD3 || ch == 0xD2 || ch == 0xD4 || ch == 0xD5 || ch == 0xD6) *q++ = 'o';  // Ó Ò Ô Õ Ö
        else if (ch == 0xFA || ch == 0xF9 || ch == 0xFB || ch == 0xFC) *q++ = 'u';  // ú ù û ü
        else if (ch == 0xDA || ch == 0xD9 || ch == 0xDB || ch == 0xDC) *q++ = 'u';  // Ú Ù Û Ü
        else if (ch == 0xE7) *q++ = 'c';  // ç
        else if (ch == 0xC7) *q++ = 'c';  // Ç
        else if (ch >= 'A' && ch <= 'Z') *q++ = ch + 32;  // Converte maiúsculas para minúsculas
        else if (ch >= 'a' && ch <= 'z' || isdigit(ch) || ch == ':') *q++ = ch;  // Adiciona números e ':' como parte da palavra
        else if (ch == ' ' && (q == word || *(q - 1) != ' ')) *q++ = ' ';  // Remove espaços duplos
        // Ignora outros caracteres
        p++;
    }
    *q = '\0';
    return word;
}

void processPost(Hash* ha, char* text, int rrn) {
    char* tempText = strdup(text);  // Duplicar o texto para não modificar o original
    char* word = strtok(tempText, " ,.-!?");  // Separar palavras
    while (word != NULL) {
        removeAcentos(word);  // Remove acentos e converte para minúsculas
        insereHash_EnderAberto(ha, word, rrn);  // Inserir na hash
        printf("Palavra processada: %s\n", word);
        word = strtok(NULL, " ,.-!?");
    }
    free(tempText);  // Liberar a memória alocada para a cópia do texto
}
