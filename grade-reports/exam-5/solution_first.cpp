#include <iostream>
#include <set>
#include <string>

using namespace std;

/* STL Sets have several methods you may (or may not) need:
 *
 * begin() -- return iterator from beginning
 * count(x) -- return number of instances of x in the set (will be 0 or 1)
 * insert(x) -- insert an element x into the set
 * erase(x) -- remove an element x from the set
 * empty() -- test if the set is empty
 * size() -- return number of elements in set
 */

set<string> findNeighbors(string curr,  set<string>& wordList)
{
    set<string> neighbors;
    int N = curr.size();
    for(int i = 0; i < N; i++)
    {
        for(char c = 'a'; c <= 'z'; c++)
        {
            if(c == curr[i])
                continue;
            string oneChange = curr.substr(0,i) + (c) + curr.substr(i+1);
            if(wordList.count(oneChange))
            {
                neighbors.insert(oneChange);
                wordList.erase(oneChange);
            }
        }
    }
    return neighbors;
}

int sequenceLength(string beginWord, string endWord, set<string>& wordList) {

    // YOUR CODE HERE!
	set<string> sequence;
	string cur=beginWord;
	sequence.insert(cur);
	int count=0;
	string prev;

	// While there are more sequences to check
	while(!sequence.empty() && cur!=endWord){
		//findNeighbors(cur, wordList);
		// If there are more possible transformations
		if(findNeighbors(cur, wordList).size()>0){
			prev=cur;
			//cur=*(findNeighbors(cur, wordList).begin());
			sequence.insert(cur);
			wordList.erase(cur);
			count++;
		}else{
			sequence.erase(cur);
			wordList.insert(cur);
			cur=prev;
			count--;
		}
	}

	if(cur==endWord)
		return sequence.size();
	else if(sequence.empty()) 	
		return 0;
	else 	return 0;
}
