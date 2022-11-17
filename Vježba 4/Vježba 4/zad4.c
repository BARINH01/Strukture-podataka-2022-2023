#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LINE 1024
#define ERROR_MESSAGE -1

typedef struct _polynom {
	int coefficient;
	int exponent;
	struct _polynom* next;
} polynom;
int read_from_file(polynom** head);
int sort(polynom* head, polynom* current);


int main()
{
	polynom* head = NULL;


	return 0;
}
int read_from_file(polynom** head) {

	FILE* fp = NULL;
	char filename[MAX_STRING] = { 0 };
	char buffer[MAX_LINE] = { 0 };
	char* charPointer = NULL;
	int k = 0;
	int n = 0;
	polynom* currentPolynom = NULL;
	//head = (polynom*) malloc(sizeof(polynom*));


	printf("Unesite ime datoteke iz koje zelite ucitati listu\n");
	scanf(" %s", filename);

	fp = fopen(filename, "r");

	if (!fp) {
		printf("Datoteka se ne moze otvoriti, pokusajte ponovno.\n");
		return ERROR_MESSAGE;
	}

	currentPolynom = (polynom*)malloc(sizeof(head));

	if (!currentPolynom) {

		printf("Greska pri alociranju memorije!\n");
		free(currentPolynom);

		return ERROR_MESSAGE;
	}

	while (!feof(fp)) {

		fgets(buffer, MAX_LINE, fp);
		*charPointer = buffer;

		while (sscanf(buffer, "%d %d %n", &currentPolynom->coefficient, &currentPolynom->exponent, &k) == 2) {

			charPointer += k;

		}
		n++;
		head = realloc(head, n * sizeof(polynom *));
		currentPolynom->coefficient = 0;
		currentPolynom->exponent = 0;
		currentPolynom->next = NULL;
		head[n] = currentPolynom;
	}

	fclose(fp);
	return 0;


}

//int sort(polynom* head, polynom* current)
