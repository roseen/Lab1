//
//  removelastCR.c
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-21.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "removelastCR.h"


/* The first occurrence of a white space (including the escape sequence, e.g. \r or \n) marks the last of word */
void removeLastCR(char* string) {
    
    int len = strlen(string);
    int letter_index = 0;
    while ((letter_index < len) && (!isspace(string[letter_index])))
    {
        letter_index++;
    }
    string[letter_index]='\0';
}