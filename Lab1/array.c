//
//  array.c
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-17.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "array.h"
#include "removelastCR.h"

void addWords2Array(char* filename,char (*array_importantwords)[60],int N1)
{
    FILE* fp;
    int count=0;
    char c[60];
    /* opening a text file for reading  */
    fp = fopen(filename,"rt");
    if(fp == NULL) { /*in case the opening was unsuccessful, e.g. a missing file*/
        perror("Error opening file");
    }
    else {
        while((fgets(c,60,fp)!=NULL) && (count<N1)) {
            removeLastCR(c);
            strcpy(array_importantwords[count],c);
            count++;
        }
    }
    fclose(fp); /*Closing is very important!*/
}

void removeFromArray(char (*array_importantwords)[60],int array_length,int remove_position) {
    int i;
    for(i=remove_position; i<array_length-1 ; i++) *array_importantwords[i]=*array_importantwords[i+1];
}