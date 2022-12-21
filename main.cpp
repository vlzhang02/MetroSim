/* CS 15 Proj3 - GERP
 *
 * main.cpp
 * Authors: Valerie Zhang, Charlotte Versavel
 * April 16, 2022
 *
 * Purpose: Runs Gerp - a program that queries files in a specified
 *          directory for a word, and saves results of the query to an
 *          output file.
 *
 *  Notes: see README for more details
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "gerp.h"

using namespace std;

/********************************************************************\
*                                Main                                *
\********************************************************************/
int main(int argc, char *argv[])
{
    if (not(argc == 3)) { // check correct number of commandline arguments
        cerr << "Usage: gerp directory output_file\n";
        exit(EXIT_FAILURE);
    }

    FSTree fileTree(argv[1]); // initialize a filetree from a directory

    Gerp g(fileTree.getRoot(), argv[2]); // create a gerp from the filetree

    g.commandLoop(cin); // allow user to query

    cout << "Goodbye! Thank you and have a nice day.\n"; // end program
    return 0;
}