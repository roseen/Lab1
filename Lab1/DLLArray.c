//
//  DLLArray.c
//  Lab1
//
//  Created by Henrik Rosén on 2014-12-29.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "DLLArray.h"

int selectArray(const char* str) {
    int a = 'A';
    char c = toupper(str[0]);
    
    return c-a;
}
