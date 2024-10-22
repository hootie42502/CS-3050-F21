#include "rbTree.c"

int main(){

    char input = '\0';
    int num;

    node *root = NULL;
    root = create_black_node(NULL,0,0);
    root->parent = NULL;

    printf("input: \n");
    scanf("%s", &input);
    if (input == 'X') { return -1; }
    num = atoi(&input);

    root->right = create_black_node(root, 1, num);
    root->right->parent = root;
    printf("Node inserted \n\n");

    int key = 2;
    while(input != 'X') {
        scanf("%s", &input);
        if (input == 'X') { break; }
        num = atoi(&input);
        insert(root->right, root->right, num, key);
        printf("Node inserted \n\n");
        key++;
    }

    print_out(root->right);
    printf("\nHeight: %d", height(root->right));
    printf("\nBlack Height: %d\n", blackHeight(root->right));
    printf("\n2nd Highest Number: %d\n", secondTreeMax(root->right,treeMax(root->right)));

    freeTree(root);

}

