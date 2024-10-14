#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 100  // Maximum number of tokens

// Token types enumeration
typedef enum {
    TOKEN_ID,     // Identifier
    TOKEN_ASSIGN, // '=' operator
    TOKEN_AND,    // 'and' operator
    TOKEN_OR,     // 'or' operator
    TOKEN_BOOL    // Boolean values 'true' or 'false'
} TokenType;

// Token structure definition
typedef struct {
    char value[20];  // Token value
    TokenType type;  // Token type
} Token;

// External declarations
extern Token tokens[MAX_TOKENS];
extern int token_count;

void tokenize(const char *expr);  // Function to tokenize input

#endif
