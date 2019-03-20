/*
    Stack methods
*/

#include "stackMethods.h"

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