#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
	char *name;
	struct tree *sibling;
	struct tree *children;
	struct tree *parent;
} branch;

int locateThePDFiles(branch *);
int createThePDFiles(branch *, char *);
int listThePDFiles(branch *);
branch *selectThePDFile(branch *, char *);
branch *previousPDFile(branch *);

int main()
{
	branch *root = (branch *)malloc(sizeof(branch));
	if (root == NULL)
		return 0;

	root->name = strdup("root");
	root->children = NULL;
	root->sibling = NULL;
	root->parent = NULL;

	branch *current = root;

    char command[10];
	char xxx[20];
	do{
		printf("\n1 - mkdir   2 - cd   3 - cd..   4 - ls\n0 - exit\n\n");
        locateThePDFiles(current);printf(">");
		scanf("%s", &command);getchar();

        if(!strcmp(command,"mkdir")){
            printf("Name of new directory: ");
            scanf("%s", xxx);
            getchar();
            createThePDFiles(current, xxx);
        }
        else if(!strcmp(command,"cd")){
            printf("Name of directory: ");
            scanf("%s", xxx);
            getchar();
            current = selectThePDFile(current, xxx);
        }
        else if(!strcmp(command,"cd..")) current = previousPDFile(current);
        else if(!strcmp(command,"ls")) listThePDFiles(current);
        else if(!strcmp(command,"exit")){}
        else{
           printf("Command not recognized\n");
        }

	}while (strcmp(command,"exit"));

	return 1;
}

int locateThePDFiles(branch *location)
{
	if (location == NULL)
		return 1;
	locateThePDFiles(location->parent);
	printf("%s/", location->name);
	return 1;
}

int createThePDFiles(branch *location, char *str)
{
	branch *p = location->children;

	branch *temp = (branch *)malloc(sizeof(branch));
	if (temp == NULL)
		return 0;

	temp->sibling = NULL;
	temp->children = NULL;
	temp->name = strdup(str);

	if (p == NULL)
	{	
		location->children = temp;
		temp->parent = location;
		return 1;
	}

	while (p->sibling != NULL)
		p = p->sibling;
	p->sibling = temp;
	temp->parent = location;

	return 1;
}

int listThePDFiles(branch *location)
{
	branch *p = location->children;

	while (p != NULL)
	{
		printf("%s\t", p->name);
		p = p->sibling;
	}
	printf("\n");

	return 1;
}

branch *selectThePDFile(branch *location, char *str)
{
	branch *p = location->children;

	while (p != NULL && strcmp(p->name, str))
		p = p->sibling;

	if (p == NULL)
	{
		printf("Directory not foound\n");
		return location;
	}

	return p;
}

branch *previousPDFile(branch *location)
{
	if (location->parent == NULL)
	{
		printf("Already in tree root\n");
		return location;
	}
	return location->parent;
}