/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

#include <vector>
using namespace std;

class DisjointSets{
    public:
	//Creates 'num' unconnected root nodes, adds to end of uptree vector
    	void addelements(int num);
	//Searches for the uptree which contains elem, returning root index	
    	int find(int elem);
	//Combines uptrees if set indices differ
    	void setunion(int a, int b);
    private:
	//disjointSet ADT
    	vector<int> uptree;
};

#endif
