/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	while(head!=NULL){
		tail=head->next;
		delete head;
		head=tail;
	}
	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* newNode = new ListNode(ndata);
	
	if(head!=NULL){
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	} else {
		head=newNode;
		tail=newNode;
	}
	length++;
	newNode=NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
	ListNode* newNode = new ListNode(ndata);
	if(tail!=NULL){
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	} else {
		head = newNode;
		tail = newNode;
	}
	length++;
	newNode=NULL;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
	if(startPoint == endPoint)
		return;
	
	ListNode* currIndex = startPoint;
	ListNode* oldIndex = startPoint;
	ListNode* endIndex = endPoint->next;

	//Swaps next and prev for all nodes in reverse range
	while(currIndex != endIndex){
		oldIndex = currIndex->prev;
		currIndex->prev = currIndex->next;
		currIndex->next = oldIndex;
		currIndex = currIndex->prev;
	}

	//Stores starting index of elements after the reverse range
	oldIndex = endPoint->prev;

	//Restores elements before the reverse range
	if(startPoint->next != NULL){
		endPoint->prev = startPoint->next;
		endPoint->prev->next = endPoint;
	}
	else
		endPoint->prev = NULL;

	//Restores elements after the reverse range
	if(oldIndex != NULL){
		startPoint->next = oldIndex;
		startPoint->next->prev = startPoint;
	}
	else
		startPoint->next = NULL;

	/*Update startPoint and endPoint to point to respective locations
	in the rearranged list*/
	oldIndex=startPoint;
	startPoint=endPoint;
	endPoint=oldIndex;

	currIndex=NULL;
	oldIndex=NULL;
	endIndex=NULL;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
	//List stays the same if length<=1 or n==1
	if(length<=1 || n<=1){
		return;
	//Reverse entire list if block length is greater than list length
	} else if(n>=length){
		reverse();
	//Else reverse block
	} else {
		ListNode* newHead = head;
		ListNode* newTail = head;	

		//While there are more blocks to reverse,
		for(int i=0; i<length; i+=n){
			//reverse the next block
			for(int j=1; j<n; j++){
				if(newTail->next != NULL)
					newTail = newTail->next;
			}

			reverse(newHead, newTail);

			//Update head pointer if first block
			if(i < n){
				head = newHead;
			}
			//Update tail pointer if last block
			if((length - i) <= n){
				tail = newTail;
			}

			//Update block head and tail pointers
			newHead = newTail->next;
			newTail = newHead;
		}
		newHead=NULL;
		newTail=NULL;
	} 
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	ListNode* currIndex = head;
	ListNode* oldIndex = head;
	ListNode* oldTail;
	int everyOther = 1; //First node is skipped

	//For every element in the list,
	for(int i=0; i<length; i++){
		/*Move every other node to the tail of list
			and update tail */
		if(everyOther%2==0){
			oldTail = tail;
			insertBack(currIndex->data);
			oldIndex->next = currIndex->next;
			currIndex->prev = oldIndex;
			tail->prev = oldTail;
		}
		//Update pointers
		oldIndex = currIndex;
		currIndex = currIndex->next;
		everyOther++;
	}
	currIndex=NULL;
	oldIndex=NULL;
	oldTail=NULL;
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    return NULL; // change me!
}
