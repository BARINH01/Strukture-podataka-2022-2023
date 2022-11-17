#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ERROR_MESSAGE -1
#define MAX_STRING 64
#define MAX_LINE 1024

typedef struct _element {
	int number;
	struct _element* next;
} element;
int read_from_file(element* head);
element* create_element(int number);
int delete_first(element* head);
int push(element* head, int tempNum);
int main() {

	element head = { .number = 0, .next = NULL };




	return EXIT_SUCCESS;
}
int read_from_file(element* head) {

	FILE* fp = NULL;
	char buffer[MAX_STRING] = { 0 };
	char* pbuffer = buffer;
	char fileName[MAX_STRING] = { 0 };
	char operator = '0';
	int t = 0;
	element* temp = head;
	int tempNumber = 0;
	int check = 0;

	printf("Unesite ime datoteke (s datotecnim nastavkom)\n");
	scanf(" %s", fileName);

	fp = fopen(fileName, "r");

	if (!fp) {

		perror("Datoteka se ne moze otvoriti! Pokusajte ponovno!\n");
		return ERROR_MESSAGE;

	}
	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (sscanf(pbuffer, "%d %n", &tempNumber, &t) == 1) {

			pbuffer += t;
			temp = push(head, tempNumber);
		}
		else if (sscanf(pbuffer, "%c %n", &operator, &t) == 1) {
			pbuffer += t;
			//operation(head, operator);
		}



	}

}
element* create_element(int number) {
	element* newElement = NULL;

	newElement = (element*)malloc(sizeof(element));

	if (!newElement) {
		printf("Alokacija memorije neuspjesna!\n");
		free(newElement);
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}
int push(element* head, int tempNum) {

	element* newElement = NULL;
	create_element(newElement);

	if (!newElement) {
		printf("Greska u izradi novog elementa!\n");
		return EXIT_FAILURE;
	}

	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;;
}
int delete_first(element* head) {
	element* temp = NULL;

	temp = head->next;

	if (!temp) {
		printf("Lista je prazna!\n");
		return EXIT_SUCCESS;
	}

	head->next = temp->next;
	free(temp);

	return 0;
}
int push(element* head, int tempNum) {
	int toPop = 0;

	if (!head->next) {

		printf("Postfix izraz netocno napisan!\n");
		return EXIT_FAILURE;
	}
	toPop = head->next->number;
	delete_first(head);

	return toPop;
}