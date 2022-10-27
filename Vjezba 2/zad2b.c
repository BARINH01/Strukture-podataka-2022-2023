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

void insert_first(person *head);
void insert_beggining(person** currentPerson);
void insert_in_struct(person* forInsert);
void printList(person* forPrint);
void insert_end(person** currentPerson);
person* find_person(person** inputStruct, char *input);
person* find_before(person* inputStruct, char input);
void delete_person(person** head);
int menu();

int main() {

    person *head = NULL;
    int choice = 0;
    char surname[MAX_STRING];
    
    //head=malloc(sizeof(person));
    //insert_first(head);
    
    while(1){
    choice = menu();

        switch (choice) {

        case 0:
            return 0;
        case 1:
            insert_beggining(&head);
            break;
        case 2:
            printList(head);
            break;
        case 3:
            insert_end(&head);
            break;

        case 4:
            printf("Unesite prezime trazene osobe: \n");
            scanf(" %s", surname);
            find_person(&head,surname);
            break;

        case 5:
            printf("Unesite prezime osobe koju zelite izbrisati: \n");
            delete_person(&head);
            break;

        default:
            printf("Pogreska!\n");
        }
    }


	return 0;
}

void insert_first(person *head){

    insert_in_struct(head);
    
    head->next=NULL;
    return;
}

void insert_beggining(person ** head) {

    person* newPerson = NULL;

    newPerson = malloc(sizeof(person));

    if (!newPerson) {
        printf("Memorija neuspješno alocirana!\n");
        free(newPerson);
        return;
    }

    insert_in_struct(newPerson);
    newPerson->next = *head;
    *head = newPerson;
    return;
}

void insert_in_struct(person* forInsert) {

    printf("Unesi ime nove osobe: \n");
    scanf(" %s", forInsert->name);

    printf("Unesi prezime nove osobe:\n");
    scanf(" %s", forInsert->surname);

    printf("Unesi godiste nove osobe:\n");
    scanf("%d", &forInsert->byear);

}

void printList(person* forPrint) {
    //person* temp = forPrint;

    if (forPrint == NULL) {
        printf("Lista je prazna!\n");
        return;
    }

    while (forPrint != NULL) {
        printf("%s %s %d\n", forPrint->name, forPrint->surname, forPrint->byear);
        forPrint = forPrint->next;
     
    }
    //free(temp);
}



void insert_end(person **head) {
    person *newPerson = NULL; //123
    person *temp=*head;

    newPerson=malloc(sizeof(person));
    //insert_in_struct(newNode);
    
    if(*head==NULL){
        insert_in_struct(newPerson);
        *head=newPerson;
        newPerson->next=NULL;

        return;
    }
    
    else{
        insert_in_struct(newPerson);
        
        while(temp->next!=NULL){
            temp=temp->next;
        }

    }

    temp->next=newPerson;
    newPerson->next=NULL;

    
}


person* find_person(person** head, char *input) {
    person* temp = *head;

    while (temp != NULL) {
        if (strcmp(input, temp->surname) == 0) {
            printf("%s %s %d\n",temp->name,temp->surname,temp->byear);
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


person* find_before(person* inputStruct,char input) {
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

void delete_person(person** head) {
    person *current = *head;
    person *temp=NULL;
    char input [MAX_STRING] = {0};
    
    scanf(" %s", input);
    
    if(strcmp((*head)->surname,input)==0){
          temp = *head;
          *head = (*head)->next;
          free(temp);
          return;
    }
    
    while(current->next!=NULL){
        if(strcmp(current->next->surname,input)==0){
            temp=current->next;
            current->next=current->next->next;
            free(temp);
            return;
            
        }
    }
}


int menu() {
    int choice = 0;

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