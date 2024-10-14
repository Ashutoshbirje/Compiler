#ifndef PARSER_H
#define PARSER_H

typedef struct ParseNode {
    char value[20];  // Node value (e.g., token or expression)
    struct ParseNode *left;
    struct ParseNode *right;
} ParseNode;

ParseNode *create_node(const char *value);  // Helper to create a new node
ParseNode *parse();  // Returns the root of the parse tree
void print_parse_tree(ParseNode *root);  // Print the parse tree

#endif
