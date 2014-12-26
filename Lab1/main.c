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


int main()
{
    //Add original words to array.
    int N1=countwords("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/originalwords.txt");
    char (*array_importantwords)[60];
    array_importantwords=(char(*)[60])malloc(N1*60*sizeof(char));
    addWords2Array("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/originalwords.txt",array_importantwords,N1);
    //Add unimportant words to stack.
    int N2=countwords("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/unimportantwords.txt");
    StackAddress strStack;
    strStack.ptop = NULL;	/* both pointers are initialised and set to NULL - there is no Stack yet*/
    strStack = addWordsToStack("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/unimportantwords.txt",strStack,N2);
    
    //Print array.
    int i;
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
    
    free(array_importantwords);
    deleteStack(strStack);
}