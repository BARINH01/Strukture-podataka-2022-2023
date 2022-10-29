#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


typedef struct {
    char ime[100], prezime[100];
    int godiste;
    struct _osoba* next;
}_osoba;

/*_osoba *alociraj_ucitaj_izbroji(char *unos){
    FILE *f;
    _osoba *o;
    int n=0;
    char temp[100];
    printf("%s",unos);
    printf("usao sam u funkciju\n");
    f=fopen(unos,"r");
    
    if(!f){
        printf("neuspješno otvorena datoteka");
        return NULL;
    }
    
    o=malloc(sizeof(_osoba));
    if(!o){
        printf("neuspješno zauzimanje memorije");
        free(o);
        return NULL;
    }
    
    while(!feof(f)){
        fgets(temp,100,f);
        printf("usao sam u while\n");
        if(sscanf(temp," %s %s %d", o[n].ime, o[n].prezime, &o[n].godiste)==3){
            printf("%s %s %d\n", o[n].ime, o[n].prezime, o[n].godiste);
            printf("%d\n",n);
            n++;
            o=realloc(o,(n+1)*sizeof(_osoba));
            if(!o){
                printf("neuspjesno alociranje");
                free(o);
                return NULL;
            }
            o[n-1].next=&o[n];
        }
        
    }

    o=realloc(o,n*sizeof(_osoba));
    o[n].next=NULL;
    
    fclose(f);
    return o;
   
}
*/

void printList(_osoba *pocetak){
    _osoba *temp=pocetak;

    while(temp!=NULL){
        printf("%s %s %d\n", temp->ime, temp->prezime, temp->godiste);
        temp=temp->next;
    }
}

void unos_u_struct (_osoba *zaUnos){
        
    printf("unesi Ime nove osobe ");
    scanf("%s", zaUnos->ime);

    printf("unesi prezime nove osobe ");
    scanf("%s",zaUnos->prezime);

    printf("unesi godiste nove osobe ");
    scanf("%d",&zaUnos->godiste);
}

void umetni_poslje(_osoba *prosla_osoba){
    _osoba *nova_osoba;
    printf("Osoba pronadena\n");
    nova_osoba=malloc(sizeof(_osoba));

    if(!nova_osoba){
        printf("memorija neuspješno alocirana");
        return;
    }

    unos_u_struct(nova_osoba);

    nova_osoba->next=prosla_osoba->next;
    prosla_osoba->next=nova_osoba;

    printf("uspio sam unjet\n");

}

void umetni_prije(_osoba *sljedeca_osoba){
    _osoba *nova_osoba;
    printf("Osoba pronadena\n");
    nova_osoba=malloc(sizeof(_osoba));
    unos_u_struct(nova_osoba);


}

_osoba *trazi_ime(char *unos,_osoba *o){
    _osoba *temp=malloc(sizeof(_osoba));
    temp = o;
    
    while(temp!=NULL){
        if(strcmp(unos,temp->prezime)==0){
            return temp;
        }

        temp=temp->next;
    }
    if(temp->next==NULL){
        printf("nisam nasa tu osobu");
        return NULL;
    }
}

int main(){
    _osoba *o, *head;
    FILE *f;
    f=fopen("osobe.txt","r");
    int n=1;
    char c;

    while((c=getc(f))!=EOF){
        if(c=='\n'){
            n++;
        }
    }
    rewind(f);
    printf("%d\n",n);
    o=malloc(n*sizeof(_osoba));
    head=&o[0];
    o[n].next=NULL;
    for(int i=1;i<n-1;i++){
        o[i-1].next=&o[i]; 
    }

    for(int i=0;i<n;i++){
        fscanf(f,"%s %s %d", o[i].ime, o[i].prezime, &o[i].godiste);  
    }

    /*printf("koju datoteku zelite otvoriti\n");

    scanf("%s",&c);
    o=alociraj_ucitaj_izbroji(c);
    head=&o[0];*/
    
    char unos;
    while(unos!='k'){
        printf("Za print liste unesi 1\nZa dodavanje elementa unesi 2\n");
        scanf("%c", &unos);
        switch (unos)
        {
        case '1':
            printList(head);
            break;
    
        case '2':
            printf("Poslije koga zelite dodati novu osobu (prezime)\n");
            char unos1[100];
            scanf("%s",unos1);
            umetni_poslje(trazi_ime(unos1,o));
            break;

        default:
            printf("\n");
        }   
    }
    return 0;

}