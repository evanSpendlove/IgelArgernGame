/*
    Game Setup Header file:
        --> Contains the function prototypes for all of the functions in gameSetup.c
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameStructures.h"

/* BOARD SETUP */
    /*
        boardSetup() function:
            --> Calls three functions to set up the board (Players, Stack, Obstacles)
    */
    void boardSetup(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[], int obstacleLocations[]);

    /*
    resetBoard()) function:
        --> Resets all cells in the board to their default values
        --> Sets the obstacle status for each cell to inactive
        --> Sets the stack pointers for each cell in the board to -1 (indicating an empty stack)
    */
    void resetBoard(cell board[][MAX_COLUMNS]);




/* OBSTACLE SETUP */
    /*
        obstacleSetup() function:
            --> Randomly enables six obstacles on the board, such that each row has one obstacle and each column (for col: 2-7) has one obstacle 
            --> Makes use of fisherShuffle() algorithm
    */
    void obstacleSetup(cell board[][MAX_COLUMNS], int obstacleLocations[]);

/* PLAYER SETUP */
    /*
        playerSetup() function:
            --> Calls three functions to get the user's username and colour and to set up their tokens
    */
    void playerSetup(player playerList[], const int totalPlayers);
    /*
        getUsername() function:
            --> Prompts the user to input their username
            --> Stores their username in their .username attribute
    */
    void getUsername(int playerNumber, player playerList[]);

    /*
        getUserColour() function:
            --> Prompts the user to choose a colour for their tokens
            --> Takes input and validates that it isn't a colour already chosen
            --> Assigns the colour chosen to the user's colour attribute
    */
    void getUserColour(int i, player playerList[]);

    /*
        colourNotChosen() function:
            --> If more than one user, checks if the colour select by the current user has already been chosen
    */
    void colourNotChosen(int* colour, player playerList[], const int totalPlayers);

    /*
        tokenSetup() function:
            --> Sets the token colour for each token of a user to their chosen colour
    */
    void tokenSetup(int playerIndex, player playerList[]);

/* INITIAL TOKEN PLACEMENT */
    /*
        initialTokenPlacement() function:
            --> Lets each player place each of their tokens on the board provided certain conditions are met
            --> Each new token must be placed on the stack with the lowest number of tokens on it
            --> A player cannot place a token on top of one of their own tokens (except... edge case)
    */
    void initialTokenPlacement(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[]);

    /*
        isValidPlacement() function:
            --> Checks that the user has selected a row that obeys the conditions specified in the description of initialTokenPlacement()
    */
    int isValidPlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour);

    /*
        onlyAvailablePlacement() function:
            --> Checks for the edge case where a player can only place a token on one of their own tokens (i.e. 5/6 rows full, remaining top = theirs)
            --> Forces the user place a token on their other own token.
    */
    int onlyAvailablePlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour);

