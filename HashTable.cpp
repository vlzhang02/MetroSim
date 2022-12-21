/* CS 15 Proj3
 *
 * FileInfo.cpp
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 14, 2022
 *
 * Purpose: The HashTable class stores a dictionary of words so that the
 *          file and line in which they were found can be quickly and
 *          easily accessed
 */

#include "HashTable.h"
#include "stringProcessing.h"

using namespace std;

/** *****************************************************************\
*                      constructor and destructor                    *
\********************************************************************/
/*                         default constructor
 * parameters: none
 * purpose: initializes member variables for the hashtable class
 * returns: n/a
 */
HashTable::HashTable()
{
    capacity = INITIAL_CAPACITY;

    table          = new wordEntry[capacity]; // table is a pointer
    numUniqueWords = 0;
}

/*                            destructor
 * parameters: none
 * purpose: clear all space in the heap associated with a hashtable
 * returns: n/a
 */
HashTable::~HashTable()
{
    delete[] table;
    table          = nullptr;
    numUniqueWords = 0;
}
/** *****************************************************************\
*                              setters                               *
\********************************************************************/
/*    void parseLineAndAdd(string &line, int indexFile, int indexLine)
 * parameters:
 *  -   string &line is a line obtained from a file
 *  -   int indexFile represents in what file the line was found
 *  -   int indexLine represents the line number where the line was found
 * purpose: to add all words from a line of a file to a hashtable
 * returns: n/a
 */
void HashTable::parseLineAndAdd(string &line, int indexFile, int indexLine)
{
    stringstream ss;
    ss << line;

    string word;
    while (ss >> word) { // get word
        // add to hashtable
        add(word, indexFile, indexLine);
    }
}

/** *****************************************************************\
*                          adding functions                          *
\********************************************************************/
/*        void add(string &s, int indexFile, int indexLine)
 * parameters:
 *  -   string &s is an instance of a word
 *  -   int indexFile represents in what file the word was found
 *  -   int indexLine represents the line number where the word was found
 * purpose: to add (using helper functions)
 * returns: n/a
 */
void HashTable::add(string &s, int indexFile, int indexLine)
{
    loadFactorCheck();
    // initialize new word instance
    string key = parseAndLower(s);
    if (key.length() != 0) {
        wordInstance word  = newWordInstance(indexFile, indexLine, s);
        int          index = linearProbeIndex(key, hashIndex(key));

        if (table[index].keyWord == "EMPTY") {
            addNewWord(word, key, index);
        }
        else { // table[index].keyWord == key
            addExistingWord(word, index);
        }
    }
}

/*     void addExistingWord(wordInstance word, string key, int index)
 * parameters:
 *  -   string &s is an instance of a word
 *  -   int indexFile represents in what file the word was found
 *  -   int indexLine represents the line number where the word was found
 * purpose: adds word that has been seen before to the existing word entry
 * returns: n/a
 */
void HashTable::addExistingWord(wordInstance word, int index)
{
    (table[index].appearances).push_back(word);
}

/*       void addNewWord(wordInstance word, string key, int index)
 * parameters:
 *  -   string &s is an instance of a word
 *  -   int indexFile represents in what file the word was found
 *  -   int indexLine represents the line number where the word was found
 * purpose: adds a not-yet-seen word to the hashtable
 * returns: n/a
 */
void HashTable::addNewWord(wordInstance word, string &key, int index)
{
    // change empty to key
    table[index].keyWord = key;

    // add word instance to instances
    (table[index].appearances).push_back(word);
    numUniqueWords++;
}

/*   wordInstance newWordInstance(int fileIndex, int lineIndex, string &s)
 * parameters:
 *  -   int fileIndex represents which file the string was found in
 *  -   int lineIndex represents what line of the file the string was found
 *  -   string &s is the string as it appears in the file
 * purpose: creates a word instance for a string
 * returns: the initialized word instance
 */
wordInstance HashTable::newWordInstance(int fileIndex, int lineIndex,
                                        string &s)
{
    wordInstance WI;
    WI.in_FileInfo = fileIndex;
    WI.in_LineNum  = lineIndex;
    WI.howFound    = s;
    return WI;
}


/** *****************************************************************\
*                   hashtable maintaining functions                  *
\********************************************************************/
/*                           void expand()
 * parameters: none
 * purpose: expands the capacity and rehashes all words
 * returns: n/a
 */
void HashTable::expand()
{
    int        oldCapacity = capacity;
    wordEntry *oldTable    = table; // save old table to delete it

    capacity = 2 * capacity + 2;        // update capacity
    table    = new wordEntry[capacity]; // create new table

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].keyWord != "EMPTY") { // if keywrd empty: continue,
            wordEntry curr = oldTable[i]; // else, make copy of word entry,
            string    key  = curr.keyWord; // & put into new table

            // linear probe index uses new table
            table[linearProbeIndex(key, hashIndex(key))] = curr;
        }
    }

    delete[] oldTable; // after, delete old array
}

/*                           void loadFactorCheck()
 * parameters: none
 * purpose: checks the load factor and rehashes if necessary
 * returns: n/a
 */
void HashTable::loadFactorCheck()
{
    float c  = capacity * 1.0;
    float nw = numUniqueWords * 1.0;
    if (nw / c > .7) {
        expand();
    }
}

/** *****************************************************************\
*                              getters                               *
\********************************************************************/
/*           wordEntry *getWordEntry(string &word)
 * parameters:
 *  -   string &word is a word that may be in the hashtable
 * purpose: access the wordEntry for the specific word
 * returns: a pointer to the wordEntry containing all instances of the word
 */
wordEntry *HashTable::getWordEntry(string &word)
{
    string key   = parseAndLower(word);
    int    index = linearProbeIndex(key, hashIndex(key));

    if (table[index].keyWord != key) { // empty
        return nullptr;
    }

    return &(table[index]); // ptr to first element
}

/*                  string parseAndLower(string s)
 * parameters:
 *  -   string s represents the original instance of a string
 * purpose: to find the key of a certain string.
 * returns: the string parsed and with lowercase letters
 */
string HashTable::parseAndLower(string s)
{
    s = stripNonAlphaNum(s);

    for (unsigned long i = 0; i < s.length(); i++) {
        if ((s[i] > 64) and (s[i] < 91)) {
            s[i] = tolower(s[i]);
        }
    }

    return s;
}
/** *****************************************************************\
*                           hash functions                           *
\********************************************************************/
/*             int linearProbeIndex(string &key, int index)
 * parameters:
 *  -   int index represents the original hash index for a key
 *  -   string &key is a key to find the index for
 * purpose: to find the correct index for a key using linear probing
 * returns: an integer representing the key's index
 */
int HashTable::linearProbeIndex(string &key, int index)
{
    int  attempt = 0;
    bool found   = false;

    while (not found) {
        index = (index + attempt) % capacity;
        if (table[index].keyWord == "EMPTY") {
            return index;
        }
        else if (table[index].keyWord == key) {
            return index;
        }
        attempt++;
    }
    return 0;
}

/*                        int hashIndex(string &key)
 * parameters:
 *  -   string &key is a key to find an index for
 * purpose: calls the hash function on the key, then mods it to get an
 *          index
 * returns: the index corresponding to the key
 */
int HashTable::hashIndex(string &key)
{
    // first get hash value for key
    // then mod by capacity to get index
    return (hash<string>{}(key) % capacity);
}