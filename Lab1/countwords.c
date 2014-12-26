//
//  countwords.c
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-20.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "countwords.h"

int countwords(char* filename)
{
    FILE* fp;
    int count=0;
    char c[60];
    /* opening a text file for reading  */
    fp = fopen(filename,"rt");
    if(fp == NULL) { /*in case the opening was unsuccessful, e.g. a missing file*/
        perror("Error opening file");
        return(-1);
    }
    else {
        while(fgets(c,60,fp)!=NULL) {
            count++;
        }
    }
    fclose(fp); /*Closing is very important!*/
    return count;
}