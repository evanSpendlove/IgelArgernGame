
#include "gameStructures.h"

int stackIsEmpty(int topOfStack);
int stackIsFull(int topOfStack);
token checkTop(token stack[MAX_TOKENS_PER_STACK], int topOfStack);
void push(token stack[], int *topOfStack, token data);
token pop(token stack[], int *topOfStack);
int printList( ListNodePtr currentPtr );
int delete( ListNodePtr *tPtr);
int insert(  ListNodePtr *tPtr, int value );
int isStackEmpty(ListNodePtr currentPtr);
int isStackFull(ListNodePtr currentPtr);
int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr);
int returnTopValue(ListNodePtr stackPtr);
int countStack(ListNodePtr stackPtr);
int printStacks(ListNodePtr currentStack);