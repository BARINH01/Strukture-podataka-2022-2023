#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_STRING (64)
#define MAX_LINE (1024)
#define ERROR_MESSAGE (-1)


typedef struct _polynom {
    int coefficient;
    int exponent;
    struct _polynom *next;

} polynom;

int read_from_file(polynom **head);
int sorted_input(polynom **head,polynom *currentPolynom);

int main(){

}

int read_from_file(polynom **head){
    FILE *f;
    char fileName[MAX_STRING]={0};
    polynom *currentPolynom=NULL;
    printf("unesi ime datoteke za open");
    scanf(" %s", fileName);

    f=fopen(fileName,"r");

    if(!f){
        printf("file neuspjesno otvoren");
        return ERROR_MESSAGE;
    }

    currentPolynom=malloc(sizeof(polynom));

    if(!currentPolynom){
        printf("malloc ne radi");
        return ERROR_MESSAGE;
    }


}

int sorted_input(polynom **head,polynom *currentPolynom){
    
}