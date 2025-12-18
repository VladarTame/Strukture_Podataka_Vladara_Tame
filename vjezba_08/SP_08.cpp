#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
	int value;
	struct tree *left;
	struct tree *right;
} branch;

branch *aNewHandTouchesTheBeacon(int);
branch *newHand(branch *, int);
branch *detectiveWork(branch *, int);
branch *disorderlyConduct(branch *);
branch *iWouldLikeToPreorderThisOne(branch *);
branch *postApocalypse(branch *);
branch *soloLeveling(branch *);

int main()
{
	branch *root = (branch *)malloc(sizeof(branch));
	root->left = NULL;root->right = NULL;
	root->value = 2;

	newHand(root, 5);
	newHand(root, 7);
	newHand(root, 8);
	newHand(root, 11);
	newHand(root, 1);
	newHand(root, 4);
	newHand(root, 2);
	newHand(root, 3);
	newHand(root, 7);

	printf("Initial values:\n2 5 7 8 11 1 4 2 3 7\n");

	printf("Inorder:\n");
	disorderlyConduct(root);
	printf("\nPreorder:\n");
	iWouldLikeToPreorderThisOne(root);
	printf("\nPostorder:\n");
	postApocalypse(root);
	printf("\nLevelorder:\n");
	soloLeveling(root);
	printf("\n");

/*
workent
*/
	// branch leaf = detectiveWork(root, 11);
	// printf("Trazi se 11 bcs why not: ");
	// if (leaf != NULL)
	// 	printf("Element %d has not touched the beacon.\n", leaf->n);
	// else
	// 	printf("Element has touched the beacon.\n");

	return 0;
}

branch *aNewHandTouchesTheBeacon(int n)
{
	branch *temp = (branch *)malloc(sizeof(branch));
	temp->value = n;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

branch *newHand(branch *root, int n)
{
	if (root == NULL) return aNewHandTouchesTheBeacon(n);

	if (n > root->value) root->right = newHand(root->right, n);
	else root->left = newHand(root->left, n);

	return root;
}

branch *detectiveWork(branch *root, int n)
{
	/*more or less the same*/
	if (root == NULL) return NULL;
	if (n == root->value) return root;

	/*gledaj lijevo i desno prije prelaska ceste*/
	if (n < root->value) root = detectiveWork(root->left, n);
	else root = detectiveWork(root->right, n);
	return root;
}

branch *disorderlyConduct(branch *root)
{
	if (root == NULL) return NULL;

	disorderlyConduct(root->left);
	printf("%d ", root->value);
	disorderlyConduct(root->right);
	return root;
}

branch *iWouldLikeToPreorderThisOne(branch *root)
{
	if (root == NULL) return NULL;

	printf("%d ", root->value);
	iWouldLikeToPreorderThisOne(root->left);
	iWouldLikeToPreorderThisOne(root->right);
	return root;
}

branch *postApocalypse(branch *root)
{
	if (root == NULL) return NULL;
	postApocalypse(root->left);
	postApocalypse(root->right);
	printf("%d ", root->value);
	return root;
}

branch *soloLeveling(branch *root)
{
	if (root == NULL) return NULL;

	branch *queue[32];
	int start = 0, end = 0;

	queue[end] = root;
	end++;

	while (start < end){
		printf("%d ", queue[start]->value);

		if (queue[start]->left != NULL) queue[end++] = queue[start]->left;
		if (queue[start]->right != NULL) queue[end++] = queue[start]->right;

		start++;
	}

	return root;
}