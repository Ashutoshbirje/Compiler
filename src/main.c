#include <stdio.h>
#include <stdlib.h>  // For malloc and free
#include "lexer.h"
#include "parser.h"
#include "constants.h"  // Include constants.h for SCREEN_WIDTH

void printLine() {
    printf("+--------------------+--------------------+\n");
}

int main() {
    // Open the input file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open input.txt\n");
        return 1;
    }

    // Allocate memory for the expression
    char *expr = malloc(MAX_EXPRESSION_LENGTH);
    if (expr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read the expression from the file
    if (fgets(expr, MAX_EXPRESSION_LENGTH, file) == NULL) {
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

    // Print the tokens in a table format
    printf("\nTokens:\n");
    printLine(); // Header line
    printf("| %-18s | %-18s |\n", "Token", "Value");
    printLine(); // Separator line
    for (int i = 0; i < token_count; i++) {
        printf("| %-18s | %-18s |\n", getTokenTypeString(tokens[i].type), tokens[i].value);
    }
    printLine(); // Footer line

    // Parse tree
    int index = 0;
    Node* parseTree = parseExpression(expr, &index);

    // Evaluate the parse tree and store the result at each node
    evaluate(parseTree);

    // Print the parse tree horizontally with intermediate results
    printf("Generated Parse Tree for (%s):\n", expr);
    printParseTree(parseTree, 0, SCREEN_WIDTH / 2);  // Start in the middle of the screen

    // Print the final result
    printf("\nFinal Result at Root: %s\n", parseTree->value ? "T" : "F");

    // Free the allocated memory (not shown in this example)
    free(expr);  // Free the allocated memory
    return 0;
}
