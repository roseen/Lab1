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


int main()
{
    //int N=countwords("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/unimportantwords.txt");
    int N1=countwords("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/originalwords.txt");
    char (*array_importantwords)[60];
    array_importantwords=(char(*)[60])malloc(N1*60*sizeof(char));
    addWords2Array("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/originalwords.txt",array_importantwords,N1);
    int N2=countwords("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/unimportantwords.txt");
    StackAddress strStack;
    strStack.pbegin = NULL;	/* both pointers are initialised and set to NULL - there is no Stack yet*/
    strStack.pend = NULL;
    strStack = addWordsToStack("/Users/Amanda/Desktop/LaborationEtt/LaborationEtt/unimportantwords.txt",strStack,N2);
    
    int i;
    for (i=0;i<N1;i++) {
        printf("%s\n",array_importantwords[i]);
    }
    printStrStack(strStack);
    
    free(array_importantwords);
    deleteStack(strStack);
    printf("%d\n",N1);
    printf("%d\n",N2);
}