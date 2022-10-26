#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING (64)
#define MAX_LINE (1024)
#define ERROR_MESSAGE (-1)

struct person;

typedef struct person {
	char name[MAX_STRING];
	char surname[MAX_STRING];
	int byear;
	struct person *next;
}person;

void insert_beggining(person* currentPerson);
void insert_in_struct(person* forInsert);
void printList(person* forPrint);
void insert_end(person* currentPerson);
person* find_person(person* inputStruct, char input);
person* find_before(person* inputStruct, char input);
void delete_person(person* inputPerson);
int menu();
int main() {
    person head = {.name = "", .surname = "", .byear = 0, .next = NULL};

    int choice = 0;
    char surname = { 0 };
  
    choice = menu();

    switch (choice) {

    case 0:
        return 0;
    case 1:
        insert_beggining(&head);
        break;
    case 2:
        printList(&head);
        break;
    case 3:
        insert_end(&head);
        break;

    case 4:
        printf("Unesite prezime trazene osobe: \n");
        scanf(" %s", &surname);
        find_person(&head, surname);
        break;

    case 5:
        delete_person(&head);
        break;

    default:
        printf("Pogreska!\n");
    }


	return 0;
}
void insert_beggining(person* currentPerson) {

    person* newPerson = NULL;

    newPerson = malloc(sizeof(person));

    if (!newPerson) {
        printf("Memorija neuspješno alocirana!\n");
        free(newPerson);
        return;
    }

    insert_in_struct(newPerson);

    newPerson->next = currentPerson->next;
    currentPerson->next = newPerson;


    return;
}
void insert_in_struct(person* forInsert) {

    printf("Unesi ime nove osobe: \n");
    scanf(" %s", forInsert->name);

    printf("Unesi prezime nove osobe:\n");
    scanf(" %s", forInsert->surname);

    printf("Unesi godiste nove osobe: \n");
    scanf("%d", &forInsert->byear);

}
void printList(person* forPrint) {
    person* temp = forPrint;

    if (forPrint == NULL) {
        printf("Lista je prazna!\n");
    }

    while (temp != NULL) {
        printf(" %s %s %d", forPrint->name, forPrint->surname, forPrint->byear);
        temp = temp->next;
     
    }
    free(temp);
}
void insert_end(person* currentPerson) {
    person* temp = NULL; //123
    
    temp = (person*)malloc(sizeof(person));

    if (!temp) {
        printf("Neuspjesno alociranje memorije!\n");      
        free(temp);
        return;
    }

    temp = currentPerson; //123

    while (currentPerson != NULL) {

        if (currentPerson->next == NULL) {
            insert_in_struct(temp);
        }
       temp->next = currentPerson->next;
       currentPerson->next = temp;

    }
    //free(temp);
}
person* find_person(person* inputStruct, char input) {
    person* temp = NULL;

    temp =(person*)malloc(sizeof(person));

    if (!temp) {
        printf("Neuspjesna alokacija memorije!\n");
        free(temp);
        return NULL;
    }
    temp = inputStruct; //123

    while (temp != NULL) {
        if (strcmp(input, temp->surname) == 0) {
            return temp;
        }

        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Osoba ne postoji u listi!\n");
        return NULL;
    }
    return NULL;
}
person* find_before(person* inputStruct, char input) {
    person* temp = NULL;
    temp = inputStruct;

    while (temp != NULL) {
        if (strcmp(temp->next->surname, input) == 0)
            return temp;
    }
    if (temp->next == NULL)
        printf("Osoba nije pronadena!\n");

    return NULL;
}

void delete_person(person* inputPerson) {
    person* temp = NULL;
    char lname[MAX_STRING] = { 0 };

    printf("Unesite prezime osobe koju zelite izbrisati iz liste!\n");
    scanf(" %s", lname);

    temp = (person*)malloc(sizeof(person));

    if (!temp) {
        printf("Neuspjesna alokacija memorije!\n");
        free(temp);
        return;
    }
    temp = find_before(inputPerson, *lname); //pokazivac problem

    temp->next = inputPerson->next;
    free(inputPerson);

    return;
}
int menu() {
    int choice = 0;

    while (1) {
        printf("Izbornik:\n"
            "0 - izlaz\n"
            "1 - Unos novog elementa na pocetak liste\n"
            "2 - Ispis liste\n"
            "3 - Unos novog elementa na kraj liste\n"
            "4 - Pronalazak elemnta u listi (po prezimenu)\n"
            "5 - Brisanje elementa iz liste\n");

        scanf("%d", &choice);
        if (choice >= 0 && choice <= 5)
            return choice;
        else
            printf("Pogresan unos ponudene opcije, pokusajte ponovno.\n");
    }
 
}