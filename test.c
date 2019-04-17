#include "gameStructures.h"



#include "stackMethods.h"
#include "stackMethods.c"

int main(void){

    ListNodePtr topPtr = NULL;
    ListNodePtr newPtr = NULL;
    int a = isStackEmpty(topPtr);
    if(a == 1){
        printf("Stack is empty.\n\n");
    }
    insert(&topPtr, 1);
    insert(&topPtr, 2);
    insert(&topPtr, 3);
    insert(&topPtr, 4);
    insert(&topPtr, 5);
    int c = countStack(topPtr);
    printf("%d\n",c);
    printList(topPtr);
    a = isStackEmpty(topPtr);
    if(a == 1){
        printf("Stack is empty.\n\n");
    }
    isStackFull(topPtr);
    int b = moveToken(&topPtr, &newPtr);
    if(b == 1){
        printf("Move complete!\n\n");
        printList(topPtr);
        printList(newPtr);
    }
    player test;
    test.userColour = Red;
    test.userStack = NULL;
    insert(&test.userStack, test.userColour);
    
    insert(&test.userStack, test.userColour);
    
    insert(&test.userStack, test.userColour);
    
    insert(&test.userStack, test.userColour);
    printList(test.userStack);
    return 0;
}