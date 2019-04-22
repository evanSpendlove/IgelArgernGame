/*
    Game IO C file:
        --> Contains the functions for game input/output
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameIO.h"
#include "gameMechanics.h"
#include "stackMethods.h"
#include "gameSave.h"

/* CONTROL PANEL FUNCTION -- MAIN WAY OF CONTROLLING HOW THE GAME STARTS */

void controlPanel(int* numPlayers, int* loadSaveGame)
{
    static cell board[MAX_ROWS][MAX_COLUMNS]; // Initialises the game board with the max number of rows and columns

    int selection; // Used for storing user input

    // Print menu to user
    printInstruction("===================================================\n");
    printInstruction("===================================================\n");
    printInstruction("==                 CONTROL PANEL                 ==\n");
    printInstruction("==   Option                       Current        ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("==   (1) Number of Players           %d           ==\n", *numPlayers);
    printInstruction("==   (2) Load saved game             %d           ==\n", *loadSaveGame);
    printInstruction("==                                               ==\n");
    printInstruction("==   (3) Start new game                          ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("===================================================\n");
    printInstruction("===================================================\n");

    validInput(&selection, 1, 3); // take user input within the range 1-3

    switch (selection) // Switch based on user input
    {
        case 1: // Used chose to input the number of players
            printInstruction("How many users? (2-6) "); // Prompt user
            validInput(numPlayers, 2, 6); // Accept valid integer input within the range 2 - 6 players
            printInstruction("Number of players: %d\n", *numPlayers); // Print the new number of players
            controlPanel(numPlayers, loadSaveGame); // Call controlPanel()
            break; // Break switch

        case 2: // Used chose to load a saved game file
            printInstruction("Do you wish to load a previous saved game? (1 for yes, 0 for no) "); // Prompt user
            validInput(loadSaveGame, 0, 1); // Valid integer input accepted within range 0 - 1
            if(*loadSaveGame == 1)
            {
                *numPlayers = readPlayerCount(); // Reads the number of players from the load file
                game(board, *numPlayers, *loadSaveGame); // Calls game() with the variable pointed to by *loadSaveGame set to 1 (i.e. true)
            }
            break;

        case 3:
            if(*numPlayers > 1) // If the number of players is set
            {
                printInstruction("GAME STARTING in 5\n"); // Print announcement of game start
                printInstruction("GAME STARTING in 4\n");
                printInstruction("GAME STARTING in 3\n");
                printInstruction("GAME STARTING in 2\n");
                printInstruction("GAME STARTING in 1\n");
                printInstruction("GAME STARTING\n");
                game(board, *numPlayers, *loadSaveGame); // Start new game (passing *loadSaveGame as 0, i..e false)
            }
            else
            {
                printError("Please select option (1) and enter the number of players (>2, <=6).\n"); // Print an error, as you cannot start a game with <2 players
                controlPanel(numPlayers, loadSaveGame); // Call controlPanel()
            } 
        default:
            break;
    }
    
}

/* BOARD OUTPUT FUNCTIONS */

void outputBoard(cell board[MAX_ROWS][MAX_COLUMNS], const int totalPlayers)
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

void printBorder(const int tokensPerCell)
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

void printEmptyCell(const int tokensPerCell)
{
    int printCount = 0; // Counter used for printing the spaces in the cell

    while(printCount < tokensPerCell) // While cell has not been filled with empty spaces
    {
        printf("%c", ' '); // Prints a space (indicating no token)
        printCount++; // Increments printCount to move to the next token-space in the cell
    }
}

void printTokensInCell(cell board[MAX_ROWS][MAX_COLUMNS], int tokensPerCell, const int rows, const int columns)
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

/* UTILITY PRINT FUNCTIONS */

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

void printUsername(player currentPlayer)
{
    switch(currentPlayer.userColour)
    {
        case 0: // I.e. the user's colour is red
            printf(PRINT_RED "%s" PRINT_RESET, currentPlayer.username);
            break;
        case 1: // I.e. the user's colour is blue
            printf(PRINT_BLUE "%s" PRINT_RESET, currentPlayer.username);
            break;
        case 2: // I.e. the user's colour is green
            printf(PRINT_GREEN "%s" PRINT_RESET, currentPlayer.username);
            break;
        case 3: // I.e. the user's colour is magenta
            printf(PRINT_MAGENTA "%s" PRINT_RESET, currentPlayer.username);
            break;
        case 4: // I.e. the user's colour is cyan
            printf(PRINT_CYAN "%s" PRINT_RESET, currentPlayer.username);
            break;
        case 5: // I.e. the user's colour is yellow
            printf(PRINT_YELLOW "%s" PRINT_RESET, currentPlayer.username);
            break;
        default:
            printError("User %s has an invalid colour.\n", currentPlayer.username);
            break;
    }
}

void printColours(void)
{
    char tokenColours[6][8] = {"Red", "Blue", "Green", "Magenta", "Cyan", "Yellow"}; // List of available token colours
    int colour = 0;
    #ifdef _WIN32
        
        /* Print "Red" in red */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Red' in red
        colour++; // Increment colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
        /* Print "Blue" in blue */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); // set text colour to blue
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Blue' in blue
        colour++; // Increment colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text colour to white
    
        /* Print "Green" in green */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); // set text colour to green
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Green' in green
        colour++; // Increment colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text colour to white
    
        /* Print "Magenta" in magenta */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // set text colour to magenta
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Magenta' in magenta
        colour++; // Increment colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text colour to white
    
        /* Print "Cyan" in cyan */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // set text colour to cyan
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Cyan' in cyan
        colour++; // Increment colour
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text colour to white
    
        /* Print "Yellow" in yellow */
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // Set text colour to yellow
        printf("%d: %s\n", colour+1, tokenColours[colour]); // Print 'Yellow' in yellow
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text colour to white
        
    #else
        // Intentionally unsequence modification and access to 'colour - ignore the warning, it's intentional
        
        printf(PRINT_RED "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        colour++; // Increment colour

        printf(PRINT_BLUE "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        colour++; // Increment colour

        printf(PRINT_GREEN "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        colour++; // Increment colour

        printf(PRINT_MAGENTA "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        colour++; // Increment colour

        printf(PRINT_CYAN "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        colour++; // Increment colour

        printf(PRINT_YELLOW "%d: %s\n" PRINT_RESET, colour+1, tokenColours[colour]); // Prints "Red" in red
        
    #endif 
}

/* UTILITY INPUT FUNCTIONS */

void validInput(int* integer, const int lower, const int upper)
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
    while(getchar() != '\n'); // Clears input buffer
}
