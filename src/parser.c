#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define SCREEN_WIDTH 80  // Define screen width for center alignment
#define MAX_EXPRESSION_LENGTH 100  // Maximum length for bool exp

// Function to create a new value node (T or F)
Node* createValueNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operator = '\0';  // No operator for value node
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new operator node (&, |, ^, ~)
Node* createOperatorNode(char operator, Node* left, Node* right) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operator = operator;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// Recursive function to evaluate the parse tree and store the result at the root
int evaluate(Node* root) {
    if (root == NULL) return 0;

    // If it's a value node (T or F)
    if (root->operator == '\0') return root->value;

    // Recursively evaluate left and right subtrees
    int leftValue = evaluate(root->left);
    int rightValue = (root->right != NULL) ? evaluate(root->right) : 0;

    // Apply the operator and store the result in the root
    switch (root->operator) {
        case '&':
            root->value = leftValue & rightValue;
            break;
        case '|':
            root->value = leftValue | rightValue;
            break;
        case '^':
            root->value = leftValue ^ rightValue;
            break;
        case '~':  // Negation case
            root->value = !leftValue;  // Unary negation
            break;
    }
    return root->value; // Return the result stored in the root
}

// Function to print spaces for centering
void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

// Recursive function to print the parse tree horizontally
void printParseTree(Node* root, int depth, int position) {
    if (root == NULL) return;

    // Print the right subtree first, offset by half the screen width for alignment
    printParseTree(root->right, depth + 1, position + 3);

    // Print current node at the correct position (centered at position)
    printSpaces(position);
    if (root->operator == '\0') {
        printf("%s\n", root->value ? "T" : "F");  // Print T or F
    } else {
        printf("%c (Result: %s)\n", root->operator, root->value ? "T" : "F");
    }

    // Print the left subtree
    printParseTree(root->left, depth + 1, position - 3);
}

// Function to parse user input and build the parse tree
Node* parseExpression(char* expr, int* index) {
    Node* left = NULL;
    while (expr[*index] != '\0') {
        char ch = expr[*index];
        (*index)++;

        if (ch == 'T' || ch == 'F') {
            // Create a value node (T or F)
            int value = (ch == 'T') ? 1 : 0;
            Node* node = createValueNode(value);
            if (left == NULL) {
                left = node;
            } else {
                // If we already have a left operand, create an operator node
                char op = expr[*index - 2];
                Node* right = node;
                left = createOperatorNode(op, left, right);
            }
        } else if (ch == '&' || ch == '|' || ch == '^') {
            // Continue parsing for the right operand
            Node* right = parseExpression(expr, index);
            return createOperatorNode(ch, left, right);
        } else if (ch == '~') {
            // Handle negation (unary operator)
            Node* negatedNode = parseExpression(expr, index);
            return createOperatorNode('~', negatedNode, NULL);
        }
    }
    return left;
}

// Function to read the expression from a file
void readExpressionFromFile(const char* filename, char* expression) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fgets(expression, MAX_EXPRESSION_LENGTH, file);
    fclose(file);
}
