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
        -->
*/
void obstacleCheck(cell board[][MAX_COLUMNS], int obstacleLocations[]);

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
void game(cell board[][MAX_COLUMNS], int totalPlayers);
