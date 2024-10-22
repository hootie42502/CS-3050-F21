#include "rbTree.h"
#include <stdio.h>
#include <stdlib.h>

#define BLACK 1
#define RED 0

node* create_red_node(node *parent, int key, int value) {
    node* newNode = (node*) malloc(sizeof(node));

    newNode->value = value;
    newNode->key = key;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
   
    return newNode;

}

node* create_black_node(node *parent,int key, int value) {
    node* newNode = (node*) malloc(sizeof(node));

    newNode->value = value;
    newNode->key = key;
    newNode->color = BLACK;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;

    return newNode;
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    } else if (b > a) {
        return b;
    } else {
        return -1;
    }
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    } else if (b < a) {
        return b;
    } else {
        return -1;
    }
}

int height (node* n) {
    if (n == NULL) {
        return 0;
    } else if (n != NULL) {
        return 1 + max(height(n->right), height(n->left));
    }
        return -1;
}

node* getGrandParent(node* n) {
    return n->parent->parent;
}

node* getRightUncle(node* n) {
    return (getGrandParent(n))->right;
}

node* getLeftUncle(node *n) {
    return (getGrandParent(n))->left;
}

void rotateRight(node *root) {
    node *temp = root->parent;
    int ins = 0; //if this remains 0, insert on left, otherwise insert on right
    
    if(temp->right == root) {
        ins = 1; //insert on right

        if(root == NULL || root->left == NULL) {
            printf("Error\n");
            return;
        }

        node *x = root->left;
        node *y = x->right;
        x->right = root;
        root->left = y;
        if(y != NULL) {
            y->parent = root;
        }
        x->parent = temp;
        root->parent = x;

        if(ins == 0) {
            temp->left = x;
        } else {
            temp->right = x;
        }
    }



    return;
}

void rotateLeft(node *root) {
    node *temp = root->parent;
    int ins = 0; //if this remains 0, insert on left, otherwise insert on right

    if(temp->right == root) {
        ins = 1; //insert on right
         if(root == NULL || root->right == NULL) {
              printf("Error\n");
              return;
          }

          node *y = root->right;
          node *x = y->left;
          y->left = root;
          root->right = x;
          y->parent = temp;
          root->parent = y;
          if(x != NULL) {
              x->parent = root;
          }

         if(ins == 0) {
             temp->left = y;
         } else {
            temp->right = y;
        }
    }

    return;
}

void case1(node* root,int rotate) {
    root->parent->parent->color = RED;
    root->parent->color = BLACK;
    if (rotate == 0) {
        rotateRight(getGrandParent(root));
    } else if (rotate == 1) {
        rotateLeft(getGrandParent(root));
    } else {
        printf("Error\n");
    }
}

void case2(node *root, int rotate) {
    node *p = root->parent;
    if(rotate == 0) {
        rotateRight(root->parent);
    } else if (rotate == 1) {
        rotateLeft(root->parent);
    } else {
        printf("Error\n");
        return;
    }

    if(rotate == 0) {
        case1(p, 1);
    } else if (rotate == 1) {
        case1(p, 0);
    }
    return;
}

void case3 (node *n,node *root)
{
    if(n == NULL) {
        return;
    } else if ( n->parent == NULL ) {
        printf("Error\n");
        return;
    } else if (getGrandParent(n) == NULL) { //color root black
        n->color = BLACK;
        return;
    } else {
        if(n->parent->color == BLACK) {
            return;
        }
        node* gp = getGrandParent(n);
        gp->right->color = BLACK;
        gp->left->color = BLACK;
        gp->color = RED;
        return;
    }
    return;
}

