#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define ERROR_MESSAGE (-1)

struct _student;
typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} student;
student* Alocirajmemorijuucitajpodatke(char* nazivdatoteke, int brojstudenata);
double izracunajmaksimalanbrojbodova(int brojac, student* studenti);
void ispispodataka(student* studenti, int brojac);
int IzbrojiStudente(char* filename);
int main() {

	char nazivdatoteke[MAX_LINE] = { 0 };
	student* studenti = NULL;

	printf("Unesi ime datoteke (s datotecnim nastavkom): \n");
	scanf(" %s", nazivdatoteke);
	int brojstudenata = 0;
	brojstudenata = IzbrojiStudente(nazivdatoteke);

	if (brojstudenata <= 0) 
		printf("U datotetci nema upisanih studenata!\n");

	studenti = Alocirajmemorijuucitajpodatke(nazivdatoteke, brojstudenata);

	if (!studenti) {
		return ("Greska pri alociranju memorije!\n");
	}

	ispispodataka(studenti, brojstudenata);

	return NULL;
}

int IzbrojiStudente(char* nazivdatoteke) {
	char buffer[MAX_LINE], ime[MAX_SIZE], prezime[MAX_SIZE] = { 0 };
	int brojac = 0;
	double bodovi = 0.0;
	FILE* p = NULL;

	p = fopen(nazivdatoteke, "r");

	if (!p) {
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR_MESSAGE;
	}
	while (!feof(p)) {
		fgets(buffer, MAX_LINE, p);
		if (sscanf(buffer, " %s\t%s\t%lf", ime, prezime, &bodovi) == 3) {
			++brojac;
		}
	}
	fclose(p);
	return brojac;
}

student* Alocirajmemorijuucitajpodatke(char* nazivdatoteke, int brojstudenata) {

	FILE* p = NULL;
	student* studenti = NULL;
	int brojac = 0;
	char ime[MAX_SIZE], prezime[MAX_SIZE], buffer[MAX_LINE] = { 0 };
	double bodovi = 0.0;

	studenti = (student*)malloc(brojstudenata * sizeof(student));
	if (!studenti) {
		printf("Greska pri alociranju memorije!\n");
		return NULL;
	}

	p = fopen(nazivdatoteke, "r");

	if (!p) {
		printf("Greska pri otvaranju datoteke!\n");
		free(studenti);
		return NULL;
	}
	while (!feof(p)) {
		fgets(buffer, MAX_LINE, p);
		if (sscanf(buffer, " %s\t%s\t%lf", ime, prezime, &bodovi) == 3) {
			strcpy(studenti[brojac].ime, ime);
			strcpy(studenti[brojac].prezime, prezime);
			studenti[brojac].bodovi = bodovi;
			++brojac;
		}
	}
	fclose(p);
	return studenti;
}
double izracunajmaksimalanbrojbodova(int brojac, student* studenti) {
	int max_br = 0;
	int i = 0;

	for (i = 1; i < brojac; i++) {
		if (studenti[i].bodovi > studenti[max_br].bodovi)
			max_br = i;
	}

	return studenti[max_br].bodovi;
}
void ispispodataka(student* studenti, int brojac) {
	int i = 0;
	double max_br_bodova = 0;

	max_br_bodova = izracunajmaksimalanbrojbodova(brojac, studenti);

	for (i = 0; i < brojac; i++) {
		printf(" %s %s %lf %.3lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, (double)studenti[i].bodovi / max_br_bodova * 100);
	}
}