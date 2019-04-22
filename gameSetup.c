/*
    Contains the implementation of all of the functions required to set up the game.
    Written by: Evan Spendlove (18492656)
*/

#include "gameSetup.h"
#include "gameIO.h"
#include "stackMethods.h"

/* BOARD SETUP */
void boardSetup(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[], int obstacleLocations[])
{
    resetBoard(board); // Sets the board cells to default values
    obstacleSetup(board, obstacleLocations); // Sets up the obstacles on the board
    playerSetup(playerList, totalPlayers); // Sets up the players and their data
    initialTokenPlacement(board, totalPlayers, playerList); // Sets up the initial token placement of players' tokens
}

void resetBoard(cell board[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++) // For each row in the row
    {
        for(int j = 0; j < MAX_COLUMNS; j++) // For each column in the row
        {
            board[i][j].obstacle = inactive; // Sets the obstacle status for this cell to inactive
            board[i][j].stackPtr = NULL; // Set the stack pointer to NULL (indicating an empty stack)
        }
    }
}

/* OBSTACLE SETUP */
void obstacleSetup(cell board[][MAX_COLUMNS], int obstacleLocations[])
{
    for(int row = 0; row < MAX_ROWS; row++) // For each row on the board
    {
        board[row][obstacleLocations[row]].obstacle = active; // Set the relevant obstacle (from obstacleLocations[]) to active
    }
}

/* PLAYER SETUP */
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

void getUsername(int playerNumber, player playerList[])
{
    char buffer[100]; // Buffer for reading in user input
    int letter = 0; // Letter counter for looping through buffer[] string
    bool noSpacesInName = true; // Boolean for keeping track of spaces in username
    bool validUsername = false; // Boolean for ensuring validUsername is inputted before moving on

    while(validUsername != true) // While the user hasn't 
    {
        printInstruction("Player %d, what is your username?\n(Please do not put spaces in your name)\n", playerNumber+1); // Prompts the user to enter their username
        scanf(" %98[^\n]s", buffer); // Scans up to 100 characters or up to a newline and stores it in their username
        clearInput(); // Clear input buffer (not buffer[] array)


        while(letter < 100 && buffer[letter] != '\0' && noSpacesInName == true) // While not at the end of the array and a space has not been found
        {
            if(buffer[letter] == ' ') // If the current letter is a space
            {
                noSpacesInName = false; // Update boolean to false
            }
            letter++; // Increment letter
        }

        if(noSpacesInName == true) // If no space was found in the username
        {
            strcpy(playerList[playerNumber].username, buffer); // Copy the buffer to the player's username
            printInstruction("Username successfully set!\n"); // Print that the username was set
            validUsername = true; // Set boolean to true
        }
        else // Otherwise, a space was found
        {
            printError("No spaces are allowed in usernames\n"); // Print an error
            noSpacesInName = true; // Reset boolean
        }
    }
}

void getUserColour(int i, player playerList[])
{
    int colourChoice = 0; // Integer to store the user's choice of colour (used for indexing tokenColours)

    printInstruction("%s, which colour do you wish to be?\n(Type the corresponding number to select a colour)\n", playerList[i].username); // Prompts the user to select a colour
    
    printColours(); // Prints the list of colours to the user

    colourNotChosen(&colourChoice, playerList, i+1); // Verifies that the colour selected by the user is not already chosen

    playerList[i].userColour = colourChoice-1; // Copies the colour choice to the user's colour attribute
}

