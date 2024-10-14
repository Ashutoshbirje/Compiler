#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper function to create a new parse tree node
ParseNode *create_node(const char *value) {
    ParseNode *node = (ParseNode *)malloc(sizeof(ParseNode));
    strcpy(node->value, value);
    node->left = node->right = NULL;
    return node;
}

int current_token = 0;

ParseNode *parse() {
    printf("Parsing the expression...\n");

    if (current_token < token_count) {
        ParseNode *node = create_node(tokens[current_token].value);
        current_token++;
        return node;  // Return the root of the tree (for now, a single node)
    }
    return NULL;
}

void print_parse_tree(ParseNode *root) {
    if (root == NULL) return;

    printf("Node: %s\n", root->value);
    print_parse_tree(root->left);
    print_parse_tree(root->right);
}
