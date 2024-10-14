#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_SYMBOLS 100

typedef struct {
    char name[20];
    int value;
} Symbol;

void init_symbol_table();
int add_symbol(const char *name);
int get_symbol_value(const char *name);
void set_symbol_value(const char *name, int value);

// Extern declarations to be used in other files
extern Symbol symbols[MAX_SYMBOLS];
extern int symbol_count;

#endif
