#include "lexer.h"
#include <string.h>  // For strncpy
#include <stdio.h>   // For printf

Token tokens[MAX_TOKENS];  // Token array
int token_count = 0;       // Keeps track of token count

void tokenize(const char *expr) {
    char temp[20];  // Temporary buffer for identifiers and boolean values
    int pos = 0;    // Position in temp buffer

    for (int i = 0; expr[i] != '\0'; i++) {
        // Skip spaces
        if (expr[i] == ' ') {
            continue;
        }

        // Check for operators and keywords
        if (expr[i] == '=') {
            tokens[token_count++] = (Token){ .value = "=", .type = TOKEN_ASSIGN };
        } else if (strncmp(&expr[i], "and", 3) == 0) {
            tokens[token_count++] = (Token){ .value = "and", .type = TOKEN_AND };
            i += 2;  // Skip past "and"
        } else if (strncmp(&expr[i], "or", 2) == 0) {
            tokens[token_count++] = (Token){ .value = "or", .type = TOKEN_OR };
            i += 1;  // Skip past "or"
        } else if (expr[i] == ';') {
            // End of statement; do nothing
        } else {
            // Handle identifiers and boolean literals
            while (expr[i] != ' ' && expr[i] != ';' && expr[i] != '=' && expr[i] != '\0') {
                temp[pos++] = expr[i];
                i++;
            }
            temp[pos] = '\0';  // Null-terminate the string
            pos = 0;          // Reset position

            // Check for boolean values
            if (strcmp(temp, "true") == 0) {
                tokens[token_count++] = (Token){ .value = "true", .type = TOKEN_BOOL };
            } else if (strcmp(temp, "false") == 0) {
                tokens[token_count++] = (Token){ .value = "false", .type = TOKEN_BOOL };
            } else {
                // Otherwise, treat it as an identifier
                tokens[token_count++] = (Token){ .value = "", .type = TOKEN_ID };
                strncpy(tokens[token_count - 1].value, temp, sizeof(tokens[token_count - 1].value) - 1);
            }
            i--;  // Decrement to account for the outer loop's increment
        }
    }
}
