/* CS 15 Proj3
 *
 * HashTable.h
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 14, 2022
 *
 * Purpose: The HashTable class stores a dictionary of words so that the
 *          file and line in which they were found can be quickly and
 *          easily accessed
 */

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

#include "DirNode.h"
#include "FSTree.h"
#include "stringProcessing.h"

using namespace std;
string stripNonAlphaNum(string toParse);

struct wordInstance {
    int    in_FileInfo;
    int    in_LineNum;
    string howFound;
};

struct wordEntry {
    string               keyWord = "EMPTY";
    vector<wordInstance> appearances;
};

static const int INITIAL_CAPACITY = 10000;

class HashTable {
public:
    /* constructor, destructor: */
    HashTable();
    ~HashTable();

    /* setter: */
    void parseLineAndAdd(string &line, int indexFile, int indexLine);
    
    /* getters: */
    wordEntry *getWordEntry(string &word);
    string     parseAndLower(string s);


private:
    int        capacity;
    int        numUniqueWords;
    wordEntry *table;

    /* adding functions */
    void add(string &s, int indexFile, int indexLine);
    void addNewWord(wordInstance word, string &key, int index);
    void addExistingWord(wordInstance word, int index);

    wordInstance newWordInstance(int fileIndex, int lineIndex, string &s);

    /* maintaining the hashtable */
    void expand();
    void loadFactorCheck();

    /* hash functions */
    int hashIndex(string &key);
    int linearProbeIndex(string &key, int index);
};

#endif