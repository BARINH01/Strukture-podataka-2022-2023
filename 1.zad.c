#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct
{
   char ime[100], prezime[100];
   int bodovi;
}_studenti;


int PrebrojiFile(char *c){

   FILE *f;
   char linija[100];
   int n=0;
   printf("%s",c);
   f=fopen(c,"r");
   if(f==NULL){
      printf("file nije otvoren");
      return;
   }

   while(fgets(linija,100,f)!=NULL){
      if(strcmp(linija,"\n")!=0){
         n++;
      }
   }

   return n;
   fclose(f);
}

void UpisiStrukturu(_studenti s[],char *c, int n){

   FILE *f;
   f=fopen(c,"r");
   if(f==NULL){
      printf("file nije otvoren\n");
      return;
   }
   for(int i=0; i<n;i++){
      fscanf(f,"%s %s %d",s[i].ime,s[i].prezime,s[i].bodovi);
   }
   fclose(f);
}

void RndBodovi(_studenti s[],int n){

   srand(time(NULL));
   int bod;
   for(int i=0;i<n;i++){
      bod=rand()%34;
      s[i].bodovi=bod;
   }   
}

void IspisPodataka(_studenti *s,int n){

   for(int i=0;i<n;i++){
      printf("ime studenta je: %s prezime studenta je: %s, broj bodova je: %d, postotak je %.2f\n",s[i].ime,s[i].prezime,s[i].bodovi,((s[i].bodovi*1.00/34.00)*100.00));
   }
}

int main(){

   _studenti *s;
   char unos[100];
   int i,n=1;

   printf("Unesi ime datoteke\n");
   scanf("%s",unos);

   n=PrebrojiFile(unos);
   printf("%d",n);

   s=malloc(n*sizeof(_studenti));
   
   RndBodovi(s,n);
   UpisiStrukturu(s,unos,n);
   IspisPodataka(s,n);
}
