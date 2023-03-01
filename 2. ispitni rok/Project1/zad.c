#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 64
#define MAX_LENGTH 1021

#define ERROR_MESSAGE -1

typedef struct _dateP {

	int year;
	int month;
	int date;

} dateP;
typedef struct _hotel {
	char name[MAX_STRING];
	int income;
	struct _dateP* date;
	struct _hotel* next;

} hotel;
//za ocjenu dovoljan(2)
int hotels_read_from_file(hotel* head);
hotel* hotel_create_from_string(char* information);
int hotel_insert_sorted(hotel* head, hotel* toInsert);
int datecmp(dateP* date1, dateP* date2);
void hotels_print(hotel* head);
void hotels_free_ll(hotel* head);
int delete_hotels_after(hotel* head);
float arithmetic_median(hotel* head);
void move_below_average_to_end(hotel* head, float average);

int main() {
	float median_income = 0.0f;
	hotel head = { .name = {0}, .income = 0, .date = NULL, .next = NULL };
	hotels_read_from_file(&head);
	hotels_print(&head);
	median_income = arithmetic_median(&head);
	printf("%f\n", median_income);
	move_below_average_to_end(&head, median_income);
	hotels_print(&head);
	hotels_free_ll(&head);
	return EXIT_SUCCESS;
}


int hotels_read_from_file(hotel* head) {
	FILE* fp = NULL;
	hotel* temp = head;
	char fileName[MAX_LENGTH] = { 0 };
	char buffer[MAX_LENGTH] = { 0 };

	printf("Please enter the filename: \n");
	scanf(" %s", fileName);

	fp = fopen(fileName, "r");

	if (!fp) {
		perror("Can't open file\n");
		return ERROR_MESSAGE;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LENGTH, fp);
		temp = hotel_create_from_string(buffer);
		if (temp) {
			hotel_insert_sorted(head, temp);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
hotel* hotel_create_from_string(char* information) {
	hotel* newHotel = NULL;
	dateP* newDate = NULL;
	char* info = information;
	int b = 0;

	newHotel = (hotel*)malloc(sizeof(hotel));
	newDate = (dateP*)malloc(sizeof(dateP));

	if (!newHotel || !newDate) {
		perror("Can't allocate memory!\n");
		free(newHotel);
		free(newDate);
		return NULL;
	}
	newHotel->date = newDate;

	if (sscanf(info, " %s %d-%d-%d %d",
		newHotel->name,
		&newHotel->date->year,
		&newHotel->date->month,
		&newHotel->date->date,
		&newHotel->income) == 5
		) {

	}

	return newHotel;
}

int hotel_insert_sorted(hotel* head, hotel* toInsert) {
	hotel* temp = head;
	int value = 0;

	while (temp->next) {
		if (datecmp(temp->next->date, toInsert->date) > 0) {
			break;
		}
		temp = temp->next;
	}
	toInsert->next = temp->next;
	temp->next = toInsert;

	return 0;
}

int datecmp(dateP* date1, dateP* date2) { // returns >0 if date1 is greater, <0 if date2 is greater, and 0 if they are the same
	int result = 0;

	result = date1->year - date2->year;
	if (result) return result;

	result = date1->month - date2->month;
	if (result) return result;

	return date1->date - date2->date;
}

void hotels_print(hotel* head) {
	hotel* temp = head->next;

	while (temp) {

		printf("%s\t %d-%d-%d\t %d\n",
			temp->name,
			temp->date->year,
			temp->date->month,
			temp->date->date,
			temp->income);
		temp = temp->next;
	}
	return;
}
void hotels_free_ll(hotel* head) {
	hotel* temp = head;

	while (temp->next != NULL) {
		delete_hotels_after(temp);
	}
	return;
}
int delete_hotels_after(hotel* head) {
	hotel* toDelete = head;
	hotel* temp = head;

	while (temp->next->next != NULL) {
		temp = temp->next;
	}
	toDelete = temp->next;
	temp->next = toDelete->next;
	free(toDelete->date);
	free(toDelete);


	return EXIT_SUCCESS;
}
float arithmetic_median(hotel* head) {
	int sum = 0, count = 0;
	hotel* temp = head->next;

	while (temp) {
		++count;
		sum += temp->income;
		temp = temp->next;
	}

	return (float)sum / count;
}

void move_below_average_to_end(hotel* head, float average) { // move appropriate hotels to a new list and then append that list to the original one
	hotel head2 = { .name = {0}, .income = 0, .date = NULL, .next = NULL };
	hotel* temp = head;
	hotel* toMove = NULL;
	hotel* newPosition = &head2;

	while (temp->next) {
		if (temp->next->income < average) {
			toMove = temp->next;
			temp->next = temp->next->next;
			toMove->next = NULL;
			newPosition->next = toMove;
			newPosition = newPosition->next;
		}
		else temp = temp->next;
	}
	temp->next = head2.next;

	return;
}