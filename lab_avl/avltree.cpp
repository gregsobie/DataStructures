/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;

    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;

    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    /* If there exists a height imbalance on left side */
    if((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) == -2){
        /* Check which side of left has greater height
         * and perform necessary rotations */
        if((heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left)) == -1)
            rotateRight(subtree);
        else     rotateLeftRight(subtree);
    /* Else if there exists a height imbalance on right side */
    }else if((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) == 2){
        /* Check which side of right has greater height
         * and perform necessary rotations */
        if((heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left)) == 1)
            rotateLeft(subtree);
        else     rotateRightLeft(subtree);    
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    /* Base case */
    if(subtree == NULL)
        subtree = new Node(key, value);
    /* Check left subtree */
    else if(key < subtree->key)
        insert(subtree->left, key, value);
    /* Check right subtree */
    else if(key > subtree->key)
        insert(subtree->right, key, value);
    rebalance(subtree);
    subtree->height = max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left))+1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
    remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
    remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
        delete subtree;
        subtree=NULL;
	return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
        Node* temp=subtree->left;
        while(temp->right != NULL)
            temp=temp->right;
        swap(subtree, temp);
        remove(subtree->left, key);
	return;
        } else {
            /* one-child remove */
            // your code here
        if(subtree->left == NULL && subtree->right != NULL){
            Node* temp=subtree->right;
            delete subtree;
            subtree = temp;
        }else if(subtree->left != NULL && subtree->right == NULL){
            Node* temp=subtree->left;
            delete subtree;
            subtree = temp;
	return;
        }
        }
        // your code here
    //return;
    }
    rebalance(subtree);
}
