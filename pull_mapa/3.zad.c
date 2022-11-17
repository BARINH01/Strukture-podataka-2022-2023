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
    polynom **heads;
    read_from_file(&heads);
}

int read_from_file(polynom **heads){
    FILE *f;
    int n=0,m=0;
    char fileName[MAX_STRING],buffer[MAX_STRING],*stringPointer=buffer;
    polynom *currentPolynom=NULL;
    printf("unesi ime datoteke za open\n");
    scanf(" %s", fileName);

    f=fopen(fileName,"r");

    if(!f){
        printf("file neuspjesno otvoren");
        return NULL;
    }

    currentPolynom=malloc(sizeof(polynom));

    if(!currentPolynom){
        printf("malloc ne radi");
        return NULL;
    }
    *heads=malloc(n*sizeof(polynom*));
    while(!feof(f)){

        fgets(buffer,MAX_LINE,f);
        *heads[n]=*currentPolynom;

        printf("usao sam u while\n");

        if(sscanf(buffer," %d %d %n",&currentPolynom->coefficient,&currentPolynom->exponent,&m)==2){
            stringPointer+=m;
            printf("usao sam u if\n");
            sorted_input(&heads[n],currentPolynom);
            printf("%dx^%d+",currentPolynom->coefficient,currentPolynom->exponent);
        }

        if(strcmp(buffer,"\n")==0){
            n++;
            printf("%d",n);
        }

        *heads=realloc(*heads,n*sizeof(polynom));

    }

}

int sorted_input(polynom **head,polynom *currentPolynom){
    polynom *temp=*head;

    printf("usao sam u funkciju\n");

    if(*head=NULL){
        printf("usao am u prvi if u funkciji\n");
        *head=currentPolynom;
        currentPolynom->next=NULL;
        return 0;            
    }

    else{
        while(temp->next!=NULL && temp->exponent<=currentPolynom->exponent){
            if(temp->exponent==currentPolynom->exponent){
                temp->coefficient+=currentPolynom->exponent;
                return 0;
            }
            temp=temp->next;
        }
        currentPolynom->next=temp->next;
        temp->next=currentPolynom;
    }
    return 0;
}