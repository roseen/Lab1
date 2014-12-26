//
//  filterWords.c
//  Lab1
//
//  Created by Amanda Rosén on 2014-12-26.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "filterWords.h"


int filterWords(char (*array_importantwords)[60],StackAddress strStack,int array_length) {
    int i;
    for (i=0; i<=array_length; i++) {
        if (existsStrStack(strStack,array_importantwords[i])!=0) {
            removeFromArray(array_importantwords,array_length,i);
            array_length--;
        }
    }
    return array_length;
}