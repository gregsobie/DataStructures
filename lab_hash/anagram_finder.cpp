/**
 * @file anagram_finder.cpp
 * Implementation of the AnagramFinder class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "anagram_finder.h"

using std::string;
using std::vector;
using std::ofstream;
using std::endl;

/**
 * Constructs an AnagramFinder based on a filename to read potential
 * anagrams from.
 *
 * @param ifilename The name of the file to read in.
 */
template <template <class K, class V> class Dict>
AnagramFinder<Dict>::AnagramFinder(const string& ifilename)
    : file(true), filename(ifilename)
{
    /* nothing */
}

/**
 * Constructs an AnagramFinder based on a set of strings instead of a
 * filename.
 *
 * @param istrings The set of strings to use for this finder.
 */
template <template <class K, class V> class Dict>
AnagramFinder<Dict>::AnagramFinder(const vector<string>& istrings)
    : file(false), strings(istrings)
{
    /* nothing */
}

/**
 * Determines if the given word is an anagram of the test word.
 *
 * @param word Word that is possibly an anagram.
 * @param test Word to check against.
 * @return A boolean value indicating whether word is an anagram of test.
 */
template <template <class K, class V> class Dict>
bool AnagramFinder<Dict>::checkWord(const string& word, const string& test)
{
    /**
     * @todo Implement this function! You should use the provided
     * templated hashtable class Dict.
     */
	/* If the words contain a different number of letters,
	 * then they cannot be anagrams of each other */
	if(word.size() != test.size())
		return false;

	Dict<char,int> hashWord(256);
	Dict<char,int> hashTest(256);
	/* For each letter in word, update frequency */
	for(size_t i=0; i<word.size(); i++){
		hashWord[word[i]]++;
		hashTest[word[i]]++;
	}
	/* Check if frequencies match */
	auto itWord=hashWord.begin();
	auto itTest=hashTest.begin();
	while(itWord != hashWord.end() && itTest != hashTest.end()){
		if(itWord->first != itTest->first)
			return false;
		else if(itWord->second != itTest->second)
			return false;
		itWord++;
		itTest++;
	}
    	return true;
}

/**
 * Retrieves a set of words that are anagrams of a given word.
 *
 * @param word The word we wish to find anagrams of inside the finder.
 */
template <template <class K, class V> class Dict>
vector<string> AnagramFinder<Dict>::getAnagrams(const string& word)
{
    // set up the return vector
    vector<string> ret;

    if (file) {
        TextFile infile(filename);
        string line;
        vector<string> tests;
        while (infile.good()) {
            string test = infile.getNextWord();
            if (checkWord(word, test))
                ret.push_back(test);
        }
    } else {
        for (size_t i = 0; i < strings.size(); i++) {
            if (checkWord(word, strings[i]))
                ret.push_back(strings[i]);
        }
    }
    return ret;
}

/**
 * Retrieves a set of anagrams in the finder of a given words, but writes
 * them out to a file instead of returning a vector.
 *
 * @param word The word we wish to find anagrams of inside the finder.
 * @param output_file The name of the file we want to write to.
 */
template <template <class K, class V> class Dict>
void AnagramFinder<Dict>::writeAnagrams(const string& word,
                                        const string& output_file)
{
    vector<string> anagrams = getAnagrams(word);
    ofstream outfile(output_file.c_str());
    if (outfile.is_open()) {
        for (size_t i = 0; i < anagrams.size(); i++)
            outfile << anagrams[i] << endl;
    }
    outfile.close();
}
