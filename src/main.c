#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"

int main() {
    init_symbol_table();

    const char *expr = "a = true; b = false; c = a and b;";
    printf("Input: %s\n", expr);

    tokenize(expr);
    ParseNode *root = parse();  // Get the parse tree root

    printf("Symbol Table:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%s: %d\n", symbols[i].name, symbols[i].value);
    }

    printf("Parse Tree:\n");
    print_parse_tree(root);  // Print the parse tree

    return 0;
}
