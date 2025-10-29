#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osoba {
	char* name;
	char* surname;
	int birth_year;

	struct osoba* next;
};

int addToBeninging(char*, char*, int, osoba*);
int addToNotBeninging(char*, char*, int, osoba*);	
osoba* findBySurname(char*, osoba*);
osoba* findBySurnameMinusOne(char*, osoba*);
int printerGoesWhirrWhoosh(osoba*);
int deletee (char*, osoba*);
int addBefore(char*, char*, int, osoba*,char*);
int addAfter(char*, char*, int, osoba*,char*);
int listSort(osoba *);
int listRead(char *, osoba *);
int listWrite(char *, osoba *);

int main() {
	int value=0;	

	osoba* head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	listRead("./datoteka.txt",head);

	// value=addToBeninging("a", "a", 1939, head);	
	// if(value) return value;
	// value=addToBeninging("b", "b", 2001, head);
	// if(value) return value;
	// value=addToNotBeninging("c", "c", 2077, head);
	// if(value) return value;
	// value=addToNotBeninging("f", "f", 2077, head);
	// if(value) return value;

	printerGoesWhirrWhoosh(head->next);

	char surnameToFind[10];
	printf("\nUnesite prezime koje trazite: ");
	scanf("%s",surnameToFind);
	getc(stdin);

	osoba* temp=findBySurname(surnameToFind, head->next);
	if(!temp){
		printf("Nepostoji osoba s tim prezimenom.\n");
	}else{
		printf("Podudaranost pronadena:%s %s, rodena %d. godine\n",temp->name, temp->surname, temp->birth_year);
	}

	value=deletee(surnameToFind, head);
	if(value) return value;
	printf("Akcije inspirirane Orwell-ovim romanom 1984 pocinjene.\n");
	printerGoesWhirrWhoosh(head->next);

	printf("\nUnesite prezime nakon kojeg cemo ubacit novu osobu: ");
	scanf("%s",surnameToFind);
	getc(stdin);
	value=addAfter("after", "e", 1079, head,surnameToFind);	
	if(value) return value;
	printerGoesWhirrWhoosh(head->next);

	printf("\nUnesite prezime prije kojeg cemo ubacit novu osobu: ");
	scanf("%s",surnameToFind);
	getc(stdin);
	value=addBefore("before", "d", 2025, head,surnameToFind);	
	if(value) return value;
	printerGoesWhirrWhoosh(head->next);

	listSort(head);
	printf("\nSorted list:\n");
	printerGoesWhirrWhoosh(head->next);

	printf("\n");
	//listWrite("./datoteka.txt",head->next);
	listWrite("./output.txt",head->next);
	free(head);

	return 0;
}

int addToBeninging(char* fname, char* lname, int birth_year, osoba* p) {
	osoba* novo = (osoba*)malloc(sizeof(osoba));
	if(!novo) return -1;

	novo->name = strdup(fname);
	novo->surname = strdup(lname);
	novo->birth_year = birth_year;
	novo->next = p->next;

	p->next = novo;

	return 0;
}

int printerGoesWhirrWhoosh(osoba* p) {
	printf("\n");
	while (p) {
		printf("%s %s %d\n", p->name, p->surname, p->birth_year);
		p = p->next;
	}

	return 0;
}

int addToNotBeninging(char* fname, char* lname, int birth_year, osoba* p) {
	while (p->next) {
		p = p->next;
	}

	addToBeninging(fname, lname, birth_year, p);

	return 0;
}

osoba* findBySurname(char* lname, osoba* p){
	while(p){
		if(!strcmp(p->surname, lname)) break;
		p=p->next;
	}

	return p;
}

osoba* findBySurnameMinusOne(char* lname, osoba* p){
	while(p){
		if(!strcmp(p->next->surname, lname)) break;
		p=p->next;
	}

	return p;
}

int deletee(char* lname, osoba* p){
	if(!p->next) return -1;

	while(p->next){	
		if(!strcmp(p->next->surname, lname)) break;
		p=p->next;
	}

	osoba* temp=p->next;
	p->next=temp->next;
	free(temp);

	return 0;
}

int addBefore(char* fname, char* lname, int birth_year, osoba* p, char* personInLine){
	osoba* find=findBySurnameMinusOne(personInLine,p->next);
	addToBeninging(fname, lname, birth_year, find);

	return 0;
}

int addAfter(char* fname, char* lname, int birth_year, osoba* p, char* personInLine){
	osoba* find=findBySurname(personInLine,p->next);
	addToBeninging(fname, lname, birth_year, find);

	return 0;
}

int listSort(osoba *p){
	p = p->next; // postavlj se na prvi pravi element
	if (p == NULL || p->next == NULL)
		return 0;

	osoba *i;

	while (p->next != NULL) // do zadnjeg elementa
	{
		i = p->next;	  // od iduceg elementa
		while (i != NULL) // dok ne dode do kraja
		{
			if (strcmp(p->surname, i->surname) > 0) // usporedba stringova
			{
				char *temp_name = p->name;	//swap
				char *temp_surname = p->surname;
				int temp_birth_year = p->birth_year;

				p->name = i->name;
				p->surname = i->surname;
				p->birth_year = i->birth_year;

				i->name = temp_name;
				i->surname = temp_surname;
				i->birth_year = temp_birth_year;
				// osoba* temp =p;
				// p=i;
				// i=temp;
			}

			i = i->next; // ide se na usporedbu s iducim
		}
		p = p->next; // glavni element usporedbe se mice na iduci
	}

	return 0;
}


int listRead(char *file, osoba *p){
	FILE *f = fopen(file, "r");
	if (f == NULL) return -1;

	char name[20]; // spremaju podatke
	char surname[20];
	int birth_year;

	while (!feof(f))
	{												  // dok ne dode do kraja
		fscanf(f, "%s %s %d\n", name, surname, &birth_year); // cita iz filea
		addToNotBeninging(name, surname, birth_year, p);		  // upisuje na kraj liste

		
	}

	fclose(f);
	return 0;
}

int listWrite(char *file, osoba *p){
	FILE *f = fopen(file, "w"); // otvara file
	if (f == NULL)	return -1; // provjera je li file otvoren

	while (p)
	{															 // za svaki element liste
		fprintf(f, "%s %s %d\n", p->name, p->surname, p->birth_year); // ispisuje u file
		p = p->next;
	}

	fclose(f);
	return 0;
}