void fix(node *n,node *root) {
    if (n == NULL) {
        printf("Error fix called on NULL\n");
        return;
    }
    else if (root == n) {
        root->color = BLACK;
        return;
    }
    else if (n->parent == root) {
        root->color = BLACK;
        return;
    }
    else {
        node* gp = getGrandParent(n);
        if(gp == NULL){
            return;
        }
        node* rightUncle = getRightUncle(n);
        node* leftUncle = getLeftUncle(n);
        if(n->color == RED && n->parent->color == RED) { //violation
            if( (rightUncle != NULL && leftUncle != NULL ) && rightUncle->color == RED && leftUncle->color == RED) {
                case3(n, root);
                fix(gp, root);
                return;
            } else {
                if( rightUncle == NULL || rightUncle != n->parent ) { //uncle is right branch, father is left branch
                    if (n->parent->left == n) { //left child on left branch
                        case1(n, 0);
                        return;
                    } else { //right child on left branch
                        case2(n, 1);
                        return;
                    }
                } else { //uncle is left branch, father is right branch
                    if(n->parent->right == n) { //right child on right branch
                        case1(n,1);
                        return;
                    } else { //left child on right branch
                        case2(n,0);
                        return;
                    }
                }
            }
        }
    }
}

void insert(node *n, node* root, int val, int key) {
    if(n == NULL) {
        printf("Error NULL\n");
        return ;
    } else {
        if(val <= n->value ) {
            if(n->left == NULL){
                printf("Insert value %d on the left of : %d\n", val, n->value);
                n->left = create_red_node(n, key, val);
                //tree_print(root);
                fix(n->left, root);
            } else {
                printf("Inserted value %d is lower than : %d, going left\n", val, n->value);
                insert(n->left, root, val, key);
            }
        } else if (val > n->value) {
            if(n->right == NULL) {
                printf("Inserting value %d on the left of node : %d\n", val, n->value);
                n->right = create_red_node(n, key, val);
                //tree_print(root);

                fix(n->right, root);
               
            } else {
                printf("Value %d is bigger than : %d, going right\n", val, n->value);
                insert(n->right, root, val, key);
            }
        }
    }
    return;
}

void print_out(node *root){
    if(root != NULL) {
        printf("%d ", root->value);
        if (root->color == BLACK) {
            printf("black\n");
        } else {
            printf("red\n");
        }
        print_out(root->left);
        if (root->right != NULL) {
            print_out(root->right);
        }
    }
}

int treeMax(node *root) {
    if(root != NULL) {
        if (root->right != NULL) {
           return treeMax(root->right);
        } else {
            return root->value;
        }
    } else {
        return -1;
    }
}

int secondTreeMax(node *root, int greatest){
    int x = 0;
    if(root->left == NULL && root->right == NULL){
        if(root->value != greatest){
            x = root->value;
        }
    } else if(root->left != NULL && root->right != NULL) {
        x = max(secondTreeMax(root->left,greatest), secondTreeMax(root->right,greatest));
        if(x < root->value && root->value != greatest) //the second highest number and the highest number have the same parent
        {
            x = root->value;
        }
    } else if(root->left != NULL && root->right == NULL) {
        if(root->left->value != greatest && root->value != greatest) {
            x = max(root->left->value, root->value);
        } else {
            x = min(root->left->value, root->value);
        }
    } else if(root->right != NULL && root->left == NULL) {
        if(root->right->value != greatest && root->value != greatest) {
            x = max(root->right->value, root->value);
        } else {
            x = min(root->right->value, root->value);
        }
    }
    return x;

}

int blackHeight(node* root) {
    if (root == NULL) {
        return 1;
    }

    int leftBlackHeight = blackHeight(root->left);
    if (leftBlackHeight == 0) {
        return leftBlackHeight;
    }

    int rightBlackHeight = blackHeight(root->right);
    if (rightBlackHeight == 0) {
        return rightBlackHeight;
    }
    if (leftBlackHeight != rightBlackHeight) {
        return 0;
    } else {
        return leftBlackHeight + root->color;
    }
}

void freeNode(node* freedomNode){
    if (freedomNode == NULL) return;
    free(freedomNode);
    freedomNode = NULL;
    return;
}

void freeTree(node* root){
    if (root == NULL) return;
    else
    {
        freeTree(root->left);
        freeTree(root->right);
        freeNode(root);
        return;
    }
}

