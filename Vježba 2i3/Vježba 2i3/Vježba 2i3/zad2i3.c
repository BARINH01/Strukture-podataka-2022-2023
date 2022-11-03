#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING (64)
#define MAX_LINE (1024)
#define ERROR_MESSAGE (-1)

struct person;

typedef struct person {
    char name[MAX_STRING];
    char surname[MAX_STRING];
    int byear;
    struct person* next;
}person;


void insert_beggining(person** currentPerson);
void insert_in_struct(person* forInsert);
void printList(person* forPrint);
void insert_end(person** currentPerson);
person* find_person(person** head, char* input);
person* find_before(person** head, char* input);
void delete_person(person** head);
int menu();
//3.zad
void insert_in_list(person* currentPerson);
void sort(person** head);
person* tortoise_and_hare(person* head);
person* merge(person* left, person* right);
person* merge_sort(person* head);
person* import_list_and_sort(person* forImport, char* fileName);



int main() {

    person* head = NULL;
    int choice = 0;
    char surname[MAX_STRING];
    char fileName[MAX_STRING] = { 0 };


    while (1) {
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
            find_person(&head, surname);
            break;

        case 5:
            printf("Unesite prezime osobe koju zelite izbrisati: \n");
            delete_person(&head);
            break;

        case 6:
            printf("Unesite prezime osobe iza koje zelite unjeti novu osobu\n");
            scanf(" %s", surname);
            insert_in_list(find_person(&head, surname));
            break;

        case 7:
            printf("Unesite prezime osobe prije koje zelite unjeti novu osobu\n");
            scanf(" %s", surname);
            insert_in_list(find_before(&head, surname));
            break;

        case 8:
            head = merge_sort(head);
            break;

        default:
            printf("Pogreska!\n");
        }
    }


    return 0;
}


void insert_beggining(person** head) {

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
    return;

}

void printList(person* forPrint) {

    if (forPrint == NULL) {
        printf("Lista je prazna!\n");
        return;
    }

    while (forPrint != NULL) {
        printf("%s %s %d\n", forPrint->name, forPrint->surname, forPrint->byear);
        forPrint = forPrint->next;

    }
}

void insert_end(person** head) {
    person* newPerson = NULL; //123
    person* temp = *head;

    newPerson = malloc(sizeof(person));
    insert_in_struct(newPerson);

    if (*head == NULL) {
        *head = newPerson;
        newPerson->next = NULL;
        return;
    }

    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
    }

    temp->next = newPerson;
    newPerson->next = NULL;


}

person* find_person(person** head, char* input) {
    person* temp = *head;

    while (temp != NULL) {
        if (strcmp(input, temp->surname) == 0) {
            printf("%s %s %d\n", temp->name, temp->surname, temp->byear);
            return temp;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        return NULL;
    }

    return NULL;
}

person* find_before(person** head, char* input) {
    person* temp = *head;

    while (temp != NULL) {
        if (strcmp(input, temp->next->surname) == 0) {
            printf("%s %s %d\n", temp->name, temp->surname, temp->byear);
            return temp;
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        return NULL;
    }
}

void delete_person(person** head) {
    person* current = *head;
    person* temp = NULL;
    char input[MAX_STRING] = { 0 };

    scanf(" %s", input);

    if (strcmp((*head)->surname, input) == 0) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    while (current->next != NULL) {
        if (strcmp(current->next->surname, input) == 0) {
            temp = current->next;
            current->next = current->next->next;
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
        "5 - Brisanje elementa iz liste\n"
        "6 - Unošenje elementa poslje\n"
        "7 - Unošenje elementa prije\n"
        "8 - Sortiraj listu po prezimenu\n");

    scanf("%d", &choice);
    if (choice >= 0 && choice <= 9)
        return choice;
    else
        printf("Pogresan unos ponudene opcije, pokusajte ponovno.\n");
    menu();

}

void insert_in_list(person* currentPerson) {
    person* newPerson = NULL;

    if (currentPerson == NULL) {
        printf("osoba ne postoji u listi! unlucky\n");
        return;
    }
    printf("Osoba pronadena\n");
    newPerson = malloc(sizeof(person));

    if (!newPerson) {
        printf("memorija neuspješno alocirana\n");
        return;
    }

    insert_in_struct(newPerson);
    newPerson->next = currentPerson->next;
    currentPerson->next = newPerson;

    printf("uspio sam unjet\n");
    return;
}

person* tortoise_and_hare(person* head) {
    person* tortoise = head;
    person* hare = head->next;

    while (hare != NULL && hare->next != NULL) {
        tortoise = tortoise->next;
        hare = hare->next->next;
    }
    return tortoise;
}

person* merge(person* left, person* right) {
    person* falseHead = malloc(sizeof(person));
    person* currentPerson = falseHead;

    while (left != NULL && right != NULL) {
        if (strcmp(left->surname, right->surname) <= 0) {
            currentPerson->next = left;
            left = left->next;
            currentPerson = currentPerson->next;
        }
        else if ((strcmp(left->surname, right->surname) > 0)) {
            currentPerson->next = right;
            right = right->next;
            currentPerson = currentPerson->next;
        }
    }
    while (left != NULL) {
        currentPerson->next = left;
        left = left->next;
        currentPerson = currentPerson->next;
    }

    while (right != NULL) {
        currentPerson->next = right;
        right = right->next;
        currentPerson = currentPerson->next;
    }

    return falseHead->next;
}

person* merge_sort(person* head) {

    if (head->next == NULL) {
        return head;
    }

    person* mid = tortoise_and_hare(head);
    person* startRightSide = mid->next;

    mid->next = NULL;

    person* left = merge_sort(head);
    person* right = merge_sort(startRightSide);
    person* newHead = merge(left, right);

    return newHead;


}
person* import_list_and_sort(person* forImport, char* fileName) {

    FILE* fp = NULL;
    char buffer[MAX_LINE] = { 0 };
    char name[MAX_STRING] = { 0 };
    char surname[MAX_STRING] = { 0 };
    int byear = 0;
    person* newPerson = NULL;

    fp = fopen(fileName, "r");

    if (!fp) {
        printf("Datoteka se ne moze otvoriti.\n");
        return NULL;
    }
    
    while (!feof(fp)) {
        fgets(buffer, MAX_LINE, fp);
        if(sscanf(buffer, " %s %s %d", name, surname, &byear) == 3)

    }
   

}
