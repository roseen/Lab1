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
    //Add original words to array.
    int N1=countwords("/Users/Henrik/Documents/Lab1/Lab1/originalwords.txt");
    char (*array_importantwords)[60];
    array_importantwords=(char(*)[60])malloc(N1*60*sizeof(char));
    addWords2Array("/Users/Henrik/Documents/Lab1/Lab1/originalwords.txt",array_importantwords,N1);
    //Add unimportant words to stack.
    int N2=countwords("/Users/Henrik/Documents/Lab1/Lab1/unimportantwords.txt");
    StackAddress strStack;
    strStack.ptop = NULL;	/* both pointers are initialised and set to NULL - there is no Stack yet*/
    strStack = addWordsToStack("/Users/Henrik/Documents/Lab1/Lab1/unimportantwords.txt",strStack,N2);
    
    //Print array.
    int i,j;
    for (i=0;i<N1;i++) {
        printf("%s\n",array_importantwords[i]);
    }
    printf("%d\n",N1);

    //Print stack.
    printStrStack(strStack);
    printf("%d\n",N2);
    
    //Filter words and updates the length of the array.
    N1=filterWords(array_importantwords,strStack,N1);
    
    for (i=0;i<N1;i++) {
        printf("%s\n",array_importantwords[i]);
    }
    printf("%d\n",N1);
    
    
    /* Try DLL */
//    StrList* beginPtr = NULL;
//    for (i=0; i<N1; i++) {
//        insertStr(&beginPtr,array_importantwords[i]);
//    }
//    printStrList(beginPtr);

    /* Try DLL */
    StrList* beginPtr[26];
    for (i=0; i<26; i++) {
        beginPtr[i] = NULL;
    }
    for (i=0; i<N1; i++) {
        j= selectArray(array_importantwords[i]);
        insertStr(&beginPtr[j],array_importantwords[i]);
    }
    for (i=0; i<26; i++) {
        printStrList(beginPtr[i]);
    }
    
    /* Test Search String */
    char *str1="rere";
    char *str2="rare";
    StrList* word;
    
    j= selectArray(str1);
    word = searchStr(&beginPtr[j],str1);
    if (word!=NULL) {
        printf("Found string %s.\n",word->strdata);
    }
    else {
        printf("Found string %s.\n",str1);
    }
 
    j= selectArray(str2);
    word = searchStr(&beginPtr[j],str2);
    if (word!=NULL) {
        printf("Found string %s.\n",word->strdata);
    }
    else {
        printf("NOT found string %s.\n",str2);
    }
    
    /* Test of remove */
     char *str3="vhis";
     char *str4="vn";
     
     j= selectArray(str3);
    printStrList(beginPtr[j]);
     removeStr(&beginPtr[j],str3);
    printStrList(beginPtr[j]);

    j= selectArray(str4);
    removeStr(&beginPtr[j],str4);
    printStrList(beginPtr[j]);
    
    
    free(array_importantwords);
    deleteStack(strStack);
}