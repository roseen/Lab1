//
//  duolist.h
//  Lab1
//
//  Created by Amanda Rosén on 2014-12-26.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#ifndef __Lab1__duolist__
#define __Lab1__duolist__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* This is a declaration of the structure for a node in the list */
typedef struct list{
    char* strdata;		 /* the string content */
    struct list* pnext;	 /* pointer to the next node in the list - reference to the same type, hence the name: self-referential struct */
    struct list* pprev;};	 /* pointer to the previous node in the list - reference to the same type, hence the name: self-referential struct */

typedef struct list StrList;     /* this is just an alias to struct lis*/
/* now it suffices to use "StrList" to denote the new type rather than "struct list"*/

/* This function adds a new node in the list with the content strdata = str */
void insertStr(StrList** pbegin,const char* str);

/* This function removes the node in the list that matches the argument string str */
void removeStr(StrList** pbegin,const char* str);

/* This function removes all the elements in the list and sets the pointer to the beginning of the network to NULL */
void removeAll(StrList** pbegin);

/* This function frees memory allocated earlier for the node in the list */
void freeNode(StrList** pnode);

/* This function returns 1 if the list is empty, 0 otherwise */
int isDuolistEmpty(StrList* pbegin);

/* This function prints out the list content */
void printStrList(StrList* ptr);


#endif /* defined(__Lab1__duolist__) */
