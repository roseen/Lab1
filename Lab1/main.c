//
//  main.c
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-17.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include <stdio.h>
#include "countwords.h"
#include "removelastCR.h"
#include "array.h"
#include "stack.h"
#include "filterWords.h"
#include "duolist.h"
#include "DLLArray.h"


int main()
{
    char wordsfile[]="/Users/Henrik/Documents/Lab1/Lab1/originalwords.txt";
    char unimportantwords[]="/Users/Henrik/Documents/Lab1/Lab1/unimportantwords.txt";
    int nOfWords;
    int nOfNonImportant;
    int i,j;

    
    /********* Load inital array and stack */
    
    //Add original words to array. http://www.lysator.liu.se/c/c-faq/c-2.html
    nOfWords=countwords(wordsfile);
    char (*arrayImportantWords)[60];
    arrayImportantWords=(char(*)[60])malloc(nOfWords*60*sizeof(char));
    addWords2Array(wordsfile,arrayImportantWords,nOfWords);
    
    //Add unimportant words to stack.
    nOfNonImportant=countwords(unimportantwords);
    StackAddress stackNonImportantWords;
    stackNonImportantWords.ptop = NULL;	/* both pointers are initialised and set to NULL - there is no Stack yet*/
    stackNonImportantWords = addWordsToStack(unimportantwords,stackNonImportantWords,nOfNonImportant);
    
    //Print array and stack
    printArray(arrayImportantWords, nOfWords);
    printStack(stackNonImportantWords);
    
    /********* Filter words and updates the length of the array. */
    nOfWords=filterWords(arrayImportantWords,stackNonImportantWords,nOfWords);
    
    //Print array.
    printArray(arrayImportantWords, nOfWords);

    
    /********* Create a Double Linked List and load it with all Important Words */

    StrList* listDoubleLinked[26]; //Pointer to Array with 26 slots
    for (i=0; i<26; i++) listDoubleLinked[i] = NULL;
    for (i=0; i<nOfWords; i++) insertStr(&listDoubleLinked[selectArray(arrayImportantWords[i])],arrayImportantWords[i]);
    
    //Print array.
    printArray(arrayImportantWords, nOfWords);
    
    /********* Test to Search for a String */

    StrList* word;
    char *searchWords[2] = {"rere", "rare"};
    for (i=0; i<2; i++) {
        printf("Trying word %s.\n",searchWords[i]);
        word = searchStr(&listDoubleLinked[selectArray(searchWords[i])],searchWords[i]);
        if (word!=NULL) {
            printf("Found string %s.\n",word->strdata);
        }
        else {
            printf("Did not find string %s.\n",searchWords[i]);
        }
    }

    /********* Test to remove Strings */
    char *removeWords[2] = {"vhis", "vn"};
    for (i=0; i<2; i++) {
        printf("Trying to remove word %s.\n",removeWords[i]);
        j= selectArray(removeWords[i]);
        printStrList(listDoubleLinked[j]);
        removeStr(&listDoubleLinked[j],removeWords[i]);
        printStrList(listDoubleLinked[j]);
    }

    
    free(arrayImportantWords);
    deleteStack(stackNonImportantWords);
}