#include <stdio.h>
#include <stdlib.h>  // For malloc and free
#include "lexer.h"

#define MAX_EXPR_LENGTH 100  // Define a maximum length for the expression

int main() {
    // Open the input file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open input.txt\n");
        return 1;
    }

    // Allocate memory for the expression
    char *expr = malloc(MAX_EXPR_LENGTH);
    if (expr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read the expression from the file
    if (fgets(expr, MAX_EXPR_LENGTH, file) == NULL) {
        fprintf(stderr, "Error: Could not read from input.txt\n");
        free(expr);
        fclose(file);
        return 1;
    }
    fclose(file);  // Close the file

    // Print the input expression
    printf("Input: %s\n", expr);

    // Tokenize the expression
    tokenize(expr);

    // Print the tokens
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }

    free(expr);  // Free the allocated memory
    return 0;
}
