#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "symbol_table.h"

void parse() {
    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == TOKEN_ID && tokens[i + 1].type == TOKEN_ASSIGN) {
            set_symbol_value(tokens[i].value, tokens[i + 2].type == TOKEN_TRUE ? 1 : 0);
        }
    }
}
