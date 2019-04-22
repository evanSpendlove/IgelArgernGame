/*
    Game Save and Load Header File:
        --> Contains the function prototypes for the gameSave.c file
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameStructures.h"

/*
    save() function:
        --> Saves all of the current player data and board data to a text file
*/
int save(int totalPlayers, cell board[MAX_ROWS][MAX_COLUMNS], player playerList[totalPlayers], int winningTokens[totalPlayers]);

/*
    saveStack() function:
        --> Used by save() to print a stack to the save file
*/
void saveStack(FILE* file, ListNodePtr node);

/*
    readPlayerCount() function:
        --> Reads the playerCount from a save file for board and playerList[] creation
        --> Need to do this before reading the rest to initialise these variables
*/
int readPlayerCount(void);

/*
    load() function:
        --> Loads player and board data into the game's current variables
*/
int load(int *totalPlayers, cell board[][MAX_COLUMNS], player playerList[], int winningTokens[]);

/*
    loadStack() function:
        --> Reads in a line and parses it for stack info and fills a stack with nodes containing that info
*/
void loadStack(FILE* file, ListNodePtr* node);