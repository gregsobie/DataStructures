/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
	/* Map for common words */
	std::map<string, unsigned int> m;
	/* For each word in the line */
	for(size_t j=0; j<words.size(); j++)
		/* Increment value if we have seen this key already */
		m[words[j]]++;
	/* Update word map */
	file_word_maps[i]=m;
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
	/* For each file */
	for(size_t i=0; i<file_word_maps.size(); i++){
		/* For each key in current file */
		for(auto& key_val : file_word_maps[i])
			/* Increment if key seen in current file */
			common[key_val.first]++;
	}
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
	/* Number of times word has appeared in file
	 * with frequency of occurance >= n */
	int counter;
	/* For each key in common */
	for(auto& common_key : common){
		/* Reset counter for next key */
		counter=0;
		/* If key is in every file */
		if(common_key.second == file_word_maps.size()){
			/* For every file */
			for(size_t i=0; i<file_word_maps.size(); i++){
				/* Findd ffrequency of key's occurance in current file */
				auto iterator = file_word_maps[i].find(common_key.first);
				if(iterator!=file_word_maps[i].end()){
					/* If frequency is greater than n */
					if(iterator->second >= n){
						counter+=1;
						/* If frequency is greater than n for all files */
						if(counter==(int)(file_word_maps.size()))
							out.push_back(common_key.first);
					}
				}
			}
		}
	}
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
