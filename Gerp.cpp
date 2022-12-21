/* CS 15 Proj3
 *
 * Gerp.cpp
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 16, 2022
 *
 * Purpose: The Gerp class creates and maintains a dictionary of words that
 *          a user can query.
 */

#include "gerp.h"

using namespace std;

/** *****************************************************************\
*                      constructor and destructor                    *
\********************************************************************/
/*                         default constructor
 * parameters: none
 * purpose: initializes an empty gerp instance
 * returns: n/a
 */
Gerp::Gerp()
{
    totalFiles = 0;
}

/*                         secondary constructor
 * parameters: none
 * purpose: initializes a gerp instance from a FSTree and an output file
 * returns: n/a
 */
Gerp::Gerp(DirNode *root, string filename)
{
    totalFiles = 0;
    openOfile(filename);
    constructorHelper(root, "");
}

/*                              destructor
 * parameters: none
 * purpose: clear all memory associated with a fileinfo class instance
 * returns: n/a
 */
Gerp::~Gerp()
{
    output.close();
}

/** *****************************************************************\
*                    constructor helper functions                    *
\********************************************************************/
/*                         constructor helper
 * parameters:
 *  -   DirNode *curr is a node containing files
 *  -   string dirPath represents the path to the directory
 * purpose: recursively reads in all info from files into a hashmap.
 * returns: n/a
 */
void Gerp::constructorHelper(DirNode *curr, string dirPath)
{
    if (curr != nullptr) {
        dirPath += curr->getName() + "/";

        if (curr->hasFiles()) { // if there are files, open and read them
                                // in to the vector
            for (int i = 0; i < curr->numFiles(); i++) {

                File newFile; // create and initialize file struct for
                newFile.filename = curr->getFile(i); // this file
                (newFile.lines).push_back(dirPath);

                // open file and read in all the lines to vector in struct
                ifstream content;
                if (openFile(content, dirPath + newFile.filename)) {
                    readOneFile(content, newFile, totalFiles);
                    content.close(); // close file
                }
                allFiles.addFile(newFile); // push the file onto the vector
            }
        }
        if (curr->hasSubDir()) { // if has subdirectories, traverse them
            for (int i = 0; i < curr->numSubDirs(); i++) {
                constructorHelper(curr->getSubDir(i), dirPath);
            }
        }
    }
}
/*                      void openOfile(string &filename)
 * parameters:
 *  -   string filename is the name of a file to open
 * purpose:
 *  -   to open a new output file to read query results to
 * returns: n/a
 */
void Gerp::openOfile(string &filename)
{
    if (output.is_open()) {
        output.close();
    }
    output.open(filename);
    if (not output.is_open()) {
        cerr << "Error: could not open file " << filename << "\n";
    }
}

/** *****************************************************************\
*                    constructor helper functions                    *
\********************************************************************/
/*      void readOneFile(ifstream &content, File &file, int fileIndex)
 * parameters:
 *  -   ifstream &content represents a filestream
 *  -   File &file represents a file instance to update with lines from the
 * file
 *  -   int fileIndex represents a
 * purpose: reads one file into the hashtable and the fileinfo instances
 * returns: n/a
 */
void Gerp::readOneFile(ifstream &content, File &file, int fileIndex)
{
    // Logic - for each line of a file:
    // read into fileinfo class, parse and add to hashtable

    int    lineNum = 1; // var to keep track of line #
    string oneLine;     // var to keep track of whole line

    while (getline(content, oneLine)) { // will stop if getline fails (EOF)

        (file.lines).push_back(oneLine); // update fileInfo instance and
        hashtab.parseLineAndAdd(oneLine, fileIndex, lineNum); // hashtable

        lineNum++;
    }

    totalFiles++;
}


/*           bool openFile(ifstream &infile, string filePath)
 * parameters:
 *  -   ifstream &infile is a filestream
 *  -   string filePath is the file to open
 * purpose: to open a file to a filestream
 * returns: true if file was opened, false if there was an error
 */
bool Gerp::openFile(ifstream &infile, string filePath)
{
    infile.open(filePath);
    if (not infile.is_open()) {
        cerr << "Error: could not open file " << filePath << "\n";
        return false;
    }
    return true;
}


/** *****************************************************************\
*                         printing functions                         *
\********************************************************************/
/*         void printCaseInsensitive(ostream &output, string word)
 * parameters:
 *  -   ostream &output is a stream to pring the output to
 *  -   string word represents a word to query the hashtable for
 * purpose: to print all lines containing a word to an output file
 * returns: n/a
 */
