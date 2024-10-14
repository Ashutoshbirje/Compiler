#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"

int main() {
    init_symbol_table();

    const char *expr = "a = true; b = false; c = a and b;";
    printf("Input: %s\n", expr);

    tokenize(expr);
    parse();

    printf("Symbol Table:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%s: %d\n", symbols[i].name, symbols[i].value);
    }

    return 0;
}
