#ifndef PARSER_H
#define PARSER_H

// Structure for a node in the parse tree
typedef struct Node {
    char operator;      // Operator ('&', '|', '^') or '\0' for boolean value
    int value;          // Boolean value (1 for 'T', 0 for 'F')
    struct Node* left;  // Left child
    struct Node* right; // Right child
} Node;

// Function prototypes
Node* createValueNode(int value);
Node* createOperatorNode(char operator, Node* left, Node* right);
int evaluate(Node* root);
void printParseTree(Node* root, int depth, int position);
Node* parseExpression(char* expr, int* index);
void readExpressionFromFile(const char* filename, char* expression);

#endif  // PARSER_H
