/* Your code here! */

#include "dsets.h"

/* This function will create 'num' unconnected root nodes
   Input: @param num - Number of nodes to create
   Output: None
   Effects: Appends nodes to the end of the uptree vector */
void DisjointSets::addelements(int num){
	for (int i=0; i<num; i++)
		uptree.push_back(-1);
}

/* This function will compress paths to find the uptree which
	contains the element
   Input: @param elem - Element to find
   Output: Index of the root of the uptree in which @param elem resides
   Effects: None */
int DisjointSets::find(int elem){
	return (uptree[elem]<0) ? elem : find(uptree[elem]);
}

/* This function will combine two disjoint sets, implemented as
	union-by-size.
   Input: @param a - Index of the first element to union
	  @param b - Index of the second element to union
   Output: None
   Effects: Sets union to two disjoint sets */
void DisjointSets::setunion(int a, int b){
	int setA=find(a);
	int setB=find(b);
	/* Only union if sets differ */
	if(setA!=setB){
		/* The smaller uptree (less nodes) will point to
 		the larger. In case of equal size, tree containing
		second arg will point to tree containing the first */
		int temp;
		if(uptree[setA]<=uptree[setB]){
			temp=uptree[setB];
			uptree[setB]=setA;
			uptree[setA]+=temp;
		}else{
			temp=uptree[setA];
			uptree[setA]=setB;
			uptree[setB]+=temp;
		}
	}
}

