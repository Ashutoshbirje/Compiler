#ifndef TAC_H
#define TAC_H

#include "parser.h"  // Include the definition of Node

// Structure to store three-address code (TAC)
typedef struct {
    char op[10];     // Operator
    char arg1[20];   // First argument
    char arg2[20];   // Second argument
    char result[20]; // Result
} TAC;

// Maximum number of TAC instructions
#define MAX_TAC 100

// External declarations for TAC storage and counters
extern TAC tac_list[MAX_TAC];
extern int tac_count;

// Function declarations
void generate_three_address_code(Node *root);
void generate_low_level_code();
void print_TAC();

#endif  // TAC_H
