/*
    
*/

#include "gameIO.h"

/*
    printInstruction() function:
        --> Prints an input string, with format specifiers, in magenta to the console
*/
void printInstruction(const char *format, ...)
{   
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    #else
        printf(PRINT_MAGENTA); // Sets the print colour to Magenta (for instructions)
    #endif

    va_list argList; // Initialises a list of variable arguments

    va_start(argList, format); // Initialises argList to be used for printing variable arguments

    vprintf(format, argList); // Prints the format string and its arguments using vprintf()
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    #else
        printf(PRINT_RESET); // Sets the print colour back to white
    #endif
    va_end(argList); // Ends the variable argument macro
}

/*
    printError() function:
        --> Simply prints an input string, with format specifiers, in red to the console
*/
void printError(const char *format, ...)
{
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    #else
        printf(PRINT_RED); // Sets the print colour to Magenta (for instructions)
    #endif
    
    va_list argList; // Initialises a list of variable arguments

    va_start(argList, format); // Initialises argList to be used for printing variable arguments

    vprintf(format, argList); // Prints the format string and its arguments using vprintf()

    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    #else
        printf(PRINT_RESET); // Sets the print colour back to white
    #endif

    va_end(argList); // Ends the variable argument macro
}

/*
    validInput() function:
        --> Takes user input
        --> Checks if it is a valid integer
        --> If it is, stores it in the address pointed to by *rating
*/
void validInput(int* integer, int lower, int upper)
{
    char input[10]; /* Array for storing user input */
    char* end; /* End array for storing non-integer part of user input */
    bool validIn = false; /* Bool for tracking status of valid input */

    while(validIn == false) /* While the user has not inputted a valid integer */
    {
        fgets(input, 10, stdin); /* Stores user input in input[] */
        *integer = strtol(input, &end, 10); /* Store the integer part of this input at the address pointed to by *matrix_dimension and the remainder of input in end[] */
        
        if(*end == '\n') /* If the only remaining input is the newline character */
        {
            if(*integer >= lower && *integer <= upper) /* If the integer is within the upper and lower bounds passed through the arguments */
            {
                validIn = true; /* If it is, update boolean, which breaks the loop */   
            }
            else /* Otherwise, print an error message requesting valid input and print the invalid input */
            {
                printError("Invalid input, please enter a valid integer\n");
            } 
        }
        else /* Otherwise, print an error message requesting valid input and print the invalid input */
        {
            printError("Input error, non-integer input: %s", end);
        }
    }
}

void clearInput(void)
{
    while(getchar() != '\n');
}

void printBorder(int tokensPerCell)
{
    int printCount = 0; // Counter used for printing borders of cells
    int columns; // Counter for looping over columns

    for(columns = 0; columns < MAX_COLUMNS; columns++)
        {
            printf("%c", '+'); // Prints the left-most corner of the cell
            for(printCount = 0; printCount < tokensPerCell; printCount++) // For each possible token in the cell, print a dash as a borderline
            {
                printf("-"); // Prints a border line
            }
        }
    printf("+\n"); // Prints the final right-most corner of the cell and then a newline
}

void printEmptyCell(int tokensPerCell)
{
    int printCount = 0; // Counter used for printing the spaces in the cell

    while(printCount < tokensPerCell) // While cell has not been filled with empty spaces
    {
        printf("%c", ' '); // Prints a space (indicating no token)
        printCount++; // Increments printCount to move to the next token-space in the cell
    }
}

void printTokensInCell(cell board[6][9], int tokensPerCell, int rows, int columns)
{
    static const char tokenImg = '|'; // Character representation of a token
    static const char wall = '|'; // Character representation of a cell wall
    static const char blank = ' '; // Blank space
    int tokenCount; // Counter for looping
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    #endif
    printf("%c", wall); // Starts cell with cell wall

    if(board[rows][columns].obstacle == active) // If there is an obstacle in the current cell
    {
        printf("X"); // Prints an obstacle to the board
        tokensPerCell--; // There is now one object in the cell, so we don't have space to fit 24 more
    }

    if(isStackEmpty(board[rows][columns].stackPtr) == 1) // If the stack of the current cell is empty
    {
        printEmptyCell(tokensPerCell); // Print an empty cell, since there are no tokens in the cell
    }
    else
    {   
        tokenCount = countStack(board[rows][columns].stackPtr);
           
        printStacks(board[rows][columns].stackPtr);
            
        while(tokenCount < tokensPerCell) // For the remaining token spaces in the cell
        {
            printf("%c", blank); // Print a blank space
            tokenCount++; // Increment counter
        }
    }
}

void outputBoard(cell board[6][9], int totalPlayers)
{
    int rows, columns, tokensPerCell; // Counters for looping

    tokensPerCell = (4*totalPlayers); // Number of tokens per cell = 4 tokens per user

    for(rows = 0; rows < MAX_ROWS; rows++) // For each row on the board
    {
        printBorder(tokensPerCell); // Prints the top border of the current row

        for(columns = 0; columns < MAX_COLUMNS; columns++) // For each column in the row...
        {
            printTokensInCell(board, tokensPerCell, rows, columns); // Print the tokens in the cell
        }
        printf("|\n"); // Print the final cell wall and a newline
    }

    printBorder(tokensPerCell); // Print the bottom border of the board
}

void controlPanel(int* numPlayers, int* loadSaveGame)
{
    cell board[MAX_ROWS][MAX_COLUMNS]; // Initialises the game board with the max number of rows and columns

    int selection;

    printInstruction("===================================================\n");
    printInstruction("===================================================\n");
    printInstruction("==                 CONTROL PANEL                 ==\n");
    printInstruction("==   Option                       Current        ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("==   (1) Num Players                 %d           ==\n",*numPlayers);
    printInstruction("==   (2) Load game                   %d           ==\n", *loadSaveGame);
    printInstruction("==                                               ==\n");
    printInstruction("==   (3) Start game                              ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("===================================================\n");
    printInstruction("===================================================\n");

    validInput(&selection, 1, 3);

    switch (selection)
    {
        case 1:
            printInstruction("How many users? (2-6) ");
            validInput(numPlayers, 2, 6);
            printInstruction("Num players: %d\n", *numPlayers);
            controlPanel(numPlayers, loadSaveGame);
            break;

        case 2:
            printInstruction("Do you wish to load a previous saved game? (1 for yes, 0 for no) ");
            validInput(loadSaveGame, 0, 1);
            controlPanel(numPlayers, loadSaveGame);

        case 3:
            if(*numPlayers > 0)
            {
                printInstruction("GAME STARTING in 5\n");
                printInstruction("GAME STARTING in 4\n");
                printInstruction("GAME STARTING in 3\n");
                printInstruction("GAME STARTING in 2\n");
                printInstruction("GAME STARTING in 1\n");
                printInstruction("GAME STARTING\n");
                game(board, *numPlayers);
            }
            else
            {
                printError("Please select option (1) and enter the number of players (>2, <=6).\n");
                controlPanel(numPlayers, loadSaveGame);
            } 
        default:
            break;
    }
    
}