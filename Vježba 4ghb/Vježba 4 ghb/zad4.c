#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct _Polynom;
typedef struct _Polynom* Position;
typedef struct _Polynom
{
	int coefficient;
	int exponent;
	Position next;

}Polynom;

int read_from_file(Position head1, Position head2, char* fileName);
int read(Position head, char* string, int n);
int insert_sorted(Position head, int k, int e);
Position create_element(int k, int e);
int print_polynom(Position first);
int sum_polynom(Position first1, Position first2, Position headSum);
int clear_zeros(Position head);
int multiply_polynom(Position first1, Position first2, Position headProdukt);
int delete_after(Position previous);
int delete_all(Position head);

int main(int argc, char** argv)
{
	char fileName[MAX_LINE] = { 0 };
	Polynom head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynom head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynom headSum = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynom headProdukt = { .coefficient = 0, .exponent = 0, .next = NULL };

	Position p1 = &head1;
	Position p2 = &head2;
	Position pS = &headSum;
	Position pP = &headProdukt;

	printf("Unesite ime datoteke: \n");
	scanf(" %s", fileName);


	if (read_from_file(p1, p2, fileName) == EXIT_SUCCESS)
	{
		printf("Prvi polinom:\t");
		print_polynom(p1->next);

		printf("\n\nDrugi polinom:\t");
		print_polynom(p2->next);

		sum_polynom(p1->next, p2->next, pS);
		printf("\n\nZbroj polinoma:\t");
		print_polynom(pS->next);

		multiply_polynom(p1->next, p2->next, pP);
		printf("\n\nProdukt polinoma:   ");
		print_polynom(pP->next);
	}

	delete_all(p1);
	delete_all(p2);
	delete_all(pS);
	delete_all(pP);

	printf("\n");

	return EXIT_SUCCESS;
}

int read_from_file(Position head1, Position head2, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	char string[MAX_LINE];

	fgets(string, MAX_LINE, fp);
	read(head1, string, strlen(string));
	fgets(string, MAX_LINE , fp);
	read(head2, string, strlen(string));

	fclose(fp);


	return EXIT_SUCCESS;
}

int read(Position head, char* string, int n)
{
	string[n] = 0;
	int k = 0, e = 0;
	int t = 0;
	char* sstring = string;
	int check = 0;

	while (strlen(sstring) > 0)
	{

		t = 0;

		check = sscanf(sstring, " %d %d %n ", &k, &e, &t);
		if (check != 2)
			break;
		sstring += t;

		insert_sorted(head, k, e);

	}

	return EXIT_SUCCESS;

}


int insert_sorted(Position head, int k, int e)
{
	Position temp = head;
	Position newEl = NULL;

	while (temp->next != NULL && temp->next->exponent > e)
		temp = temp->next;

	if (temp->next != NULL && temp->next->exponent == e)
		temp->next->coefficient += k;

	else
	{
		newEl = create_element(k, e);
		newEl->next = temp->next;
		temp->next = newEl;
	}
	return EXIT_SUCCESS;
}

Position create_element(int k, int e)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(Polynom));
	if (!newEl)
	{
		perror("Neuspijesno alociranje memorije!\n");
		return NULL;
	}

	newEl->exponent = e;
	newEl->coefficient = k;


	return newEl;
}

int print_polynom(Position first)
{
	Position temp = first;


	while (temp)
	{
		if (temp->exponent == 0)
			printf(" %d ", temp->coefficient);
		else if (temp->exponent == 1 && temp->coefficient == 1)
			printf(" X ");
		else if (temp->exponent == 1)
			printf(" %dX ", temp->coefficient);
		else if (temp->coefficient == 1)
			printf(" X%d ", temp->exponent);
		else
			printf(" %dX^%d ", temp->coefficient, temp->exponent);

		if (temp->next != NULL)
			printf("+");

		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int sum_polynom(Position first1, Position first2, Position headSum)
{
	Position temp1 = first1;
	Position temp2 = first2;

	while (temp1)
	{
		insert_sorted(headSum, temp1->coefficient, temp1->exponent);
		temp1 = temp1->next;
	}
	while (temp2)
	{
		insert_sorted(headSum, temp2->coefficient, temp2->exponent);
		temp2 = temp2->next;
	}

	clear_zeros(headSum);

	return EXIT_SUCCESS;

}

int multiply_polynom(Position first1, Position first2, Position headProdukt)
{
	Position temp1 = first1;
	Position temp2 = first2;

	while (temp1)
	{
		temp2 = first2;

		while (temp2)
		{
			insert_sorted(headProdukt, temp1->coefficient * temp2->coefficient, temp1->exponent + temp2->exponent);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}

	clear_zeros(headProdukt);

	return EXIT_SUCCESS;

}

int clear_zeros(Position head)
{
	Position p = head;
	Position temp;

	while (p->next)
	{
		if (!p->next->coefficient)
		{
			temp = p->next;
			p->next = p->next->next;
			free(temp);
		}
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int delete_after(Position previous)
{
	Position temp = NULL;

	temp = previous->next;
	previous->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int delete_all(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		delete_after(temp);
	}

	return EXIT_SUCCESS;
}