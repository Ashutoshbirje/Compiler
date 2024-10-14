#include <stdio.h>
#include "lexer.h"

int main() {
    const char *expr = "a = true; b = false; c = a and b;";
    printf("Input: %s\n", expr);

    tokenize(expr);

    // Print the tokens
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        Token token = tokens[i];
        const char *token_type;
        switch (token.type) {
            case TOKEN_ID: token_type = "IDENTIFIER"; break;
            case TOKEN_ASSIGN: token_type = "ASSIGN"; break;
            case TOKEN_AND: token_type = "AND"; break;
            case TOKEN_OR: token_type = "OR"; break;
            case TOKEN_BOOL: token_type = "BOOLEAN"; break;
            default: token_type = "UNKNOWN"; break;
        }
        printf("Type: %s, Value: %s\n", token_type, token.value);
    }

    return 0;
}
