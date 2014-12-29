//
//  stack.c
//  LaborationEtt
//
//  Created by Amanda Rosén on 2014-12-20.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "stack.h"
#include "removeLastCR.h"


/* IMPORTANT: 	This is a first-in-first-out (FIFO) Stack where elements are removed from the beginning and added to the end.
	
 Pay attention to those functions that modify the Stack (add or remove a node, or delete the entire Stack) and notice
 that they take a structure saddress of type StackAddress (with pointers-addresses to the beginning & end of the Stack) as an argument
 and return the updated version. The updated pointers have to be returned because when the function call is over
 the internal argument saddress seizes to exist. It needs to be copied outside and this is achieved by RETURN.
 At the same time the memory under the adress pointed by pointers can be permanently modified.
 In conclusion, it is worth noticing the difference between modifying the memory content pointed by a pointer (operation on memory seen 			also from outside the function) and modifying the pointer itself (changing the address), which is limited in scope to the function 			(therefore has to be returned in order to be seen outside the function scope).
 */


/* This function adds a new node to the end of the Stack with the content strdata = str */
StackAddress Push(StackAddress saddress,const char* str)
{
    /* create the node by allocating memory and assigning strdata*/
    StrStack* pnewnode = (StrStack*)malloc(sizeof(StrStack));
    pnewnode->pnext = saddress.ptop; 			/* This is going to be the last element so its pnext field should point towards NULL */
    pnewnode->strdata = (char*)malloc((strlen(str)+1)*sizeof(char)); /* allocate memory to store a string */
    strcpy(pnewnode->strdata,str);		/* copy the requested string str to the new memory allocation */
    
    if (saddress.ptop==NULL) {	/* if the Stack is empty */
        		/*  saddress.ptop should point to the new node */
        saddress.ptop = pnewnode;
    } else {					/* if this is not the first node in the Stack*/
        saddress.ptop = pnewnode; 	        /* 2) update the pointer ptop to the top of the Stack*/
    }
    
    return saddress;
    
}

/* This function removes the node from the beginning of the Stack, frees memory and assigns the string value to the argument string str */
/* IMPORTANT: It is assumed that memory has been allocated to str outside the function*/
StackAddress Pop(StackAddress saddress,char* str)

{
    StrStack * auxptr;
    
    if (saddress.ptop!=NULL) { /* if the Stack is not empty */
        
        auxptr = saddress.ptop;	/* store aside the pointer to the beginning of the Stack and
                                     at the same time (more importantly) the pointer to the node that will be deStackd (removed) */
        
        saddress.ptop = saddress.ptop->pnext;	/* update the pointer to the beginning of the Stack */
        if (saddress.ptop==NULL)  /* if after removing the node the Stack becomes empty,.. */
        {
            saddress.ptop = NULL;    /* ..., set the ptop pointer to NULL, too. */
        }
        
        /* The Stack pointers have been updated now is the time to work on the deStackd node. */
        strcpy(str,auxptr->strdata);	/* First, copy the content of the field strdata to the str character array, for which memory had to be allocated outside the function */
        
        /* Secondly, free memory occupied by the node ...*/
        free( auxptr->strdata );	/*... starting from dynamical memory of its fields, i.e. char array strdata ... */
        free( auxptr ); 		/* ...and finally the memory occupied by structure, here pointed to by pnode */
        /* the order of freeing memory is very important, otherwise we would loose the pointer to the structure field strdata*/
    }
    
    return saddress;
}


/* This function returns 1 if the Stack is empty, 0 otherwise */
int isStackEmpty(StackAddress saddress)
{ return saddress.ptop == NULL; /*return the status of the ptop pointer*/
}

/* Returns 1 if word exists, 0 otherwise */
int existsStrStack(StackAddress saddress, const char* str)
{
    if (1==1) {
        
    }
    while (saddress.ptop) { // equivalent to while (ptop != NULL)
        if (strcmp(saddress.ptop->strdata,str) == 0) {
            return 1;
        }
        saddress.ptop = saddress.ptop->pnext;   // This change of saddress will not affect the original
    }
                                                 
    return 0;
    
}

/* This function prints out the Stack content */
void printStrStack(StackAddress saddress)
{
    /* if Stack is empty */
    if (isStackEmpty(saddress)) { // equivalent to if (ptop == NULL)
        printf("The Stack is empty.\n" );
    } else {
        printf( "The Stack is:\n" );
        /* while not the end of the Stack */
        while (saddress.ptop) { // equivalent to while (ptop != NULL)
            printf( "%s --> ", saddress.ptop->strdata );
            saddress.ptop = saddress.ptop->pnext;   /* This change of saddress will not affect the original StackAddress variable in the main program
                                                         because saddress is passed to the function by value. This means that a local copy of the 								original StackAddress variable is made and it disappears when the function execution is over.
                                                         We just use it here to traverse the Stack without any consequences for the original ptop pointer pointing to the top of the Stack.*/
            
        }
        printf( "NULL\n" );
    }
}


StackAddress deleteStack(StackAddress saddress)
{
    StrStack* ptemp;
    
    while ( !isStackEmpty(saddress)  ) {		/* traverse (iterate) through the Stack */
        ptemp = saddress.ptop;	    	/* store aside the pointer to the current beginning of the list */
        saddress.ptop = saddress.ptop->pnext; /* update the address of the beginning of the Stack -> move to the next */
        
        free(ptemp->strdata);			/* free memory for the deStackd node, first its field strdata and ...*/
        free(ptemp);				/* ... then the entire node structure (see also Pop for extra comments) */
    }
    saddress.ptop=NULL;			/* at the end set both ptop and pend to NULL - the Stack does not exist any longer */
    
    return saddress;
    
}


StackAddress addWordsToStack(char* filename,StackAddress strStack,int N2)
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
        while((fgets(c,60,fp)!=NULL) && (count<N2)) {
            removeLastCR(c);
            strStack= Push(strStack,c);
            count++;
        }
    }
    fclose(fp); /*Closing is very important!*/
    return strStack;
}