#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ERROR_MESSAGE -1
#define MAX_STRING 64
#define MAX_LINE 1024

typedef struct _element {
	double number;
	struct _element* next;
} element;


int read_from_file(element* head);
int operation(char operator, element *head);
element* create_element(double number);
int delete_first(element* head);
int push(element* head, double tempNum);
int pop(element* head);
int print_postfix_result(element *head);

int main() {

	element head = { .number = 0, .next = NULL };

    read_from_file(&head);

	return EXIT_SUCCESS;
}

int read_from_file(element *head) {

	FILE* fp = NULL;
	char buffer[MAX_STRING] = { 0 };
	char* pbuffer = buffer;
	char fileName[MAX_STRING] = { 0 };
	char operator = '0';
	int b = 0;
	element* temp = head;
	double tempNumber = 0;
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
        while(strlen(pbuffer) > 0){
	    	if (sscanf(pbuffer, " %lf %n", &tempNumber, &b) == 1) {
		    	push(head,tempNumber);
		    }

		    else if (sscanf(pbuffer, " %c %n", &operator, &b) == 1) {
                operation(operator, head);
		    }

		    *pbuffer += b;
        }
	}

    print_postfix_result(head);



}

int operation(char operator, element *head) {
	double num1 = 0, num2 = 0, result = 0;

	if (!head->next || !head->next->next) {
		printf("Nema postfixa unlucky"); 
		return ERROR_MESSAGE;
	}

	num1 = pop(head);
	num2 = pop(head);

	switch (operator) {
	case '+':
		result = num2 + num1;
		break;
	case '-':
		result = num2 - num1;
		break;
	case '*':
		result = num2 * num1;
		break;
	case '/':
		result = num2 / num1;
		break;
	default:
		printf("Nema postfixa unlucky");
		return ERROR_MESSAGE;
	}

	push(head, result);

	return EXIT_SUCCESS;
}

element* create_element(double number) {
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

int push(element* head, double tempNum) {

	element* newElement = NULL;
	newElement=create_element(tempNum);

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

int delete_all(element* head) {
	element* temp = NULL;

	temp = head->next;

	if (!temp) {
		printf("Lista je prazna!\n");
		return EXIT_SUCCESS;
	}

	head->next = temp->next;
	free(temp);

    delete_all(&head);

	return 0;
}


int pop(element* head) {
	int toPop = 0;

	if (!head->next) {

		printf("Postfix izraz netocno napisan!\n");
		return EXIT_FAILURE;
	}
	toPop = head->next->number;
	delete_first(head);

	return toPop;
}

int print_postfix_result(element *head){
    	
    if (!head->next || head->next->next) {
		printf("Postfix netocno uzet unlucky ");
		return ERROR_MESSAGE;
	}

	printf("Rezultat postfixa je: %.2lf", head->next->number); 

	return EXIT_SUCCESS;
}