/*
    Header file for Game input and output
    -> Contains function prototypes for all functions in gameIO.c file
    Written by: Evan Spendlove (18492656)
*/

#include "gameStructures.h"
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
#endif

/* CONTROL PANEL FUNCTION -- MAIN WAY OF CONTROLLING HOW THE GAME STARTS */

    /*
        controlPanel() function:
            --> Prints the menu to the user at the start of the program
            --> Allows the user to set the number of players, load a game or start a new game
    */
    void controlPanel(int* numPlayers, int* loadSaveGame);

/* BOARD OUTPUT FUNCTIONS */

    /*
        outputBoard() function:
            -->  Calls various other functions to print the board with the obstacles and tokens on it
    */
    void outputBoard(cell board[MAX_ROWS][MAX_COLUMNS], const int totalPlayers);

    /*
        printBorder() function:
            --> Prints the border of the cells on the board
    */
    void printBorder(const int tokensPerCell);

    /*
        printEmptyCell() function:
            -->  Prints an empty cell (i.e. one with no tokens in it)
    */
    void printEmptyCell(const int tokensPerCell);

    /*
        printTokensInCell() function:
            --> Prints the tokens in a cell (in their respective colours)
    */
    void printTokensInCell(cell board[MAX_ROWS][MAX_COLUMNS], int tokensPerCell, const int rows, const int columns);

/* PRINT UTILITY FUNCTIONS */

    /*
        printInstruction() function:
            --> Prints an input string, with format specifiers, in magenta to the console
    */
    void printInstruction(const char *format, ...);

    /*
        printError() function:
            --> Simply prints an input string, with format specifiers, in red to the console
    */
    void printError(const char *format, ...);

    /*
        printUsername() function:
            --> Prints the username of the player based by value in its respective colour
    */
    void printUsername(player currentPlayer);

    /*
        printColours() function:
            --> Prints the list of available token/user colours in their respective colours
    */
    void printColours(void);

/* INPUT UTILITY FUNCTIONS */

    /*
        validInput() function:
            --> Takes user input
            --> Checks if it is a valid integer
            --> If it is, stores it in the address pointed to by *rating
    */
    void validInput(int* integer, const int lower, const int upper);

    /*
        clearInput() function:
            --> Clear input buffer
    */
    void clearInput(void);





