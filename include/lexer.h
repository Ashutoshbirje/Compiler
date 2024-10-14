#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_ID,    // Variable
    TOKEN_ASSIGN, // =
    TOKEN_AND,   // and
    TOKEN_OR,    // or
    TOKEN_TRUE,  // true
    TOKEN_FALSE, // false
    TOKEN_SEMICOLON, // ;
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    char value[20];
    TokenType type;
} Token;

void tokenize(const char *expr);
extern Token tokens[100]; // Stores tokens from input
extern int token_count;

#endif

