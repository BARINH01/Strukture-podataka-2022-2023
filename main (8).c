#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
}Node;

Node* insert(Node* root, int data) {
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

void replace(Node* root) {
    
    if (root == NULL) 
        return;
        
    int left_sum = 0, right_sum = 0;
    
    if (root->left != NULL) 
        left_sum = root->left->data;
        
    if (root->right != NULL) 
        right_sum = root->right->data;
        
    root->data = left_sum + right_sum;
    replace(root->left);
    replace(root->right);
}

int main(){
    Node* root = NULL;
    
    root = insert(root, 2);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 7);
    
    replace(root);


}