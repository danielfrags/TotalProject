#include<stdlib.h>
#include<stdio.h>
#include "items.h"


typedef struct bin_tree
{
	int data;
	struct bin_tree* right, * left, * parent;
}node;


node* tree()
{
	node* root = NULL;
	node A = { 1, NULL,NULL ,NULL };
	node B = { 2, NULL,NULL ,NULL };
	node C = { 3, NULL,NULL ,NULL };
	node D = { 4, NULL,NULL ,NULL };
	node E = { 5, NULL,NULL ,NULL };

	A.right = &C;
	A.left = &B;
	C.left = &D;
	B.right = &E;

	C.parent = &A;
	B.parent = &A;
	D.parent = &C;
	E.parent = &B;

	root = &A;

	return root;

}

int findvalue(node* root, int value) {
	if (root == NULL) {
		return 0; // Reached the end of a branch, value not found
	}

	if (root->data == value) {
		return 1; // Value found
	}

	// Recursively check the left and right subtrees
	if (findvalue(root->left, value) || findvalue(root->right, value)) {
		return 1;
	}

	return 0; // Value not found in either subtree
}

void main()
{
	node* root;
	root = tree();
	int num = 6;
	int result;
	result = findvalue(root, num);
	if (result == 1)
		printf("the value appear in the tree");
	else
		printf("the value doesn't appear in the tree");
}