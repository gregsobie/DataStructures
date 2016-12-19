#include <iostream>
#include <vector>
#include <set>
using namespace std;

int find(vector<int> &uptree, int index)
{
    // Your code here!
	/* Base case -- if vector value is index, element is a root */
	if(uptree[index]==index)
		return index;
	/* Else recursively find the root index for the set to which element belongs */
	uptree[index]=find(uptree, uptree[index]);
	 
    
    return -1;
}

