#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATION_MEMORY_ERROR (-1)


struct _Tree;
typedef struct _Tree* Position;
typedef struct _Tree {
	int number;
	Position left;
	Position right;
} Tree;

Position make_empty(Position S); //ovo mozes stavit za brisanje na kraju programa
Position make_tree(int x);
Position insert_element(Position S, int num);
int to_insert(Position S);
int main() {
	Tree root = { .number = 0, .left = NULL, .right = NULL };

	return EXIT_SUCCESS;
}
Position make_empty(Position S) {

	if (S != NULL) {
		make_empty(S->left);
		make_empty(S->right);
		free(S);
	}

	return NULL;
}
Position make_tree(Position S, int x) {
	S = (Position)malloc(sizeof(Tree));
	if (!S) {
		perror("Neuspjesna alokacija memorije!\n");
		return NULL;
	}
	S->number = x;
	S->left = NULL;
	S->right = NULL;

	return S;
}
Position insert_element(Position S, int num) {
	
	if (S == NULL)
		make_tree(S, num);
	else if (S->number > num) {
		S->left=insert_element(S, num);
	}
	else if (S->number < num) {
		S->right = insert_element(S, num);
	}

	return S;
}
int to_insert(Position S) {

	int num = 0;
	printf("Unesite element: \n");
	scanf(" %d", &num);
	insert_element(S, num);

	return EXIT_SUCCESS;
}