
#include "gameStructures.h"

int delete( ListNodePtr *tPtr);
int insert(  ListNodePtr *tPtr, int value );
int printList( ListNodePtr currentPtr );
int isStackEmpty(ListNodePtr currentPtr);
int isStackFull(ListNodePtr currentPtr);
int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr);
int returnTopValue(ListNodePtr stackPtr);
int countStack(ListNodePtr stackPtr);
int printStacks(ListNodePtr currentStack);