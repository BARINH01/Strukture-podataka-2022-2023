#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
}Node;

Node* insert( Node* root, int data) {
    if (root == NULL) {
        
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->left = root->right = NULL;
    } 
    
    else if (data <= root->data) {
        root->left = insert(root->left, data);
    } 
    
    else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

void inorder_to_file(Node* root) {
    if (root == NULL) 
    return;
    
    inorder_to_file(root->left);
    
    FILE* file = fopen("tree_inorder.txt", "a");
    
    fprintf(file, "%d ", root->data);
    fclose(file);
    
    inorder_to_file(root->right);
}

int main() {
    Node* root = NULL;
    srand(time(0));
    
    for (int i = 0; i < 10; i++) {
        int random_num = rand() % 81 + 10;
        root = insert(root, random_num);
    }

    inorder_to_file(root);
    return 0;
}
