#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

Node<int>* deleteNode(Node<int> *&root, int target)
{
	// YOUR CODE HERE!
	/* Recursive base case */
	if(root==NULL) return NULL;
	/* Else if root->data > target, recur through left subtree */
	else if(root->data > target)
		deleteNode(root->left, target);
	/* Else if root->data < target, recur through right subtree */
	else if(root->data < target)
		deleteNode(root->right, target);
	/* Else if root->data == target, we have found the key and
	 * must check how many children this node has */
	else{
		Node<int>* temp;
		/* No children -- simply return root */
		if(root->left==NULL && root->right==NULL){
			delete root;
			root=NULL;
		/* One child -- left */
		}else if(root->left!=NULL && root->right==NULL){
			/*temp=root->left;
			delete root->left;
			root->left=NULL;
			root=temp;*/
			root=root->left;
			delete root->left;
			root->left=NULL;
		/* One child -- right */
		}else if(root->left==NULL && root->right!=NULL){
			/*temp=root->right;
			delete root->right;
			root->right=NULL;
			root->data=temp->data; */
			root=root->right;
			delete root->right;
			root->right=NULL;
		/* Two children */
		}else{
			/* Find POI and replace root with value */
			temp=root->left;
			while(temp->right!=NULL)
				temp=temp->right;
			root->data=temp->data;
			if(temp->left!=NULL)
				temp=temp->left;
			delete temp->left;
			temp->left=NULL;
		}
	}
	return root;
}
