/*
 * FileInfo.cpp
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 10, 2022
 *
 * CS 15 Proj3
 * Purpose: The FileInfo class stores all of the files so that their paths
 *          and lines can be easily referenced.
 */

#include "FileInfo.h"

/** *****************************************************************\
*                      constructor and destructor                    *
\********************************************************************/
/*                          default constructor
 * parameters: none
 * purpose: initializes the FileInfo instance
 * returns: n/a
 */
FileInfo::FileInfo() {}

/*                              destructor
 * parameters: none
 * purpose: clear all memory associated with a fileinfo class instance
 * returns: n/a
 */
FileInfo::~FileInfo()
{
    for (unsigned long i = 0; i < files.size(); i++) {
        files[i].lines.clear();
    }

    files.clear();
}

/** *****************************************************************\
*                              setters                               *
\********************************************************************/
/*            bool openFile(ifstream &infile, string &filePath)
 * parameters:
 *  -   ifstream &infile is a filestream to open the file to
 *  -   string &filePath is the path of the file to open
 * purpose: to open the specified file
 * returns: true if the file was opened, false otherwise
 */
bool FileInfo::openFile(ifstream &infile, string &filePath)
{
    infile.open(filePath);
    if (not infile.is_open()) {
        cerr << "Error: could not open file " << filePath << "\n";
        return false;
    }
    return true;
}
/*                       void addFile(File file)
 * parameters:
 *  -   File file represents a file to add to the vector of files
 * purpose: adds a file to the FileInfo vector
 * returns: n/a
 */
void FileInfo::addFile(File file)
{
    files.push_back(file);
}

/** *****************************************************************\
*                              getters                               *
\********************************************************************/
/*                  string getFilePath(int fileIndex)
 * parameters:
 *  -   int fileIndex represents the index of the file to find a path for
 * purpose: to obtain the file's path for a specific file
 * returns: a string containing the path to a file
 */
string FileInfo::getFilePath(int fileIndex)
{
    return files[fileIndex].lines[0] + files[fileIndex].filename;
}
/*              string getLine(int fileIndex, int lineNum)
 * parameters:
 *  -   int fileIndex represents the file to get a line from
 *  -   int lineNum represents which line to reference
 * purpose: a getter function to obtain a line from a specific file
 * returns: a string containing a certain line in the file
 */
string FileInfo::getLine(int fileIndex, int lineNum)
{
    return files[fileIndex].lines[lineNum];
}