/* CS 15 Proj3
 *
 * Gerp.h
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 16, 2022
 *
 * Purpose: The Gerp class creates and maintains a dictionary of words that
 *          a user can query.
 */

#ifndef _GERP_H_
#define _GERP_H_

#include <fstream>
#include <functional>
#include <iostream>
#include <vector>


#include "DirNode.h"
#include "FSTree.h"
#include "FileInfo.h"
#include "HashTable.h"
#include "stringProcessing.h"


using namespace std;

class Gerp {
public:
    /* constructor, destructor: */
    Gerp();
    Gerp(DirNode *root, string filename);
    ~Gerp();


    void commandLoop(istream &input);

    /* print functions: */
    void printCaseInsensitive(ostream &output, string word);
    void printCaseSensitive(ostream &output, string word);

    /* reading in files: */
    bool openFile(ifstream &infile, string filePath);
    void readOneFile(ifstream &content, File &file, int fileIndex);


private:
    int       totalFiles;
    FileInfo  allFiles;
    HashTable hashtab;

    ofstream output;

    /* constructor helper functions */
    void constructorHelper(DirNode *curr, string dirPath);
    void openOfile(string &filename);

    /* print helper functions */
    bool printCaseInsensitiveHelper(ostream &output, string word);
    bool printCaseSensitiveHelper(ostream &output, string word);
};

#endif