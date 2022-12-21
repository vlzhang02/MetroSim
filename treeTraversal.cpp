/*
 *  FSTreeTraversal.cpp
 *  April 9, 2022
 *
 *  COMP 15 Project 3: gerp
 *
 * Purpose: todo. helper function function for the gerp class that prints
 *          the paths to each file
 *
 */

#include "DirNode.h"
#include "FSTree.h"

#include <iostream>
#include <string>
using namespace std;

/*********************************************************************\
*                        function declarations                        *
\*********************************************************************/
void printFilepaths(DirNode *curr, string directoryPath);

/*********************************************************************\
*                                main                                 *
\*********************************************************************/
int main(int argc, char *argv[])
{
    if (argc != 2) { // make sure that commandline has a filename as well
        cerr << "Usage: ./treeTraversal Directory\n";
        exit(EXIT_FAILURE);
    }

    FSTree tree(argv[1]);
    printFilepaths(tree.getRoot(), "");

    return 0;
}


/*********************************************************************\
*                        function definitions                         *
\*********************************************************************/


/*            void printFilepaths(DirNode *curr, string directoryPath)
 * parameters:
 *  -   DirNode *curr is a pointer to a directory node may have files to
 *      print, and may have subdirectories
 *  -   string directoryPath represents a path leading to the curr(ent)
 *      directory node
 * purpose: to create a substring out of toParse where the
 * first and last characters are alphanumeric returns: a substring of
 * toParse
 */
void printFilepaths(DirNode *curr, string directoryPath)
{
    if (curr != nullptr) { // don't want to deref a nullptr

        directoryPath += curr->getName() + "/"; // add current dir to path

        if (curr->hasFiles()) { // if there are files, print them
            for (int i = 0; i < curr->numFiles(); i++) {
                cout << directoryPath << curr->getFile(i) << "\n";
            }
        }

        if (curr->hasSubDir()) { // if has subdirectories, traverse them
            for (int i = 0; i < curr->numSubDirs(); i++) {
                printFilepaths(curr->getSubDir(i), directoryPath);
            }
        }
    }
}