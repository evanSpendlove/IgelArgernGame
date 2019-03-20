/*
    Header file containing function prototypes for all functions required to set up the game
    Written by: Evan Spendlove (18492656)
*/

#include "gameStructures.h"
#include "gameIO.h"
#include "random.h"
#include "initialTokens.h"

/*
    getUsername() function:
        --> Prompts the user to input their username
        --> Stores their username in their .username attribute
*/
void getUsername(int i, player playerList[]);

/*
    tokenSetup() function:
        --> Sets the token colour for each token of a user to their chosen colour
*/
void tokenSetup(int playerIndex, player playerList[]);

/*
    colourNotChosen() function:
        --> If more than one user, checks if the colour select by the current user has already been chosen
*/
void colourNotChosen(int* colour, player playerList[], const int totalPlayers);

/*
    getUserColour() function:
        --> Prompts the user to choose a colour for their tokens
        --> Takes input and validates that it isn't a colour already chosen
        --> Assigns the colour chosen to the user's colour attribute
*/
void getUserColour(int i, player playerList[]);

/*
    playerSetup() function:
        --> Calls three functions to get the user's username and colour and to set up their tokens
*/
void playerSetup(player playerList[], const int totalPlayers);

/*
    resetBoard()) function:
        --> Resets all cells in the board to their default values
        --> Sets the obstacle status for each cell to inactive
        --> Sets the stack pointers for each cell in the board to -1 (indicating an empty stack)
*/
void resetBoard(cell board[][MAX_COLUMNS]);

/*
    obstacleSetup() function:
        --> Randomly enables six obstacles on the board, such that each row has one obstacle and each column (for col: 2-7) has one obstacle 
        --> Makes use of fisherShuffle() algorithm
*/
void obstacleSetup(cell board[][MAX_COLUMNS], int obstacleLocations[]);

/*
    boardSetup() function:
        --> Calls three functions to set up the board (Players, Stack, Obstacles)
*/
void boardSetup(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[], int obstacleLocations[]);