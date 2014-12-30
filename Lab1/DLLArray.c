//
//  DLLArray.c
//  Lab1
//
//  Created by Henrik Rosén on 2014-12-29.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "DLLArray.h"

int * initDLLArray() {
    int i;
    static StrList* beginPtr[26];
    for (i=0;i<26;i++) beginPtr[i] = NULL;
    return beginPtr;
}

/* This function adds a new node in the list with the content strdata = str */
void insertDLLArray(int* DLLArray,const char* str) {
    insertStr(&DLLArray[selectArray(str)],str);
}

/* This function removes the node in the list that matches the argument string str */
void removeDLLArray(int* DLLArray,const char* str) {
    removeStr(&DLLArray[selectArray(str)],str);
}

/* This function removes all the elements in the list and sets the pointer to the beginning of the network to NULL */
void removeAllDLLArray(int* DLLArray) {
    int i;
    for (i=0; i<26; i++) {
        removeAll(DLLArray[i]);
    }
}

int selectArray(const char* str) {
    int a = 'A';
    char c = toupper(str[0]);
    
    return c-a;
}
