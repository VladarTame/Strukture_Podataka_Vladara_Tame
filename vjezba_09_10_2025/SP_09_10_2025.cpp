#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximum_points 100

typedef struct student{
	char name[20];
	char surname[20];
	int points;
} _student;

int sudentAttendance(char*);   //number of pupils
int noPrivacyForStudents(char*, _student*); 
double CalculatorGoBrrr(int);	//relative score
int releaseTheFiles(_student*);    //printing pupils info (bcs ig this needs commenting 2 ig)

int main() {
	int br_stud=0; 
	int i=0; //i

	br_stud = sudentAttendance("./datoteka.txt");

	_student* students = (_student*)malloc(br_stud * sizeof(_student));	//alocation for studedents
	if (students == NULL) {
		return -1;
	}

	noPrivacyForStudents("./datoteka.txt", students);

	//printing student info (like its manifesto)
	for (i = 0; i < br_stud; i++) {
		releaseTheFiles(students+i);	//'comic printer sound'
	}
	putc('\n',stdout);
	free(students);

	return 0;
}

int sudentAttendance(char* path) {
	int i = 0;
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		fclose(file);
		return -1;
	}

	while (!feof(file)) {
		if(fgetc(file)=='\n') i++;
	}
	
	fclose(file);

	return i;
}

int noPrivacyForStudents(char* path, _student* students) {
	FILE* file = fopen(path, "r");
	int i=0;	//i

	if (file == NULL) {
		fclose(file);
		return -1;
	}

	while (!feof(file)) {
		fscanf(file, "%s %s %d ", students[i].name, students[i].surname, &students[i].points);	//scans studennt info (like goverment our messages) and stores it in an instance
		i++;	//i++
	}

	fclose(file);

	return 0;
}

double CalculatorGoBrrr(int score) {
	return (double)score / maximum_points * 100;
}

int releaseTheFiles(_student* s) {
	printf("%s %s %d/100 %.2f%%\n", s->name, s->surname, s->points, CalculatorGoBrrr(s->points));	//prints data(just like goverment money)

	return 0;
}