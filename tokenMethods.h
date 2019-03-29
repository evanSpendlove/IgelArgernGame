/*
    Header file containing the function prototypes for dealing with token movement and values
    after the game has been initialised and set up.
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameStructures.h"

/*
    isUsersToken() function:
        --> Checks if the token at the top of the stack of the cell specified matches the colour specified
        --> When calling this function, pass: playerList[i].colour as the userColour argument
*/
bool isUsersToken(int row, int column, char userColour[8], cell board[][MAX_COLUMNS]);
