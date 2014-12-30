//
//  DLLArray.h
//  Lab1
//
//  Created by Henrik Rosén on 2014-12-29.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#ifndef __Lab1__DLLArray__
#define __Lab1__DLLArray__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "duolist.h"

#endif /* defined(__Lab1__DLLArray__) */

int * initDLLArray();

/* This function adds a new node in the list with the content strdata = str */
void insertDLLArray(int* DLLArray,const char* str);

/* This function removes the node in the list that matches the argument string str */
void removeDLLArray(int* DLLArray,const char* str);

/* This function removes all the elements in the list and sets the pointer to the beginning of the network to NULL */
void removeAllDLLArray(int* DLLArray);

int selectArray(const char* str);