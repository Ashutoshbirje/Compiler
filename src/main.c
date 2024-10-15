#include <stdio.h>
#include <stdlib.h>     // For malloc and free
#include <string.h>     // For strcspn
#include "lexer.h"      // Include lexer functions and declarations
#include "parser.h"     // Include parser functions and declarations
#include "tac.h"        // Include TAC functions and declarations
#include "constants.h"  // Include constants

void printLine() {
    printf("+--------------------+--------------------+\n");
}

// Function to check if a character is a valid operator
int isOperator(char ch) {
    return ch == '&' || ch == '|' || ch == '^' || ch == '~';
}

// Function to check if the expression is valid (with parentheses)
int isValidExpression(const char *expr) {
    int length = strlen(expr);
    int operandExpected = 1;  // Start expecting an operand
    int openParenCount = 0;   // To keep track of parentheses balance

    for (int i = 0; i < length; i++) {
        char ch = expr[i];

        // Ignore whitespace
        if (ch == ' ') continue;

        if (ch == '(') {
            openParenCount++;  // Track opening parentheses
            operandExpected = 1;  // Expect an operand after '('
        } else if (ch == ')') {
            if (openParenCount == 0 || operandExpected) return 0;  // Unmatched ')' or expecting operand
            openParenCount--;  // Closing a parenthesis
        } else if (ch == 'T' || ch == 'F') {
            // If operand (T/F), ensure it's in a valid position
            if (!operandExpected) return 0;
            operandExpected = 0;  // After operand, expect an operator
        } else if (isOperator(ch)) {
            if (ch == '~') {
                // '~' is allowed before an operand
                if (!operandExpected) return 0;
            } else {
                // For binary operators (&, |, ^), ensure it's after an operand
                if (operandExpected) return 0;
                operandExpected = 1;  // After operator, expect an operand
            }
        } else {
            // Invalid character detected
            return 0;
        }
    }

    // Ensure parentheses are balanced and no operand is expected at the end
    return openParenCount == 0 && !operandExpected;
}

int main() {
    // Open the input file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open input.txt\n");
        return 1;
    }

    // Allocate memory for the expression
    char *expr = malloc(MAX_EXPRESSION_LENGTH + 1);  // +1 for null terminator
    if (expr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read the expression from the file
    if (fgets(expr, MAX_EXPRESSION_LENGTH + 1, file) == NULL) {
        fprintf(stderr, "Error: Could not read from input.txt\n");
        free(expr);
        fclose(file);
        return 1;
    }
    fclose(file);  // Close file

    // Remove trailing newline (if any)
    expr[strcspn(expr, "\n")] = '\0';

    // Validate the input expression
    if (!isValidExpression(expr)) {
        fprintf(stderr, "Error: Invalid expression '%s'. Please enter a valid boolean expression.\n", expr);
        free(expr);
        return 1;
    }

    // Print the input expression
    printf("Input: %s\n", expr);

    // Tokenize the expression
    tokenize(expr); 

    // Print the tokens
    printf("\nTokens:\n");
    printLine();  // Header line
    printf("| %-18s | %-18s |\n", "Token", "Value");
    printLine();  // Separator line
    for (int i = 0; i < token_count; i++) {
        printf("| %-18s | %-18s |\n", getTokenTypeString(tokens[i].type), tokens[i].value);
    }
    printLine();  // Footer line

    // Parse the expression into a parse tree
    int index = 0;
    Node *parseTree = parseExpression(expr, &index);

    if (!parseTree) {
        fprintf(stderr, "Error: Invalid expression\n");
        free(expr);
        return 1;
    }

    // Evaluate the parse tree
    int result = evaluate(parseTree);

    // Print the parse tree
    printf("\nGenerated Parse Tree for '%s':\n", expr);
    printParseTree(parseTree, 0, SCREEN_WIDTH / 2);  // Start in the middle

    // Print the result
    printf("\nFinal Result at Root: %s\n", result ? "T" : "F");

    // Generate and print three-address code (TAC)
    printf("\nGenerating Three-Address Code (TAC):\n");
    generate_three_address_code(parseTree);
    print_TAC();

    // Generate low-level code from TAC
    generate_low_level_code();

    free(expr);

    return 0;
}
