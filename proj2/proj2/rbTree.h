#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree node;
struct tree{
    int value;
    int key;
    char color;
    struct tree *left;
    struct tree *right;
    struct tree* parent;
};

node* create_red_node(node *parent, int key, int value);

node* create_black_node(node *parent, int key, int value);

void rotateRight(node *root);

void rotateLeft(node *root);

void fix(node *n,node *root);

void print_tree(node *tree);

void insert(node* n, node* root, int val, int key);

int secondTreeMax(node *root, int greatest);

int blackHeight(node* root);

void free_node(node* freedomNode);

void free_tree(node* root);


