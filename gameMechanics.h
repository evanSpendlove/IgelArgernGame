/*
    Game Mechanics Header file:
        --> Contains the function prototypes for the gameMechanics.c file
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameStructures.h"

/* GAME CONTROL */
    /*
        game() function:
            --> Initialises game variables
            --> Calls load() to load a saved game if requested by the user
            --> Calls save() to save the game if requested by a player
            --> While the game is in_progress and no one has won/requested to save, calls gameTurn()
    */
    void game(cell board[][MAX_COLUMNS], int totalPlayers, bool loadSaveGame);

    /*
        gameTurn() function:
            --> Lets the user roll the dice, move a token sideways and move a token forwards
            --> Checks if the obstacles are all still valid
            --> Calls updateWinningTokens() if a token is placed into the final column
    */
    void gameTurn(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int obstacleLocations[], enum gameStatus currentGame);

    /*
        moveSideways() function:
            --> Asks the user if they want to move a token sideways
            --> If they do, allows them to provided the token they choose is a valid token
    */
    void moveSideways(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer);

    /*
        moveForwards() function:
            --> Allows the user to move a token forwards in a column of their choice based on the row selected by the dice
            --> Checks if there are any tokens in the row that can be moved before offering the choice to the player
    */
    void moveForwards(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int dieSelectedRow);

    /*
        promptSaveGame() function:
            --> Prompts the user to save the game
            --> Returns 1 if they choose to save, or 0 if they don't
    */
    int promptSaveGame(void);

/* GAME MANAGEMENT */

    /*
        updateWinningTokens() function:
            --> Updates the winningTokens[] array
            --> Increments the winningTokenCount of the player who owns the token that is now in the final row
    */
    void updateWinningTokens(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int winningTokens[], int row, int column);

    /*
        printWinners() function:
            --> Prints the players in order of their rank (based on their total tokens in the final column)
            --> Prints the winner of the game
    */
    void printWinners(int totalPlayers, int winningTokens[totalPlayers], player playerList[totalPlayers]);
    
    /*
        isUsersToken() function:
            --> Checks if the token at the top of the stack of the cell specified matches the colour specified
            --> When calling this function, pass: playerList[i].colour as the userColour argument
    */
    bool isUsersToken(int row, int column, enum colour userColour, cell board[][MAX_COLUMNS]);

    /*
        validTokenInRow() function:
            --> Verifies that there is a token in the specified row (range) that:
                    - Isn't on an obstacle
                    - Actually exists (i.e. the cell stack isn't empty)
    */
    bool validTokenInRow(cell board[MAX_ROWS][MAX_COLUMNS], int row, int lower, int upper);

    /*
        obstacleCheck() function:
            --> Checks if all obstacles are currently still valid obstacles 
            --> Checks if there are tokens in the columns behind each obstacle and if there aren't, sets their status to inactive
    */
    void obstacleCheck(cell board[][MAX_COLUMNS], int obstacleLocations[]);

/* UTILITY FUNCTIONS */
    /*
        max() function:
            --> Returns the maximum value of an integer array
    */
    int max(const int size, const int array[size]);

    /*
        diceRoll() function:
            --> Returns a random integer between 1 and 6 using the rand() function
    */
    int diceRoll(void);

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
