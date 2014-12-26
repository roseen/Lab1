//
//  duolist.c
//  Lab1
//
//  Created by Amanda Rosén on 2014-12-26.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "duolist.h"

void initDuo() {
    StrList* beginPtr[26];
    for (i=0,i<25,i++) beginPtr[i] = NULL    
}

int main(void)
{
    char inputStr[21]; 	        /* static string of max len 20 characters to store user's input from the console */
    StrList* beginPtr = NULL;    /* this is the pointer with the address of the first node in the list - the beginning of the list */
				/* NULL means that initially there are no nodes */
    
    do { /* add words provided by the user - the loop completes when the user writes end or END */
        printf("Enter another word to add to the list (or write END to finish this step): ");
        scanf("%s",inputStr);
        if ( strcmp(inputStr,"end") && strcmp(inputStr,"END") ) /* nodes are added provided that it is not END */
        {
            insertStr(&beginPtr,inputStr);	/* insert user's word to the list */
        }
        
    } while ( strcmp(inputStr,"end") && strcmp(inputStr,"END") ); /* the stopping condition: library fun STRCMP is used to see if the strings match */
    
    if (!isEmpty(beginPtr)) {
        printf("This is the current content of the list:\n");
        printStrList(beginPtr); /* print the list content */
        
        do {  /* remove words provided by the user - the loop completes when the user writes end or END */
            printf("Enter word to remove from the list (or write END to finish this step): ");
            scanf("%s",&inputStr);
            if ( strcmp(inputStr,"end") && strcmp(inputStr,"END") ) /* list will be searched for a given word provided that it is not END */
            {
                removeStr(&beginPtr,inputStr);	/* remove user's word from the list */
            }
            
        } while ( strcmp(inputStr,"end") && strcmp(inputStr,"END")); /* the stopping condition */
        
        if (!isEmpty(beginPtr)) {
            printf("This is the current content of the list:\n");
            printStrList(beginPtr);
            removeAll(&beginPtr); /* It is very important to free memory and remove the entire list at the end. */
        } else {
            printf("The final list is empty.\n");
        }
        
    } else {
        printf("Nothing has been added to the list.... program quits..\n");
    }
    
    return 0;
}


/* ---------------   function definition block -----------------------*/

/* This function adds a new node in the list with the content strdata = str */
void insertStr(StrList** pbegin,const char* str)	/* QUESTION: Why do we have a pointer to a pointer, i.e. **pbegin, here? */
{
    StrList* pnew; /* pointer to new node */
    StrList* pprev; /* pointer to previous node in list */
    StrList* pcurrent; /* pointer to current node in list */
    
    pnew = malloc(sizeof(StrList)); /* create a node, allocate memory for the structure and ... */
    pnew->strdata = malloc(strlen(str)+1); /* ... its member that is a pointer to char array - string  */
    /* The length of str can be obtained using STRLEN function (from string.h lib).
     The output of STRLEN should be increased by 1 to hold an extra '\0' terminator for strings. */
    
    if ( pnew != NULL ) { /* is space available */
        strcpy(pnew->strdata,str); /* place string str in node's field strdata; since this is an operation on strings, use string function STRCPY*/
        pnew->pnext = NULL; /* node does not link to another node */
        
        pprev = NULL;
        pcurrent = *pbegin;
        
        /* loop to find the correct location in the list */
        while ( pcurrent != NULL && ( strcmp(str,pcurrent->strdata) > 0 ) ) {  /* for comparing strings, use a library function STRCMP (string.h) */
            /* the idea behind WHILE condition is to iterate until the right spot (alphabetically ordered) is found for a new string*/
            pprev = pcurrent; /* move to ... */
            pcurrent = pcurrent->pnext; /* ... next node */
        }
        
        /* insert new node at beginning of list */
        if ( pprev == NULL ) {
            pnew->pnext = *pbegin;
            *pbegin = pnew;    /* update the pointer to the list */
            printf("------->  node added to the beginning of the list\n");
        }
        else { /* insert new node between pprev and pcurrent */
            pprev->pnext = pnew;		/* set the pointer from the list to this new item */
            pnew->pnext = pcurrent;	/* set the pointer from the new item to the next one in the list */
            printf("------->  next node added to the list\n");
        }
        
    }
    else {
        printf( "Problems with inserting %s.\n", str);
    }
}

/* This function removes the node in the list that matches the argument string str */
void removeStr(StrList** pbegin,const char* str) /* QUESTION: Why do we have a pointer to a pointer, i.e. **pbegin, here? */
{
    StrList* ptemp; /* temporary node pointer */
    StrList* pprev; /* pointer to previous node in list */
    StrList* pcurrent; /* pointer to current node in list */
    
    /* delete first node if it has a corresponding strdata content to the input argument str */
    if ( !strcmp((*pbegin)->strdata,str) ){
        ptemp = *pbegin; /* hold onto node being removed */
        *pbegin = (*pbegin)->pnext; /* de-thread the node */
        
        /* free the memory of the node ... */
        freeNode(&ptemp);
        
        printf("Node with %s has been removed.\n", str);
    }
    else {
        pprev = *pbegin;
        pcurrent = (*pbegin)->pnext;
        
        /* loop to find the correct location in the list */
        while ( pcurrent != NULL && strcmp(pcurrent->strdata,str) ) {
            pprev = pcurrent; /* walk to ... */
            pcurrent = pcurrent->pnext; /* ... next node */
        }
        
        /* delete node at pcurrent */
        if ( pcurrent != NULL ) {
            ptemp = pcurrent;
            pprev->pnext = pcurrent->pnext;
            printf("Node with %s has been removed.\n", str);
        } else {
            printf("Node with %s has not been found.\n", str);
        }
    }
    
}


/* This function frees memory allocated earlier for the node in the list */
void freeNode(StrList** pnode){ /* QUESTION: Why do we have a pointer to a pointer, i.e. **pnode, here? */
    
    free( (*pnode)->strdata );	/*... starting from dynamical memory of its fields, i.e. char array strdata ... */
    free( *pnode ); 		/* ...and finally the memory occupied by structure, here pointed to by pnode */
				/* the order of freeing memory is very important, otherwise we would loose pointer to the structure member strdata*/
    *pnode = NULL;
}

/* This function removes all the elements in the list and sets the pointer to the beginning of the network to NULL */
void removeAll(StrList** pbegin){ /* QUESTION: Why do we have a pointer to a pointer, i.e. **pbegin, here? */
    
    StrList* ptemp;
    
    while ( !isEmpty(*pbegin)  ) {
        ptemp = *pbegin;	    /* store aside the pointer to the beginning of the list */
        *pbegin = (*pbegin)->pnext; /* update *pbegin */
        freeNode(&ptemp);           /* remove the top node pointed to by ptemp set aside above  - memory is freed and the pointer set to NULL*/
    }
}

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty(StrList* pbegin)
{
    return pbegin == NULL; /*return the status of the pbegin pointer*/
}

/* This function prints out the list content */
void printStrList(StrList* pbegin)
{
    /* if list is empty */
    if (isEmpty(pbegin)) { // equivalent to if (ptr == NULL)
        printf("List is empty.\n" );
    } else {
        printf( "The list is:\n" );
        /* while not the end of the list */
        while (pbegin) { // equivalent to while (ptr != NULL)
            printf( "%s --> ", pbegin->strdata );
            pbegin = pbegin->pnext;
        } 
        printf( "NULL\n" );
    }
}
