/*
    Stack Methods C file:
        --> Contains all of the functions required for linked-list stack implementation
    Written by: Reuben Mulligan (18733589) and Evan Spendlove (18492656)
*/

#include "stackMethods.h"
#include "gameStructures.h"
#include "gameIO.h"
#ifdef _WIN32
    #include <windows.h>
#endif

int insert(ListNodePtr *tPtr, int value)
{
    ListNodePtr newPtr = malloc(sizeof(ListNode)); 
    if (newPtr != NULL) 
    { 
        newPtr->data = value; 
        
        if(*tPtr == NULL)
        {
            newPtr->prevPtr = NULL;
            *tPtr = newPtr;
            return 1;
        }
        else
        {
            newPtr->prevPtr = *tPtr;
            *tPtr = newPtr;
            return 1;
        }
    } 
    else 
    {
        printError( "%d not inserted. No memory available.\n", value );
        return 2;
    } 
} 

int delete(ListNodePtr *tPtr)
{
     if (*tPtr != NULL) 
     {
         ListNodePtr tempPtr = *tPtr;
         *tPtr = (*tPtr)->prevPtr;
         return 1;
    }
    else
    {
        printError("List is empty.\n");
        return 2;
    }
} 


void printList(ListNodePtr currentPtr)
{
    /* if list is empty */
    if ( currentPtr == NULL ) {
        printInstruction( "List is empty.\n\n" );
     } /* end if */
    else {
        printInstruction( "The list is:\n" );

    /* while not the end of the list */
    while ( currentPtr != NULL ) {
        printInstruction( "%d --> ", currentPtr->data );
        currentPtr = currentPtr->prevPtr;
     } /* end while */

    printInstruction( "NULL\n\n" );
     } /* end else */
}

void printStacks(ListNodePtr currentStack)
{
    int count = countStack(currentStack);
    int stack[count];
    int i = 0;
    if(currentStack != NULL)
    {
        while(currentStack != NULL)
        {
            stack[i] = currentStack->data;
            currentStack = currentStack->prevPtr;
            i++;
        }

        i--;

        while(i > -1)
        {
            #ifdef _WIN32
                if(stack[i] == 0) // If the token colour is red
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    printf("%c", '|'); // Print a red token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(stack[i] == 1) // If the token colour is blue
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                    printf("%c", '|'); // Print a blue token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(stack[i] == 2) // If the token colour is green
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    printf("%c", '|'); // Print a green token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(stack[i] == 3) // If the token colour is magenta
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                    printf("%c", '|'); // Print a magenta token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(stack[i] == 4) // If the token colour is Cyan
                { 
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    printf("%c", '|'); // Print a cyan token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                else if(stack[i] == 5) // Else the colour must be yellow
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    printf("%c", '|'); // Print a yellow token
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
            #else
                if(stack[i] == 0) // If the token colour is red
                {
                    printf(PRINT_RED "%c" PRINT_RESET, '|'); // Print a red token
                }
                else if(stack[i] == 1) // If the token colour is blue
                {
                    printf(PRINT_BLUE "%c" PRINT_RESET, '|'); // Print a blue token
                }
                else if(stack[i] == 2) // If the token colour is green
                {
                    printf(PRINT_GREEN "%c" PRINT_RESET, '|'); // Print a green token
                }
                else if(stack[i] == 3) // If the token colour is magenta
                {
                    printf(PRINT_MAGENTA "%c" PRINT_RESET, '|'); // Print a magenta token
                }
                else if(stack[i] == 4) // If the token colour is Cyan
                { 
                    printf(PRINT_CYAN "%c" PRINT_RESET, '|'); // Print a cyan token
                }
                else // Else the colour must be yellow
                {
                    printf(PRINT_YELLOW "%c" PRINT_RESET, '|'); // Print a yellow token
                }
            #endif 
            i--;
        }
    }
}

int isStackEmpty(ListNodePtr currentPtr)
{
    if(currentPtr == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isStackFull(ListNodePtr currentPtr)
{
    int counter;

    if(currentPtr == NULL)
    {
        return 0;
    }
    else
    {
        while( currentPtr != NULL)
        {
            counter++;
            currentPtr = currentPtr->prevPtr;
        }
        if(counter == 24)
        {
            printError("Stack is full.\n\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int moveToken(ListNodePtr *originalStackPtr, ListNodePtr *newStackPtr)
{
    if(isStackFull(*newStackPtr) == 1)
    {
        printError("New stack is full, unable to complete move.\n\n");
        return 0;
    }
    else if(isStackEmpty(*originalStackPtr) == 1)
    {
        printError("Original stack is empty, no token to move. Move uncompletable.\n\n");
        return 0;
    }
    else
    {
        ListNodePtr newPtr = malloc(sizeof(ListNode));
        int a = returnTopValue(*originalStackPtr);

        if(a != 6)
        {
            if(insert(newStackPtr, a) == 2)
            {
                printError("Insert failed\n\n");
                return 0;
            }
            else
            {
                if(delete(originalStackPtr) == 2)
                {
                    printError("Delete failed\n\n");
                    return 0;
                }

            }
            return 1;
        }
        else
        {
            return 0;
        }

    }
}

int returnTopValue(ListNodePtr stackPtr)
{
    if(stackPtr != NULL)
    {
        return (stackPtr->data);
    }

    else if(stackPtr == NULL) // If the stack pointer is NULL (i.e. empty stack)
    {
        return -1;
    }

    else // An error ocurred
    {
        return 6;
    }
}

int countStack(ListNodePtr stackPtr)
{
    if(stackPtr != NULL)
    {
        int counter = 0;

        while(stackPtr != NULL)
        {
            counter++;
            stackPtr = stackPtr->prevPtr;
        }

        return counter;
    }

    else if(stackPtr == NULL) // If the stack is empty
    {
        return 0; // Stack is empty
    }

    else // An error ocurred
    {
        return -1;
    }
}