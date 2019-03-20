
#include "gameStructures.h"

int stackIsEmpty(int topOfStack);
int stackIsFull(int topOfStack);
token checkTop(token stack[MAX_TOKENS_PER_STACK], int topOfStack);
void push(token stack[], int *topOfStack, token data);
token pop(token stack[], int *topOfStack);