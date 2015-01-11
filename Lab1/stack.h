//
//  stack.h
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-20.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#ifndef __LaborationEtt__stack__
#define __LaborationEtt__stack__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* declaration of a Stack structure  */
typedef struct Stack {
    char* strdata;		 /* the string content */
    struct Stack* pnext;};	 /* pointer to the next node in the Stack - reference to the same type, hence the name: self-referential struct */

typedef struct Stack StrStack;     /* this is just an alias to struct Stack*/
/* now it suffices to use "StrStack" to denote the new type rather than "struct Stack"*/

/* declaration of a structure of pointer to the Stack*/
/* this is just a neat way to keep this pointer under the same structure, otherwise we could just have one independent pointer variable - ptop */
typedef struct Stack_address {
    StrStack* ptop;	 /* pointer to the beginning of the Stack */
};

typedef struct Stack_address StackAddress;     /* this is just an alias to struct Stack_address*/


/* This function adds a new node to the end of the Stack with the content strdata = str */
StackAddress Push(StackAddress ptr,const char* str);

/* This function removes the node from the beginning of the Stack, frees memory and assigns the string value to the argument string str */
/* IMPORTANT: It is assumed that memory has been allocated to str outside the function*/
StackAddress Pop(StackAddress ptr,char* str);

/* This function returns 1 if the Stack is empty, 0 otherwise */
int isStackEmpty(StackAddress ptr);

/* Returns 1 if word exists, 0 otherwise */
int exists(StackAddress ptr, const char* str);

/* This function prints out the Stack content */
void printStack(StackAddress ptr);

/* This function deletes or rather frees memory allocated for the entire Stack, including memory for fields .strdata */
StackAddress deleteStack(StackAddress ptr);

StackAddress addWordsToStack(char* filename,StackAddress strStack,int N2);

#endif /* defined(__LaborationEtt__stack__) */
