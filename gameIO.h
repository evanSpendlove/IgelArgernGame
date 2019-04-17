/*
    Header file for Game input and output
    -> Contains function prototypes for all functions in gameIO.c file
    Written by: Evan Spendlove (18492656)
*/

#include "gameStructures.h"
#include "gameMechanics.h"
#include "stackMethods.h"
#include <stdarg.h>

#ifdef _WIN32
    #include <windows.h>
#endif

/*
    printInstruction() function:
        -->
*/
void printInstruction(const char *format, ...);

/*
    printError() function:
        -->
*/
void printError(const char *format, ...);

/*
    validInput() function:
        -->
*/
void validInput(int* integer, int lower, int upper);

/*
    clearInput() function:
        -->
*/
void clearInput(void);

/*
    printBorder() function:
        -->
*/
void printBorder(int tokensPerCell);

/*
    printEmptyCell() function:
        -->
*/
void printEmptyCell(int tokensPerCell);

/*
    printTokensInCell() function:
        -->
*/
void printTokensInCell(cell board[6][9], int tokensPerCell, int rows, int columns);

/*
    outputBoard() function:
        -->
*/
void outputBoard(cell board[6][9], int totalPlayers);

/*
    controlPanel() function:
        -->
*/
void controlPanel(int* numPlayers, int* loadSaveGame);
