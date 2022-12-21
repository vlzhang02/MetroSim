/*
 * FileInfo.h
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 10, 2022
 *
 * CS 15 Proj3
 * Purpose: The FileInfo class stores all of the files so that their lines
 *          and paths can be easily referenced.
 */

#ifndef _FILEINFO_H_
#define _FILEINFO_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "DirNode.h"
#include "FSTree.h"
#include "HashTable.h"

using namespace std;

struct File {
    string         filename;
    vector<string> lines; // note: 0th index stores file path
};

class FileInfo {
public:
    /* constructor, destructor: */
    FileInfo();
    ~FileInfo();

    /* setters: */
    bool openFile(ifstream &infile, string &filename);
    void addFile(File file);

    /* getters: */
    string getFilePath(int fileIndex);
    string getLine(int fileIndex, int lineNum);

private:
    vector<File> files;
};

#endif