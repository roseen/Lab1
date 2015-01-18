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
    char output2file[]="/Users/Henrik/Documents/Lab1/Lab1/outputfile.txt";
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
    StrList* listDoubleLinkedBegin[26];//Pointer to Arrays with 26 slots, for begin pointers.
    StrList* listDoubleLinkedEnd[26]; //Pointer to Arrays with 26 slots, for end pointers.
    for (i=0; i<26; i++) {
        listDoubleLinkedBegin[i] = NULL;
        listDoubleLinkedEnd[i] = NULL;
    }
    for (i=0; i<nOfWords; i++) insertStr(&listDoubleLinkedBegin[selectArray(arrayImportantWords[i])],&listDoubleLinkedEnd[selectArray(arrayImportantWords[i])],arrayImportantWords[i]);
    
    /********* Test to Search for a String */
    StrList* word;
    char *searchWords[2] = {"rere", "rare"};
    for (i=0; i<2; i++) {
        printf("Trying to search for word %s.\n",searchWords[i]);
        word = searchStr(&listDoubleLinkedBegin[selectArray(searchWords[i])],searchWords[i]);
        if (word!=NULL) {
            printf("Found string %s.\n",word->strdata);
        }
        else {
            printf("Did not find string %s.\n",searchWords[i]);
        }
    }

    /********* Test to remove Strings */
    char *removeWords[3] = {"vhis", "vn", "vn"};
    for (i=0; i<3; i++) {
        printf("Trying to remove word %s.\n",removeWords[i]);
        j= selectArray(removeWords[i]); /* Find what array to use */
        printStrList(listDoubleLinkedBegin[j]); /* Print the list before */
        removeStr(&listDoubleLinkedBegin[j],&listDoubleLinkedEnd[j],removeWords[i]); /* Try to remove from list */
        printStrList(listDoubleLinkedBegin[j]); /* Print the list after */
    }

    /********* Export to file */
    FILE *f = fopen(output2file , "w");
    int count=0;
    if (f == NULL)
    {
        printf("Error opening file!\n");
    }
    else {
        for (i=0; i<26; i++) {
            if (listDoubleLinkedBegin[i] != NULL) { /* Check if list is Empty or not */
                count = count + printStrList2File(f,listDoubleLinkedBegin[i]);
            }
        }
        fclose(f);
        printf("%d words written to file\n",count);
    }
    
    /********* Print to screen */
    char *printLetters[2] = {"c", "s"};
    for (i=0; i<2; i++) {
        j= selectArray(printLetters[i]); /* Find what array to use */
        printStrList(listDoubleLinkedBegin[j]); /* Print the list */
       
    }
    /********* Print second and second last */
    for (i=0; i<26; i++) {
        print2ndFirstnLast(listDoubleLinkedBegin[i], listDoubleLinkedEnd[i]);
    }
    
    /********* Clean up */
    free(arrayImportantWords);
    deleteStack(stackNonImportantWords);
}