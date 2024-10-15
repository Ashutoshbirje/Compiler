#include "lexer.h"
#include <string.h>  
#include <stdio.h>   

Token tokens[MAX_TOKENS]; 
int token_count = 0;       

void tokenize(const char *expr) {
    char temp[20]; 
    int pos = 0;   

    for (int i = 0; expr[i] != '\0'; i++) {
        
        // Handle parentheses
        if (expr[i] == '(') {
            tokens[token_count++] = (Token){ .value = "(", .type = TOKEN_LPAREN };
            continue;
        } else if (expr[i] == ')') {
            tokens[token_count++] = (Token){ .value = ")", .type = TOKEN_RPAREN };
            continue;
        }

        // Ignore whitespace
        if (expr[i] == ' ') continue;

        // Handle operators and keywords
        if (expr[i] == '=') {
            tokens[token_count++] = (Token){ .value = "=", .type = TOKEN_ASSIGN };
        } else if (strncmp(&expr[i], "and", 3) == 0) {
            tokens[token_count++] = (Token){ .value = "&", .type = TOKEN_AND };
            i += 2;  // Skip "and"
        } else if (strncmp(&expr[i], "or", 2) == 0) {
            tokens[token_count++] = (Token){ .value = "|", .type = TOKEN_OR };
            i += 1;  // Skip "or"
        } else if (strncmp(&expr[i], "xor", 3) == 0) {
            tokens[token_count++] = (Token){ .value = "^", .type = TOKEN_XOR };
            i += 2;  // Skip "xor"
        } else if (strncmp(&expr[i], "negation", 8) == 0) {
            tokens[token_count++] = (Token){ .value = "negation", .type = TOKEN_NOT };
            i += 7;  // Skip "negation"
        } else if (expr[i] == '&') {
            tokens[token_count++] = (Token){ .value = "&", .type = TOKEN_AND };
        } else if (expr[i] == '|') {
            tokens[token_count++] = (Token){ .value = "|", .type = TOKEN_OR };
        } else if (expr[i] == '^') {
            tokens[token_count++] = (Token){ .value = "^", .type = TOKEN_XOR };
        } else if (expr[i] == '~') {
            tokens[token_count++] = (Token){ .value = "~", .type = TOKEN_NOT };
        } else {
            // Handle identifiers and boolean literals
            pos = 0;
            while (expr[i] != ' ' && expr[i] != ';' && expr[i] != '=' && 
                   expr[i] != '&' && expr[i] != '|' && expr[i] != '^' && 
                   expr[i] != '~' && expr[i] != '\0' && expr[i] != '(' && expr[i] != ')') {
                temp[pos++] = expr[i++];
            }
            temp[pos] = '\0';  // Null-terminate the string
            
            // Check for boolean values
            if (strcmp(temp, "true") == 0) {
                tokens[token_count++] = (Token){ .value = "true", .type = TOKEN_BOOL };
            } else if (strcmp(temp, "false") == 0) {
                tokens[token_count++] = (Token){ .value = "false", .type = TOKEN_BOOL };
            } else {
                // Treat it as an identifier
                tokens[token_count++] = (Token){ .value = "", .type = TOKEN_ID };
                strncpy(tokens[token_count - 1].value, temp, sizeof(tokens[token_count - 1].value) - 1);
            }
            i--;  // Adjust index to reprocess current character
        }
    }
}

// Function to return string representation of token types
const char* getTokenTypeString(TokenType type) {
    switch (type) {
        case TOKEN_ID: return "id";
        case TOKEN_ASSIGN: return "relop";
        case TOKEN_AND: return "bitop";
        case TOKEN_OR: return "bitop";
        case TOKEN_BOOL: return "keyword";
        case TOKEN_XOR: return "bitop";
        case TOKEN_NOT: return "bitop";
        case TOKEN_LPAREN: return "lparen";
        case TOKEN_RPAREN: return "rparen";
        default: return "unknown";
    }
}
