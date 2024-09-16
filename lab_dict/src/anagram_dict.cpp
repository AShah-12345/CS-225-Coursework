/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream file(filename);
        if (file.is_open())
        {
            char c;
            string word;
            while (file.get(c)) 
            {
                if (c == '\n') 
                {
                    string sorted = word;
                    sort(sorted.begin(), sorted.end());
                    dict[sorted].push_back(word);
                    word.clear();
                } 
                else 
                {
                    word += c;
                }
            }
            if (!word.empty()) 
            {
                string sorted = word;
                sort(sorted.begin(), sorted.end());
                dict[sorted].push_back(word);
            }
            file.close();
        }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (const string& word : words) 
    {
            string sorted = word;
            sort(sorted.begin(), sorted.end());
            dict[sorted].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted = word;
    sort(sorted.begin(), sorted.end());
    auto key = dict.find(sorted);
    if (key != dict.end()) 
    {
        return key->second;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all;
    for (const auto& match : dict) 
    {
        const vector<string>& anagrams = match.second;
        if (anagrams.size() >= 2) 
        {
            all.push_back(anagrams);
        }
    }
    return all;
}
