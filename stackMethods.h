
#include "gameStructures.h"

int delete( ListNodePtr *tPtr);
int insert(  ListNodePtr *tPtr, int value );

void printList(ListNodePtr currentPtr);
void printStacks(ListNodePtr currentStack);

int isStackEmpty(ListNodePtr currentPtr);
int isStackFull(ListNodePtr currentPtr);

int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr);
int returnTopValue(ListNodePtr stackPtr);
int countStack(ListNodePtr stackPtr);