/*
    C file containing the implementation for functions dealing with token movement and values
    after the game has been initialised and set up.
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "tokenMethods.h"

bool isUsersToken(int row, int column, enum colour userColour, cell board[][MAX_COLUMNS])
{
    if(board[row][column].stack[board[row][column].topOfStack].tokenColour == userColour)
    {
        return true;
    }
    else
    {
        return false;
    }
}