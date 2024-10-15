#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 100

typedef enum {
    TOKEN_ID,     // Identifier
    TOKEN_ASSIGN, // '=' operator
    TOKEN_AND,    // 'and' operator
    TOKEN_OR,     // 'or' operator
    TOKEN_BOOL,   // Boolean values 'true' or 'false'
    TOKEN_XOR,    // XOR operator
    TOKEN_NOT,   // Negation operator
       TOKEN_LPAREN,  // Left Parenthesis
    TOKEN_RPAREN   // Right Parenthesis
} TokenType;

typedef struct {
    char value[20]; // Token value
    TokenType type; // Token type
} Token;

extern Token tokens[MAX_TOKENS];  // Declare the token array as extern
extern int token_count;             // Declare token_count as extern

void tokenize(const char *expr);

const char* getTokenTypeString(TokenType type); // Function declaration to get string representation

#endif // LEXER_H
