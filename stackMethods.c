/*
    Stack methods
*/

#include "stackMethods.h"
#include "gameStructures.h"

int stackIsEmpty(int topOfStack)
{
    if(topOfStack == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int stackIsFull(int topOfStack)
{
    if(topOfStack == MAX_TOKENS_PER_STACK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

token checkTop(token stack[MAX_TOKENS_PER_STACK], int topOfStack)
{
    return stack[topOfStack];
}

void push(token stack[], int *topOfStack, token data)
{
    if(stackIsFull(*topOfStack) == 0)
    {
        (*topOfStack)++;
        stack[(*topOfStack)] = data;
    }
    else
    {
        puts("Stack is full.");
    }
}

token pop(token stack[], int *topOfStack)
{
    if(stackIsEmpty(*topOfStack) == 0)
    {
        token data = stack[*topOfStack];
        (*topOfStack)--;
        return data;
    }
    else
    {
        puts("Stack empty.");
    }
}

int insert( ListNodePtr *tPtr, int value )
{
    ListNodePtr newPtr = malloc( sizeof( ListNode ) ); 
    if ( newPtr != NULL ) { 
        newPtr->data = value; 
        
        if(*tPtr == NULL){
            newPtr->prevPtr = NULL;
            *tPtr = newPtr;
            return 1;
        }else{
            newPtr->prevPtr = *tPtr;
            *tPtr = newPtr;
            return 1;
        }

    } 
    else {
        printf( "%d not inserted. No memory available.\n", value );
        return 2;
    } 
} 

int delete( ListNodePtr *tPtr)
{
     if ( *tPtr != NULL ) {
         ListNodePtr tempPtr = *tPtr;
         *tPtr = (*tPtr)->prevPtr;
         return 1;
    }else{
        printf("List is empty. \n\n");
        return 2;
    }
} 


int printList( ListNodePtr currentPtr )
{
    /* if list is empty */
    if ( currentPtr == NULL ) {
        printf( "List is empty.\n\n" );
     } /* end if */
    else {
        printf( "The list is:\n" );

    /* while not the end of the list */
    while ( currentPtr != NULL ) {
        printf( "%d --> ", currentPtr->data );
        currentPtr = currentPtr->prevPtr;
     } /* end while */

    printf( "NULL\n\n" );
     } /* end else */
} /* end function printList */

int isStackEmpty(ListNodePtr currentPtr){
    if(currentPtr == NULL){
        return 1;
    }else{
        return 0;
    }
}

int isStackFull(ListNodePtr currentPtr){
    int counter;
    if(currentPtr == NULL){
        printf("List is empty.\n\n");
        return 0;
    }else{
        while( currentPtr != NULL){
            counter++;
            currentPtr = currentPtr->prevPtr;
        }
        if(counter == 24){
            printf("Stack is full.\n\n");
            return 1;
        }else{
            printf("Stack isn't full.\n\n");
            return 0;
        }
    }
}

int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr){
    if(isStackFull(*newStackPtr) == 1){
        printf("New stack is full, unable to complete move.\n\n");
        return 0;
    }else if(isStackEmpty(*originalStackPtr) == 1){
        printf("Original stack is empty, no token to move. Move uncompletable.\n\n");
        return 0;
    }else{
        ListNodePtr newPtr = malloc( sizeof( ListNode ) );
        int a = returnTopValue(*originalStackPtr);
        if(a != 6){
            insert(newStackPtr, a);
            printList(*newStackPtr);
            delete(originalStackPtr);
        }else{
            return 0;
        }
        return 1;
    }
}

int returnTopValue(ListNodePtr stackPtr){
    if(stackPtr != NULL){
        return (stackPtr->data);
    }else{
        return 6;
    }
}
int countStack(ListNodePtr stackPtr){
    if(stackPtr != NULL){
        int counter = 0;
        while(stackPtr != NULL){
            counter++;
            stackPtr = stackPtr->prevPtr;
        }
        return counter;
    }else{
        return -1;
    }
}