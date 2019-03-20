/*
    Main file for the Game.
    Project written by: Reuben Mulligan, Evan Spendlove
*/

/* #INCLUDES GO HERE */

#include "gameStructures.h"

#include "gameSetup.h"
#include "gameSetup.c"

#include "gameIO.h"
#include "gameIO.c"

#include "random.h"
#include "random.c"

#include "stackMethods.h"
#include "stackMethods.c"

#include "initialTokens.h"
#include "initialTokens.c"

int main(void)
{
    cell board[MAX_ROWS][MAX_COLUMNS]; // Initialises the game board with the max number of rows and columns
    int obstacleLocations[6]; // Used for checking obstacles at each stage of the game

    srand(time(NULL));

    /* Requesting the user to set the total number of players */
    int totalPlayers = 0;
    printInstruction("How many players are there?\n");
    validInput(&totalPlayers, 2, 6);
    
    
    player playerList[totalPlayers];
    boardSetup(board, totalPlayers, playerList, obstacleLocations);

    outputBoard(board, totalPlayers);

    return 0;
}
