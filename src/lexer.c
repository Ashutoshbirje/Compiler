#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

Token tokens[100];
int token_count = 0;

void add_token(const char *value, TokenType type) {
    strcpy(tokens[token_count].value, value);
    tokens[token_count].type = type;
    token_count++;
}

void tokenize(const char *expr) {
    char buffer[20];
    int i = 0, j = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        } else if (isalpha(expr[i])) {
            buffer[j++] = expr[i++];
            buffer[j] = '\0';

            if (strcmp(buffer, "true") == 0) {
                add_token(buffer, TOKEN_TRUE);
            } else if (strcmp(buffer, "false") == 0) {
                add_token(buffer, TOKEN_FALSE);
            } else if (strcmp(buffer, "and") == 0) {
                add_token(buffer, TOKEN_AND);
            } else if (strcmp(buffer, "or") == 0) {
                add_token(buffer, TOKEN_OR);
            } else {
                add_token(buffer, TOKEN_ID);
            }
            j = 0;
        } else if (expr[i] == '=') {
            add_token("=", TOKEN_ASSIGN);
            i++;
        } else if (expr[i] == ';') {
            add_token(";", TOKEN_SEMICOLON);
            i++;
        } else {
            add_token("?", TOKEN_UNKNOWN);
            i++;
        }
    }
}
