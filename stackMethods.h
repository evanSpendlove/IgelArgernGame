/*
    Stack Methods Header File:
        --> Contains all of the function prototypes for the functions in stackMethods.c
    Written by: Reuben Mulligan (18733589)
*/
#include "gameStructures.h"

int delete( ListNodePtr *tPtr); // Maybe remove? (Do we use?)
int insert(  ListNodePtr *tPtr, int value );

void printList(ListNodePtr currentPtr); // Maybe remove?
void printStacks(ListNodePtr currentStack);

int isStackEmpty(ListNodePtr currentPtr);
int isStackFull(ListNodePtr currentPtr);

int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr);
int returnTopValue(ListNodePtr stackPtr);
int countStack(ListNodePtr stackPtr);