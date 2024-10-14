#include "lexer.h"
#include <string.h>  // For strncpy

Token tokens[MAX_TOKENS];  // Token array
int token_count = 0;       // Keeps track of token count

void tokenize(const char *expr) {
    char temp[20];
    int pos = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' ' || expr[i] == ';' || expr[i] == '=' || expr[i] == '\0') {
            if (pos > 0) {
                temp[pos] = '\0';
                tokens[token_count++] = (Token){ .value = "", .type = TOKEN_ID };
                strncpy(tokens[token_count - 1].value, temp, sizeof(tokens[token_count - 1].value) - 1);
                pos = 0;
            }
        } else {
            temp[pos++] = expr[i];
        }
    }
}
