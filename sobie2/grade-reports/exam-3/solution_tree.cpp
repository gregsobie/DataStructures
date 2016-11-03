#include "common.h"
#include <iostream>

using namespace std;

void updateSum(Node<int> *&root)
{
	// YOUR CODE HERE!
	/* Recursive base case */
	if(root == NULL)
		return;

	/* Recursively update sums of left, then right
	   side of tree */
	updateSum(root->left);
	updateSum(root->right);

	/* Treat NULL nodes as having a value of 0 */
	if(root->left == NULL && root->right != NULL)
		root->data += root->right->data;
	else if(root->right == NULL && root->left != NULL)
		root->data += root->left->data;
	else if(root->left == NULL && root->right == NULL)
		return;
	else
		root->data += root->left->data + root->right->data;
}
