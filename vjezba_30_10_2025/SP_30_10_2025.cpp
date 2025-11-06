#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct n{
	int number;
	struct n *next;
};

int pushItIn(int, n *);
int popItOut(n *);
int calcuratores(int, int, char);
int datotekaCalculatores(char *, n *);

int main(){

	n head = {0, NULL};

	printf("Rezultat je %d\n", datotekaCalculatores("./datoteka.txt", &head));

	return 0;
}


int pushItIn(int x, n *p){

	n *novi = (n *)malloc(sizeof(n));
	if (novi == NULL) return -1;

	novi->number = x;
	novi->next = p->next;
	p->next = novi;

	return 0;
}

int popItOut(n *p){

	n *temp = p->next;
	if (temp == NULL) return 1;

	int n = temp->number;

	p->next = temp->next;
	free(temp);
	return n;
}

int calcuratores(int a, int b, char o){

	int rez = 0;
	switch (o)
	{
	case '+':
		rez = a + b;
		break;
	case '-':
		rez = a - b;
		break;
	case '*':
		rez = a * b;
		break;
	case '/':
		rez = a / b;
		break;
	}

	return rez;
}

int datotekaCalculatores(char *path, n *p){

	char buffer[10], *end;
	int a = 0, b = 0;

	FILE *f = fopen(path, "r");
	if (f == NULL)
		return -1;

	while (!feof(f))
	{
		fscanf(f, "%s ", buffer);

		switch (buffer[0])
		{
		case '+':
		case '-':
		case '*':
		case '/':	
			b = popItOut(p);	
			a = popItOut(p);	
			pushItIn(calcuratores(a, b, buffer[0]), p);
			break;
		default:
			pushItIn(strtol(buffer, &end, 10), p);
		}
	}

	fclose(f);
	return popItOut(p);
}