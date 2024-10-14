#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct {
    char name[20];
    int value;  // 1 for true, 0 for false
} Symbol;

void init_symbol_table();
int add_symbol(const char *name);
void set_symbol_value(const char *name, int value);
int get_symbol_value(const char *name);

extern Symbol symbols[100];
extern int symbol_count;

#endif
