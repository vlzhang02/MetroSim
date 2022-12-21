/*
 *  stringProcessing.cpp
 *  April 9, 2022
 *
 *  COMP 15 Project 3: gerp
 *
 * Purpose: todo. todo
 *
 */

#include "stringProcessing.h"
#include "DirNode.h"
#include "FSTree.h"
#include <iostream>


using namespace std;

/*********************************************************************\
*                        function definitions                         *
\*********************************************************************/

/*            string stripNonAlphaNum(string toParse)
 * parameters:
 *  - string toParse represents a string of varying character types
 * purpose: to create a substring out of toParse where the first and last
 *          characters are alphanumeric
 * returns: a substring of toParse
 */
string stripNonAlphaNum(string toParse)
{
    // have a loop to find the front
    int front = frontAlphaNum(toParse); // check in range
    int back  = backAlphaNum(toParse);  // check in range, length

    if ((front == -1) or (back == -1)) {
        return "";
    }

    string sub = toParse.substr(front, (back + 1) - front);

    return sub;
}


/*                int frontAlphaNum(string toParse)
 * parameters:
 *  - string toParse represents a string of varying character types
 * purpose: find the first alphanumeric char in a string
 * returns: the index of the first alphanumeric char
 */
int frontAlphaNum(string toParse)
{
    for (unsigned long i = 0; i < toParse.length(); i++) {
        if (isAlphaNum(toParse[i])) {
            return i;
        }
    }

    return -1;
}

/*                int backAlphaNum(string toParse)
 * parameters:
 *  - string toParse represents a string of varying character types
 * purpose: find the last alphanumeric char in a string
 * returns: the index of the last alphanumeric char
 */
int backAlphaNum(string toParse)
{
    for (int i = toParse.length() - 1; i > -1; i--) {
        if (isAlphaNum(toParse[i])) {
            return i;
        }
    }

    return -1;
}


/*                   bool isAlphaNum(char c)
 * parameters:
 *  - char c represents a char to check
 * purpose: determines if char c is or is not an alphabetical or
 * numerical character
 * returns: true if c is an alphanumeric character, false otherwise
 */
bool isAlphaNum(char c)
{
    if (((c > 47) and (c < 58)) or ((c > 64) and (c < 91)) or
        ((c > 96) and (c < 123))) {
        return true;
    }
    else {
        return false;
    }
}