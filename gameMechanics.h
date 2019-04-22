/*

*/

#include "gameStructures.h"

/*
    diceRoll() function:
        --> Returns a random integer between 1 and 6 using the rand() function
*/
int diceRoll(void);

/*
    obstacleCheck() function:
        --> Checks if all obstacles are currently still valid obstacles 
        --> Checks if there are tokens in the columns behind each obstacle and if there aren't, sets their status to inactive
*/
void obstacleCheck(cell board[][MAX_COLUMNS], int obstacleLocations[]);

/*
    swap() function:
        --> swaps four elements based on the values of two (x and y) of those elements
        --> Used to sort two arrays based on the values stored in the second array
*/
void swap(player *a, player *b, int *x, int *y);

/*
    sortNetwork() function:
    Goal: To sort an array according based on the data from another array
        --> Uses the Bose-Nelson sorting network algorithm (http://pages.ripco.net/~jgamble/nw.html)
        --> This is a very efficient algorithm, as it is faster than and uses less memory than many other sorting algorithms (e.g. Quicksort)
        --> It's downside is that it only works for up to 6 players
*/
void sortNetwork(int totalPlayers, player p[], int values[totalPlayers]);

/*
    isUsersToken() function:
        --> Checks if the token at the top of the stack of the cell specified matches the colour specified
        --> When calling this function, pass: playerList[i].colour as the userColour argument
*/
bool isUsersToken(int row, int column, enum colour userColour, cell board[][MAX_COLUMNS]);

/*
    game() function:
        -->
*/
void game(cell board[][MAX_COLUMNS], int totalPlayers, bool loadSaveGame);

/*
    gameTurn() function:
        -->
*/
void gameTurn(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int obstacleLocations[], enum gameStatus currentGame);

/*
    validTokenInRow() function:
        -->
*/
bool validTokenInRow(cell board[MAX_ROWS][MAX_COLUMNS], int row, int lower, int upper);

int promptSaveGame(void);
