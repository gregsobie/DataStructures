#include "linkedlist.h"
#include <iostream>
using namespace std;

bool append(LinkedList &mylist, int newdata)
{
	Node* newNode = new Node(newdata);

	if(mylist.head==NULL){
		mylist.head = newNode;
		mylist.head->next = NULL;
		return 1;
	} else {
		Node* temp = mylist.head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = NULL;
		return 1;
	}
	return 0;
}
