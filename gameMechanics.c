/*
    C file containing the implementation for functions dealing with token movement and values
    after the game has been initialised and set up.
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameMechanics.h"

int diceRoll(void)
{
    return ((rand() % 6) + 1);
}

void obstacleCheck(cell board[][MAX_COLUMNS], int obstacleLocations[])
{
    bool noTokensInColumn[7] = {true, true, true, true, true, true, true};
    bool flag = false;

    /* First check if every column has no tokens in it */
    for(int column = 0; column < 7; column++)
    {
        for(int row = 0; row < MAX_ROWS; row++)
        {
            if(isStackEmpty(board[row][column].stackPtr) != 1) // If the stack is not empty
            {
                noTokensInColumn[column] = false; // Set the relevant boolean to false
            }
        }
    }

    /* Now check if every column before each obstacle has no tokens in it */
    for(int obstacle = 0; obstacle < 6; obstacle++)
    {
        for(int columnCheck = 0; columnCheck < obstacleLocations[obstacle] && flag == false; columnCheck++)
        {
            if(noTokensInColumn[columnCheck] == false)
            {
                flag = true;
            }
        }

        if(flag == false)
        {
            board[obstacle][obstacleLocations[obstacle]].obstacle = inactive;
        }
    }
}

bool isUsersToken(int row, int column, enum colour userColour, cell board[][MAX_COLUMNS])
{
    if(returnTopValue(board[row][column].stackPtr) == userColour)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game(cell board[][MAX_COLUMNS], int totalPlayers)
{
    /* Set up the game */
    enum gameStatus currentGame = to_start;
    player playerList[totalPlayers];
    int obstacleLocations[6] = {3,6,4,5,2,7}; // The index = row, the value = column

    boardSetup(board, totalPlayers, playerList, obstacleLocations);
    outputBoard(board, totalPlayers);

    currentGame = in_progress;

    /* Playing the game from here on */
    while(currentGame == in_progress)
    {
        //gameTurn(board, totalPlayers, obstacleLocations, currentGame); // DEFINE THIS 
    }

    printInstruction("Game Started!\n");
}

/*
void gameTurn(cell board[][MAX_COLUMNS], int totalPlayers, int obstacleLocations[], enum gameStatus currentGame)
{
    
}
*/