//
//  array.h
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-17.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#ifndef __LaborationEtt__array__
#define __LaborationEtt__array__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


void addWords2Array(char* filename,char (*array_importantwords)[60],int N1);
void removeFromArray(char (*array_importantwords)[60],int array_length,int remove_position);


#endif /* defined(__LaborationEtt__array__) */
