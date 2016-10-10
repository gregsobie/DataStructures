/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // your code here
	//Call recursive helper function
	mirror(root);
}

/**
 * Private helper function for the public mirror function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    	// Base case - null node
    	if (subRoot == NULL)
        	return;
	//Swap left and right for current node
	Node* temp = subRoot->left;
	subRoot->left = subRoot->right;
	subRoot->right = temp;

	mirror(subRoot->left);
	mirror(subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
	//Call recursive helper function
    return isOrdered(root);
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot
 */
template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const
{
	bool leftOrdered, rightOrdered;
	int leftmostRight, rightmostLeft;

    	// Base case - null node
    	if (subRoot == NULL)
        	return true;
	// Order left side
	if (subRoot->left == NULL){
		leftOrdered = true;
		rightmostLeft = subRoot->elem;
	} else {
		leftOrdered = isOrdered(subRoot->left);
		
		Node* temp = subRoot->left;
		while(temp->right != NULL)
			temp = temp->right;
		rightmostLeft = temp->elem;
	}

	// Order right side
	if (subRoot->right == NULL){
		rightOrdered = true;
		leftmostRight = subRoot->elem;
	} else {
		rightOrdered = isOrdered(subRoot->right);
		
		Node* temp = subRoot->right;
		while(temp->left != NULL)
			temp = temp->left;
		leftmostRight = temp->elem;
	}

	// If list is ordered
	if(leftOrdered && rightOrdered && subRoot->elem >= rightmostLeft && subRoot->elem <= leftmostRight)
		return true;
	return false;

}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
	int path[100];
	// Call recursive helper function
	printPaths(root, path, 0);
}

/**
 * Private helper function for the public printPaths function.
 * @param subRoot
 * @param path[] Array of current path from root to leaf
 * @param index  Index of the current node in the path array
 */
template <typename T>
void BinaryTree<T>::printPaths(const Node* subRoot, int path[], int index) const
{
	// Base case - null node
	if(subRoot == NULL)
		return;

	// Store next node in path array and move to next node
	path[index] = subRoot->elem;
	index++;

	// If current node is a leaf, print path
	if(subRoot->left == NULL && subRoot->right == NULL){
		cout << "Path: ";
		for(int i=0; i<index; i++)
			cout << path[i] << " ";
		cout << endl;
	} else {
		printPaths(subRoot->left, path, index);
		printPaths(subRoot->right, path, index);
	}
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
	// Call recursive helper function
	int sum, dist;
	sum=0;
	dist=0;
	sumDistances(root, sum, dist);
	return sum;
}

/**
 * Private helper function for the public sumDistances function.
 * @param subRoot
 * @param sum     Holds the totaled distances for each path
 * @param dist    Distance between root and leaf for given path
 */
template <typename T>
void BinaryTree<T>::sumDistances(const Node* subRoot, int & sum, int dist) const
{
	// Base case - null node
	if(subRoot == NULL)
		return;
	sum += dist;
	sumDistances(subRoot->left, sum, dist+1);
	sumDistances(subRoot->right, sum, dist+1);
}

