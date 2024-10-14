#include <stdio.h>
#include "lexer.h"

int main() {
    const char *expr = "a = true; b = false; c = a and b;";
    printf("Input: %s\n", expr);

    tokenize(expr);

    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }

    return 0;
}
