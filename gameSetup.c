/*
    Contains the implementation of all of the functions required to set up the game.
    Written by: Evan Spendlove (18492656)
*/

#include "gameSetup.h"

void getUsername(int i, player playerList[])
{
    printInstruction("Player %d, what is your username?\n", i+1); // Prompts the user to enter their username
    scanf(" %98[^\n]s", playerList[i].username); // Scans up to 100 characters or up to a newline and stores it in their username
}

void tokenSetup(int playerIndex, player playerList[])
{
    for(int token = 0; token < 4; token++) // For every token that a user has (i.e. starts with)
    {
        strcpy(playerList[playerIndex].user_stack[token].colour, playerList[playerIndex].colour); // Sets all of the user's tokens to their chosen colour
    }

    playerList[playerIndex].topOfStack = 3; // Points to the top of the stack, currently the 4th token
}

void colourNotChosen(int* colour, player playerList[], const int totalPlayers)
{
    int validColourChoice = -1; // Flag used for looping until a valid colour choice has been made
    char tokenColours[6][8] = {"Red", "Blue", "Green", "Magenta", "Cyan", "Yellow"}; // List of available token colours

    clearInput(); // Clears input buffer

    if(totalPlayers > 1) // If there is more than one user
    {
        while(validColourChoice != 1) // While the user has not inputted a valid colour choice
        {
            validColourChoice = -1; // Resets validColourChoice flag

            validInput(colour, 1, 6); // Validates that the user has inputted an integer between 1 and 6
            
            for(int player = 0; player < totalPlayers && validColourChoice != 0; player++) // For each player in playerList
            {
                if(strcmp(tokenColours[*colour-1], playerList[player].colour) == 0) // If the colour chosen matches an existing colour
                {
                    validColourChoice = 0; // The colour is already chosen
                    printInstruction("Sorry, this colour is already chosen. Please choose another:\n"); // Print an error to the user
                }
            }
            if(validColourChoice == -1) // If the colour is not already chosen
            {
                validColourChoice = 1; // The user has entered a valid colour choice
            }
        }
    }
    else // Otherwise there is only one user, so they can choose any colour
    {
        validInput(colour, 1, 6); // Validates that the user has inputted an integer between 1 and 6
    }
}

void getUserColour(int i, player playerList[])
{
    char tokenColours[6][8] = {"Red", "Blue", "Green", "Magenta", "Cyan", "Yellow"}; // List of available token colours
    int colourChoice = 0; // Integer to store the user's choice of colour (used for indexing tokenColours)

    printInstruction("%s, which colour do you wish to be?\n(Type the corresponding number to select a colour)\n", playerList[i].username); // Prompts the user to select a colour
    for(int colour = 0; colour < 6; colour++) // For each colour in tokenColours
    {
        printInstruction("%d: %s\n", colour+1, tokenColours[colour]); // Print the colour as an option
    }

    colourNotChosen(&colourChoice, playerList, i+1); // Verifies that the colour selected by the user is not already chosen

    strcpy(playerList[i].colour, tokenColours[(colourChoice-1)]); // Copies the colour choice to the user's colour attribute
}

void playerSetup(player playerList[], const int totalPlayers)
{
    for(int i = 0; i < totalPlayers; i++) // For each player in playerList[]
    {
        /* Ask the user for their username*/
        getUsername(i, playerList);
       
        /* Ask the user to choose a colour for their tokens */
        getUserColour(i, playerList);

        /* Sets up the user's tokens */
        tokenSetup(i, playerList); 
    }
}


void resetBoard(cell board[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++) // For each row in the row
    {
        for(int j = 0; j < MAX_COLUMNS; j++) // For each column in the row
        {
            board[i][j].obstacle = inactive; // Sets the obstacle status for this cell to inactive
            board[i][j].topOfStack = -1; // Set the stack pointer to -1 (indicating an empty stack)
        }
    }
}

void obstacleSetup(cell board[][MAX_COLUMNS], int obstacleLocations[])
{
    int i; /* Counter for looping over the array */
    int columnSelection[6] = {2,3,4,5,6,7}; // Array of all valid columns for an obstacle

    fisherShuffle(columnSelection, 6); /* Calls the fisherShuffle() function to shuffle the array properly */

    for(i = 0; i < MAX_ROWS; i++) // For each row
    {
        board[i][columnSelection[i]].obstacle = active; // Set an obstacle in a random column
        obstacleLocations[i] = columnSelection[i]; // Stores the locations of each obstacle in an array
    }
}

void boardSetup(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[], int obstacleLocations[])
{
    resetBoard(board); // Sets the board cells to default values
    obstacleSetup(board, obstacleLocations); // Sets up the obstacles on the board
    playerSetup(playerList, totalPlayers); // Sets up the players and their data
    initialTokenPlacement(board, totalPlayers, playerList); // Sets up the initial token placement of players' tokens
}