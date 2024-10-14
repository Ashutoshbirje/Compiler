#include "parser.h"  // Must be included to access Node
#include "tac.h"
#include <stdio.h>
#include <string.h>

// Three-address code (TAC) storage
TAC tac_list[MAX_TAC];
int tac_count = 0;
int temp_var_count = 0;

// Helper function to get node value as a string
const char* get_node_value(Node* node) {
    static char buffer[20];
    
    if (node->operator != '\0') {  // If the node has an operator
        snprintf(buffer, sizeof(buffer), "%c", node->operator);
    } else {  // If the node holds a boolean value
        snprintf(buffer, sizeof(buffer), "%d", node->value);
    }
    return buffer;
}

// Check if a character is a valid operator
int is_operator(char operator) {
    return (operator == '&' || operator == '|' || operator == '^');
}

// Function to generate three-address code from the parse tree
void generate_three_address_code(Node* root) {
    if (!root) return;

    generate_three_address_code(root->left);
    generate_three_address_code(root->right);

    if (root->left && root->right && is_operator(root->operator)) {
        snprintf(tac_list[tac_count].op, sizeof(tac_list[tac_count].op), "%c", root->operator);
        snprintf(tac_list[tac_count].arg1, sizeof(tac_list[tac_count].arg1), "%s", get_node_value(root->left));
        snprintf(tac_list[tac_count].arg2, sizeof(tac_list[tac_count].arg2), "%s", get_node_value(root->right));
        snprintf(tac_list[tac_count].result, sizeof(tac_list[tac_count].result), "t%d", temp_var_count);

        printf("t%d = %s %c %s\n", temp_var_count, 
               get_node_value(root->left), 
               root->operator, 
               get_node_value(root->right));

        // Update the current node to represent the temporary result
        root->operator = '\0';  // Clear the operator
        root->value = temp_var_count;  // Store the temp variable number

        temp_var_count++;
        tac_count++;
    }
}

// Generate low-level code from the TAC
void generate_low_level_code() {
    printf("\nLow-Level Code:\n");
    for (int i = 0; i < tac_count; i++) {
        if (strcmp(tac_list[i].op, "&") == 0) {
            printf("MOV R0, %s\n", tac_list[i].arg1);
            printf("AND R0, %s\n", tac_list[i].arg2);
            printf("MOV %s, R0\n", tac_list[i].result);
        } else if (strcmp(tac_list[i].op, "|") == 0) {
            printf("MOV R0, %s\n", tac_list[i].arg1);
            printf("OR R0, %s\n", tac_list[i].arg2);
            printf("MOV %s, R0\n", tac_list[i].result);
        } else if (strcmp(tac_list[i].op, "^") == 0) {
            printf("MOV R0, %s\n", tac_list[i].arg1);
            printf("XOR R0, %s\n", tac_list[i].arg2);
            printf("MOV %s, R0\n", tac_list[i].result);
        }
    }
}

// Print the generated TAC for debugging
void print_TAC() {
    printf("\nGenerated Three-Address Code:\n");
    for (int i = 0; i < tac_count; i++) {
        printf("%s %s, %s, %s\n", 
               tac_list[i].op, 
               tac_list[i].arg1, 
               tac_list[i].arg2, 
               tac_list[i].result);
    }
}
