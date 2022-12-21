/*
 *  todo.cpp
 *  April 9, 2022
 *
 *  COMP 15 Project 3: gerp
 *
 * Purpose: todo. todo
 *
 */

#ifndef STRING_PROCESSING_H
#define STRING_PROCESSING_H

#include "DirNode.h"
#include "FSTree.h"

#include <iostream>
#include <string>


using namespace std;

/*********************************************************************\
*                        function declarations                        *
\*********************************************************************/

string stripNonAlphaNum(string toParse);
int    frontAlphaNum(string toParse);
int    backAlphaNum(string toParse);
bool   isAlphaNum(char c);


#endif