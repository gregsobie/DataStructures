#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int removeAt(queue<int> &q, int pos)
{
	// YOUR CODE HERE!
	/* Element to be removed, -1 if invalid index */
	int ret = -1;

	/* If invalid index, return -1 */
	if(pos<0 || pos>=q.size())
		return ret;

	/* For each element in the queue */
	for(int i=0; i<=q.size(); i++){
		/* If pos is valid index, remove element 
			at that index */
		if(i==pos){
			ret = q.front();
			q.pop();
		/* Move next element to back of queue so as
		   to avoid modifying it */
		} else {
			q.push(q.front());
			q.pop();
		}
	}
	/* Return removed element */
	return ret;
}
