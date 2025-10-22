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
int printerGoesWhirrWhoosh(osoba*);
int deletee (char*, osoba*);

int main() {
	int value=0;	

	osoba* head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	value=addToBeninging("a", "a", 1939, head);	
	if(value) return value;
	value=addToBeninging("b", "b", 2001, head);
	if(value) return value;
	value=addToNotBeninging("c", "c", 2077, head);
	if(value) return value;

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

	printf("\n");
	free(head);
	return 0;
}

int addToBeninging(char* fname, char* lname, int birth_year, osoba* p) {
	osoba* novo = (osoba*)malloc(sizeof(osoba));
	if(!novo) return -1;

	novo->name = fname;
	novo->surname = lname;
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