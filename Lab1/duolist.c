//
//  duolist.c
//  Lab1
//
//  Created by Amanda Rosén on 2014-12-26.
//  Copyright (c) 2014 Amanda Rosén. All rights reserved.
//

#include "duolist.h"

/* This function adds a new node in the list with the content strdata = str */
void insertStr(StrList** pbegin,StrList** pend,const char* str)	/* QUESTION: Why do we have a pointer to a pointer, i.e. **pbegin, here? */
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
        pnew->pprev = NULL;
        
        pprev = NULL; /* Iterator: Pointer to previous node */
        pcurrent = *pbegin; /* Iterator: Pointer to current node */
        
        /* loop to find the correct location in the list */
        while ( pcurrent != NULL && ( strcmp(str,pcurrent->strdata) > 0 ) ) {  /* for comparing strings, use a library function STRCMP (string.h) */
            /* the idea behind WHILE condition is to iterate until the right spot (alphabetically ordered) is found for a new string*/
            pprev = pcurrent; /* move to ... */
            pcurrent = pcurrent->pnext; /* ... next node */
        }
        
        if ( pprev == NULL ) { /* insert new node at beginning of list */
            if (*pbegin != NULL) {
                pnew->pnext = *pbegin; /* Link to the previous first element */
                (*pbegin)->pprev = pnew; /* Connect from previous first element back to the new first */
            }
            if (*pbegin == NULL) *pend =pnew; /* This is the first element in the list - update the end pointer */
            *pbegin = pnew;    /* update the pointer to the list */
            printf("------->  %s. node added to the beginning of the list\n",str);
        }
        else { /* Not first in list */
            if (pcurrent == NULL ) { /* Insert last in list pprev */
                pprev->pnext = pnew;		/* set the pointer from the list to this new item */
                pnew->pprev = pprev;
                *pend = pnew; /* Last element - update the end pointer */
                printf("------->  %s. next node added to the list\n",str);
                
            }
            else {
                if (strcmp(str,pcurrent->strdata) != 0) { /* insert new node in the list, not first, not last */
                    pprev->pnext = pnew;		/* set the pointer from the list to this new item */
                    pnew->pprev = pprev;
                    pnew->pnext = pcurrent;	/* set the pointer from the new item to the next one in the list */
                    pcurrent->pprev = pnew;
                    printf("------->  %s. next node added to the list\n",str);
                }
                else {
                    printf("------->  %s. duplicate - not added to the list\n",str);
                }
            }
        }
    }
    else {
        printf( "Problems with inserting %s.\n", str);
    }
}

/* Search for word. NULL if not found, otherwise pointer to word */
StrList* searchStr(StrList** pbegin,const char* str)
{
    StrList* pprev; /* pointer to previous node in list */
    StrList* pcurrent; /* pointer to current node in list */
    StrList* returnValue = NULL;
    
    pprev = NULL;
    pcurrent = *pbegin;
    
    /* loop to find the correct location in the list */
    while ( pcurrent != NULL && ( strcmp(str,pcurrent->strdata) != 0 ) ) {  /* for comparing strings, use a library function STRCMP (string.h) */
        /* the idea behind WHILE condition is to iterate until the right spot (alphabetically ordered) is found for a new string*/
        pprev = pcurrent; /* move to ... */
        pcurrent = pcurrent->pnext; /* ... next node */
    }

    if (pcurrent != NULL) {
        if (strcmp(str, pcurrent->strdata)==0) {
            returnValue = pcurrent;
        }
    }
    return returnValue;
}


/* This function removes the node in the list that matches the argument string str */
void removeStr(StrList** pbegin,StrList** pend,const char* str)
{
    StrList* ptemp; /* temporary node pointer */
    StrList* pprev; /* pointer to previous node in list */
    StrList* pcurrent; /* pointer to current node in list */
    
    /* delete first node if it has a corresponding strdata content to the input argument str */
    if (*pbegin != NULL) {
        if ( !strcmp((*pbegin)->strdata,str) ){ /* Remove first node */
            ptemp = *pbegin; /* hold onto node being removed */
            *pbegin = (*pbegin)->pnext; /* de-thread the node */
            if (*pbegin!=NULL) (*pbegin)->pprev = NULL; /* Change pointer back if not last in list */
            /* free the memory of the node ... */
            freeNode(&ptemp);
            
            printf("Node with %s has been removed.\n", str);
        }
        else {
            pprev = *pbegin;  /* Iterator: Pointer to previous node */
            pcurrent = (*pbegin)->pnext;  /* Iterator: Pointer to current node */
            
            /* loop to find the correct location in the list */
            while ( pcurrent != NULL && strcmp(pcurrent->strdata,str) ) {
                pprev = pcurrent; /* walk to ... */
                pcurrent = pcurrent->pnext; /* ... next node */
            }
            
            /* delete node at pcurrent */
            if ( pcurrent != NULL ) {
                ptemp = pcurrent;
                pprev->pnext = pcurrent->pnext;
                if (pcurrent->pnext == NULL) { /* This is the last element. Update the end pointer */
                     pend = NULL;
                }
                else {
                    pcurrent->pnext->pprev = pprev;
                }
                freeNode(&ptemp);
                printf("Node with %s has been removed.\n", str);
            } else {
                printf("Node with %s has not been found.\n", str);
            }
        }
    }
    else {
        printf("List empty, nothing to remove.\n");
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
void removeAll(StrList** pbegin,StrList** pend){ /* QUESTION: Why do we have a pointer to a pointer, i.e. **pbegin, here? */
    
    StrList* ptemp;
    
    while ( !isDuolistEmpty(*pbegin)  ) {
        ptemp = *pbegin;	    /* store aside the pointer to the beginning of the list */
        *pbegin = (*pbegin)->pnext; /* update *pbegin */
        freeNode(&ptemp);           /* remove the top node pointed to by ptemp set aside above  - memory is freed and the pointer set to NULL*/
    }
    *pend = NULL;
}

/* Return 1 if the list is empty, 0 otherwise */
int isDuolistEmpty(StrList* pbegin)
{
    return pbegin == NULL; /*return the status of the pbegin pointer*/
}

/* This function prints out the list content */
void printStrList(StrList* pbegin)
{
    /* if list is empty */
    if (isDuolistEmpty(pbegin)) { // equivalent to if (ptr == NULL)
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

/* This function prints out the list content */
int printStrList2File(FILE *f,StrList* pbegin)
{
    int count=0;
    /* if list is empty */
    if (isDuolistEmpty(pbegin)) { // equivalent to if (ptr == NULL)
        printf("List is empty.\n" );
    } else {
        /* while not the end of the list */
        while (pbegin) { // equivalent to while (ptr != NULL)
            fprintf(f, "%s\n", pbegin->strdata );
            count++;
            pbegin = pbegin->pnext;
        }
    }
    return count;
}

/* This function prints out the list content */
void print2ndFirstnLast(StrList* pbegin,StrList* pend)
{
    /* if list is empty */
    if (isDuolistEmpty(pbegin)) { // equivalent to if (ptr == NULL)
        printf("List is empty.\n" );
    } else {
        if (pbegin == pend) {
            printf("Only one element in list - don't print!\n" );
        }
        else {
            printf("Second element is %s and second last element is %s.\n",pbegin->pnext->strdata,pend->pprev->strdata);
        }
    }
}