void colourNotChosen(int* colour, player playerList[], const int totalPlayers)
{
    int validColourChoice = -1; // Flag used for looping until a valid colour choice has been made
    int availableColours[6] = {0,1,2,3,4,5}; // List of available token colours

    if(totalPlayers > 1) // If there is more than one user
    {
        while(validColourChoice != 1) // While the user has not inputted a valid colour choice
        {
            validColourChoice = -1; // Resets validColourChoice flag

            validInput(colour, 1, 6); // Validates that the user has inputted an integer between 1 and 6
            
            for(int player = 0; player < totalPlayers && validColourChoice != 0; player++) // For each player in playerList
            {
                if(availableColours[*colour-1] == playerList[player].userColour) // If the colour chosen matches an existing colour
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

void tokenSetup(int playerIndex, player playerList[])
{   
    /* Set the user stack to NULL */
    playerList[playerIndex].userStack = NULL;

    for(int token = 0; token < 4; token++) // For every token that a user has (i.e. starts with)
    {
        insert(&playerList[playerIndex].userStack, playerList[playerIndex].userColour); // Insert a token to the user's stack
    }
}

/* INITIAL TOKEN PLACEMENT */
void initialTokenPlacement(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[])
{
    int placedTokenCount = 0; // Number of tokens that have been placed on the board
    int rowChoice = -1; // Default row choice to -1

    for(int i = 0; i < 4; i++) // Loop four times (four tokens per player)
    {
        for(int player = 0; player < totalPlayers; player++) // For each player
        {
            printUsername(playerList[player]); // Print the player's username
            printInstruction("'s turn:\n", playerList[player].username); // Print that it's their turn

            rowChoice = isValidPlacement(board, placedTokenCount, playerList[player].userColour); // Assign a valid token placement to rowChoice by calling isValidPlacement() to prompt user and supply input
            moveToken(&playerList[player].userStack, &board[rowChoice][0].stackPtr); // Move the token from the player's stack onto their chosen board cell stack
            placedTokenCount++; // Increment placedTokenCount
        }
    }

}

int isValidPlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour)
{
    bool validPlacement = false; // Flag for valid placement status
    int rowChoice = 0; // Integer variable for storing user's choice of row

    while(validPlacement != true) // While the user has not selected a valid row
    {
        printInstruction("Which row do you wish to place your token in?\n"); // Instruct the user to pick a row
        validInput(&rowChoice, 1, 6); // Validate that their input is an integer and lies within the range 1 - 6
        int stackValue = countStack(board[rowChoice-1][0].stackPtr);
        int topValue = returnTopValue(board[rowChoice-1][0].stackPtr);

        if(placedTokenCount < 6) // If not all of the rows have a token on them
        {
            if(isStackEmpty(board[rowChoice-1][0].stackPtr) == 1) // Only allow user to pick a row that has an empty stack
            {
                validPlacement = true; // Set boolean to true
            }
            else
            {
                printError("Please select an empty row to minimise stack size.\n"); // Print an appropriate error message to the user
            }
        }

        else if((stackValue == ((placedTokenCount/MAX_ROWS))) && (topValue != playerColour)) // If the chosen row's stack counter is equal to the average token count per row
        {
            validPlacement = true; // Set boolean to true
        }

        else if(onlyAvailablePlacement(board, placedTokenCount, playerColour) != -1) // If there is only one row available to place a token in, and the top token is one of the user's tokens...
        {
            int onlyValidRow = onlyAvailablePlacement(board, placedTokenCount, playerColour); // Set the onlyValidRow to the return value of onlyAvailablePlacement

            printInstruction("You can only place your token in row %d, to minimise stack height.\n", onlyValidRow+1); // Print explanation

            rowChoice = onlyValidRow + 1; // Set rowChoice to the onlyValidRow + 1 (b/c users select from range 1 - 6)

            validPlacement = true; // They made a valid placement
        }

        else
        {
            printError("Please select a valid row to minimise stack size.\n"); // Print an appropriate error message to the user
        }
    }

    return (rowChoice-1); // Returns the (valid) row selected by the user
}

int onlyAvailablePlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour)
{
    bool invalidRows[6] = {0}; // Used for tracking whether or not a user can place a token in each row
    int invalidRowcounter = 0; // Counter for the number of rows a user can't place a token in

    for(int row = 0; row < MAX_ROWS; row++) // For each row
    {
        int stackValue = countStack(board[row][0].stackPtr); // Store the count of tokens placed in this stack

        if(stackValue != ((placedTokenCount/MAX_ROWS))) // If the token count is not equal to the lowest stack
        {
            invalidRows[row] = true; // Set the row to invalid
            invalidRowcounter++; // Increment the counter of invalid rows
        }
    }

    if(invalidRowcounter == 5) // If 5 of the 6 (MAX_ROWS == 6) rows are invalid
    {
        int validRow; // Stores the only valid row

        for(int row = 0; row < MAX_ROWS; row++) // Loop through the rows
        {
            if(invalidRows[row] != true) // If the row is not invalid (i.e. is valid)
            {
                validRow = row; // Set the (only) validRow to this row
            }
        }

        if(returnTopValue(board[validRow][0].stackPtr) == playerColour) // If this row's top token is of the same colour as the current player
        {
            return validRow; // Return this row
        }
    }

    return -1; // Otherwise, return -1 (indicating this edge case did not arise)
}
