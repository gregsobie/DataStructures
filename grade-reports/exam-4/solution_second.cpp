#include "common.h"
#include "quadtree.h"

#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

int Quadtree::tallyDeviants(RGBAPixel const & target, 
    QuadtreeNode const * curNode, int tolerance) const {
    //YOUR CODE HERE
	int count=0;
	/* Base case -- curNode is a leaf, check tolerance */
	if(curNode->nwChild==NULL && curNode->neChild==NULL &&
	   curNode->swChild==NULL && curNode->seChild==NULL){
		if((curNode->element.red > target.red + tolerance) ||
		   (curNode->element.green > target.green + tolerance) ||
		   (curNode->element.blue > target.blue + tolerance))
			count++;
	}else{
		tallyDeviants(target, curNode->nwChild, tolerance);
		tallyDeviants(target, curNode->neChild, tolerance);
		tallyDeviants(target, curNode->swChild, tolerance);
		tallyDeviants(target, curNode->seChild, tolerance);
	}
    return count;
}

void Quadtree::prunish(int tolerance, double percent) {
    //YOUR CODE HERE
	prunish(root, tolerance, percent);
} 

void Quadtree::prunish(QuadtreeNode * curNode, int tolerance, int res, double percent) {
    //YOUR CODE HERE
	if(curNode==NULL)
		return;
	for(int i=0; i<res; i++){
		int numDeviants=tallyDeviants(curNode->element, curNode, tolerance);
		if((numDeviants/res)>=percent){
			prunish(curNode->nwChild, tolerance, res, percent);
			prunish(curNode->neChild, tolerance, res, percent);
			prunish(curNode->swChild, tolerance, res, percent);
			prunish(curNode->seChild, tolerance, res, percent);
		}
	}
	
}
