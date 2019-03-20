/*
    C file containing the implementation for functions dealing with token movement and values
    after the game has been initialised and set up.
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "tokenMethods.h"

bool isUsersToken(int row, int column, char userColour[8], cell board[][MAX_COLUMNS])
{
    if(strcmp(board[row][column].stack[board[row][column].topOfStack].colour, userColour) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}