void Gerp::printCaseInsensitive(ostream &output, string word)
{
    word = stripNonAlphaNum(word);
    if ((word.length() == 0) or
        (not printCaseInsensitiveHelper(output, word))) {
        output << word << " Not Found.\n";
    }
}

/*         void printCaseSensitive(ostream &output, string word)
 * parameters:
 *  -   ostream &output is a stream to pring the output to
 *  -   string word represents a word to query the hashtable for
 * purpose: to print all lines containing a word to an output file
 * returns: n/a
 */
void Gerp::printCaseSensitive(ostream &output, string word)
{
    word = stripNonAlphaNum(word);

    if ((word.length() == 0) or
        (not printCaseSensitiveHelper(output, word))) {
        output << word << " Not Found. Try with @insensitive or @i.\n";
    }
}

/** *****************************************************************\
*                      printing helper functions                     *
\********************************************************************/
/*       bool printCaseInsensitiveHelper(ostream &output, string word)
 * parameters:
 *  -   ostream &output is a stream to pring the output to
 *  -   string word represents a word to query the hashtable for
 * purpose: to find all instances of the word and print them
 * returns: true if the word existed in the hashtable, false if it wasnt
 *          printed
 */
bool Gerp::printCaseInsensitiveHelper(ostream &output, string word)
{
    wordEntry *entry = hashtab.getWordEntry(word); // all intances of word
    if ((entry == nullptr) or (word.length() == 0)) { // word not in table
        return false;
    }

    bool didPrint  = false; // keep track of if fxn printed
    int  currFile  = -1; // variables to prevent a line from being printed
    int  currIndex = -1; // multiple times

    for (size_t i = 0; i < entry->appearances.size(); i++) {
        // check that file and line aren't the same as the previous print
        if ((entry->appearances[i].in_FileInfo != currFile) or
            (entry->appearances[i].in_LineNum != currIndex)) {

            currFile  = entry->appearances[i].in_FileInfo;
            currIndex = entry->appearances[i].in_LineNum;

            output << allFiles.getFilePath(currFile)        // file path
                   << ":" << currIndex << ": "              // line num
                   << allFiles.getLine(currFile, currIndex) // line
                   << "\n";

            didPrint = true;
        }
    }
    return didPrint;
}

/*         bool printCaseSensitiveHelper(ostream &output, string word)
 * parameters:
 *  -   ostream &output is a stream to pring the output to
 *  -   string word represents a word to query the hashtable for
 * purpose: to find all instances of the word and print them
 * returns: true if the word existed in the hashtable, false if it wasnt
 *          printed
 */
bool Gerp::printCaseSensitiveHelper(ostream &output, string word)
{
    wordEntry *entry = hashtab.getWordEntry(word); // all intances of word
    if (entry == nullptr) {                        // word not in hashtable
        return false;
    }

    bool didPrint  = false; // keep track of if fxn printed
    int  currFile  = -1; // variables to prevent a line from being printed
    int  currIndex = -1; // multiple times

    for (size_t i = 0; i < entry->appearances.size(); i++) {
        // check case sensitive
        if (stripNonAlphaNum(entry->appearances[i].howFound) == word) {
            // check that file and line aren't the same as the last print:
            if ((entry->appearances[i].in_FileInfo != currFile) or
                (entry->appearances[i].in_LineNum != currIndex)) {

                currFile  = entry->appearances[i].in_FileInfo;
                currIndex = entry->appearances[i].in_LineNum;

                output << allFiles.getFilePath(currFile) // file path
                       << ":" << currIndex << ": "       // line num
                       << allFiles.getLine(currFile, currIndex) << "\n";
                didPrint = true;
            }
        }
    }
    return didPrint;
}


/*                    void commandLoop(istream &input)
 * parameters:
 *  -   istream &input is an input stream to recieve commands from
 * purpose: to
 * returns: n/a
 */
void Gerp::commandLoop(istream &input)
{
    std::string command = "";
    cout << "Query? ";

    while (not(input >> command).fail()) {
        if ((command == "@i") or (command == "@insensitive")) {
            string anyString;
            cin >> anyString;
            printCaseInsensitive(output, anyString);
        }
        else if (command == "@f") {
            string newOutputFilename;
            cin >> newOutputFilename;
            openOfile(newOutputFilename);
        }
        else if ((command == "@q") or (command == "@quit")) {
            return;
        }
        else { // treat input as a query
            string anyString = command;
            printCaseSensitive(output, anyString);
        }
        if (input.peek() == EOF) {
            return;
        }
        cout << "Query? ";
    }
}