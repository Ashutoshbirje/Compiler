#include <string.h>
#include "symbol_table.h"

Symbol symbols[100];
int symbol_count = 0;

void init_symbol_table() {
    symbol_count = 0;
}

int add_symbol(const char *name) {
    strcpy(symbols[symbol_count].name, name);
    symbols[symbol_count].value = 0;
    return symbol_count++;
}

void set_symbol_value(const char *name, int value) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i].name, name) == 0) {
            symbols[i].value = value;
            return;
        }
    }
}

int get_symbol_value(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i].name, name) == 0) {
            return symbols[i].value;
        }
    }
    return -1;
}
