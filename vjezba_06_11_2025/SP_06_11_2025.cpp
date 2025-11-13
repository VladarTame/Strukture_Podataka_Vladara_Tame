#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct polinom{
	int baza;
	int exponent;
	struct polinom *next;
};

int fileRead(char *, polinom *, polinom *);
int segregation(int, int, polinom *);	
int addon(polinom *, polinom *, polinom *);
int romi(polinom *, polinom *, polinom *);

int main(){
	polinom head1 = {0, 0, NULL},head2 = {0, 0, NULL};
	polinom head_sum = {0, 0, NULL},headCensusOfRomi = {0, 0, NULL};

	fileRead("./datoteka.txt", &head1, &head2);
	addon(&head1, &head2, &head_sum);
	romi(&head1, &head2, &headCensusOfRomi);


	polinom *p = head1.next;
	// p = head1.next;
	// while (p != NULL){
	// 	printf("%dx^%d", p->baza, p->exponent);
	// 	if (p->next != NULL)
	// 		printf(" + ");
	// 	p = p->next;
	// }

	// p = head2.next;
	// while (p != NULL){
	// 	printf("%dx^%d", p->baza, p->exponent);
	// 	if (p->next != NULL)
	// 		printf(" + ");
	// 	p = p->next;
	// }

	printf("\n%s","zbroj africans: ");
	p = head_sum.next;
	while (p != NULL){
		printf("%dx^%d", p->baza, p->exponent);
		if (p->next != NULL)
			printf(" + ");
		p = p->next;
	}
	
	printf("\n%s","umnozak roma/kosovcana(SR): ");
	p = headCensusOfRomi.next;
	while (p != NULL){
		printf("%dx^%d", p->baza, p->exponent);
		if (p->next != NULL)
			printf(" + ");
		p = p->next;
	}
	printf("\n");

	return 0;
}

int segregation(int coeficient, int exponentt, polinom *p){
	polinom *novi = (polinom *)malloc(sizeof(polinom));
	if (novi == NULL) return -1;

	novi->baza = coeficient;
	novi->exponent = exponentt;

	while (p->next != NULL && p->next->exponent > exponentt){
		p = p->next;
	}

	if (p->next != NULL && p->next->exponent == exponentt){
		p->next->baza += coeficient;
		free(novi);
		return 0;
	}

	novi->next = p->next;
	p->next = novi;

	return 0;
}

int fileRead(char *path, polinom *p1, polinom *p2){
	FILE *f = fopen(path, "r");
	if (f == NULL)	return -1;

	char buffer = '0';
	int coeficient_temp = 0, exponent_temp = 0;

	while (buffer != '\n'){
		fscanf(f, "%d %d", &coeficient_temp, &exponent_temp);
		segregation(coeficient_temp, exponent_temp, p1);
		buffer = fgetc(f);
	}
	buffer = '0';

	while (buffer != EOF){ 
		fscanf(f, "%d %d", &coeficient_temp, &exponent_temp);
		segregation(coeficient_temp, exponent_temp, p2);
		buffer = fgetc(f);
	}

	fclose(f);
	return 0;
}

int addon(polinom *p1, polinom *p2, polinom *rez){
	p1 = p1->next;
	p2 = p2->next;
	while (p1 != NULL){
		segregation(p1->baza, p1->exponent, rez);
		p1 = p1->next;
	}

	while (p2 != NULL){
		segregation(p2->baza, p2->exponent, rez);
		p2 = p2->next;
	}

	return 0;
}

int romi(polinom* p1, polinom* p2, polinom* rez){
	p1 = p1->next;
	p2 = p2->next;
	
	polinom* start=p2;

	while(p1!=NULL){
		p2=start;
		while(p2!=NULL){
			segregation(p1->baza*p2->baza, p1->exponent+p2->exponent, rez);
			p2=p2->next;
		}
		p1=p1->next;
	}

	return 0;
}