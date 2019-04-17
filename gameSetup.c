/*
    Contains the implementation of all of the functions required to set up the game.
    Written by: Evan Spendlove (18492656)
*/

#include "gameSetup.h"

void getUsername(int playerNumber, player playerList[])
{
    printInstruction("Player %d, what is your username?\n", playerNumber+1); // Prompts the user to enter their username
    scanf(" %98[^\n]s", playerList[playerNumber].username); // Scans up to 100 characters or up to a newline and stores it in their username
}

void tokenSetup(int playerIndex, player playerList[])
{   
    for(int token = 0; token < 4; token++) // For every token that a user has (i.e. starts with)
    {
        /*
        playerList[playerIndex].user_stack[token].tokenColour = playerList[playerIndex].userColour; // Sets all of the user's tokens to their chosen colour
        playerList[playerIndex].topOfStack = 3; // Points to the top of the stack, currently the 4th token
        */
        insert(&playerList[playerIndex].userStack, playerList[playerIndex].userColour);
    }
}

void colourNotChosen(int* colour, player playerList[], const int totalPlayers)
{
    int validColourChoice = -1; // Flag used for looping until a valid colour choice has been made
    int availableColours[6] = {0,1,2,3,4,5}; // List of available token colours

    clearInput(); // Clears input buffer

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

    playerList[i].userColour = colourChoice-1; // Copies the colour choice to the user's colour attribute
}

void playerSetup(player playerList[], const int totalPlayers)
{
    for(int i = 0; i < totalPlayers; i++) // For each player in playerList[]
    {
        /* Ask the user for their username*/
        getUsername(i, playerList);
       
        /* Ask the user to choose a colour for their tokens */
        getUserColour(i, playerList);

        /* Set the user stack to NULL */
        playerList[i].userStack = NULL;

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
            board[i][j].stackPtr = NULL; // Set the stack pointer to -1 (indicating an empty stack)
        }
    }
}

int onlyAvailablePlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour)
{
    int invalidRows[6] = {0};
    int invalidRowcounter = 0;

    for(int row = 0; row < MAX_ROWS; row++)
    {
        int stackValue = countStack(board[row][0].stackPtr);
        if(stackValue != ((placedTokenCount/MAX_ROWS)))
        {
            invalidRows[row] = 1;
            invalidRowcounter++;
        }
    }

    if(invalidRowcounter == 5)
    {
        int validRow;
        for(int row = 0; row < MAX_ROWS; row++)
        {
            if(invalidRows[row] != 1)
            {
                validRow = row;
            }
        }
        if(returnTopValue(board[validRow][0].stackPtr) == playerColour)
        {
            return validRow;
        }
    }

    return -1;
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
                printf("Chosen a -1.\n");
            }
            else
            {
                printError("Please select an empty row to minimise stack size.\n"); // Print an appropriate error message to the user
            }
        }

        else if((stackValue == ((placedTokenCount/MAX_ROWS))) && (topValue != playerColour)) // If the chosen row's stack counter is equal to the average token count per row
        {
            validPlacement = true; // Set boolean to true
            printf("Chosen a non-empty stack.\n");
        }

        else if(onlyAvailablePlacement(board, placedTokenCount, playerColour) != -1)
        {
            int onlyValidRow = onlyAvailablePlacement(board, placedTokenCount, playerColour);
            printf("Please select any row except %d:\n", onlyValidRow);
            validInput(&rowChoice, 1, 6);
            if(rowChoice != onlyValidRow)
            {
                validPlacement = true;
                printf("You've picked a valid row (these rules are funny, huh).");
            }
        }

        else
        {
            printError("Please select a valid row to minimise stack size.\n"); // Print an appropriate error message to the user
        }
    }

    return (rowChoice-1); // Returns the (valid) row selected by the user
}

void userPlaceToken(cell board[][MAX_COLUMNS], player playerList[], int player, int row, int column)
{
    /*
    token temp; // Initialises a temporary token
    temp = pop(playerList[player].user_stack, &playerList[player].topOfStack); // Pops the top token from the user's stack and stores it in temp
    push(board[row][column].stack, &board[row][column].topOfStack, temp); // Pushes this token onto the chosen cell stack
    */
    moveToken(&playerList[player].userStack, &board[row][column].stackPtr);
}

void initialTokenPlacement(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[])
{
    int placedTokenCount = 0;
    int rowChoice = -1;

    for(int round = 0; round < 4; round++)
    {
        for(int player = 0; player < totalPlayers; player++)
        {
            printInstruction("%s's turn:\n", playerList[player].username);
            rowChoice = isValidPlacement(board, placedTokenCount, playerList[player].userColour);
            userPlaceToken(board, playerList, player, rowChoice, 0);
            placedTokenCount++;
        }
    }

}

void obstacleSetup(cell board[][MAX_COLUMNS], int obstacleLocations[])
{
    for(int row = 0; row < MAX_ROWS; row++)
    {
        board[row][obstacleLocations[row]].obstacle = active;
    }
}

void boardSetup(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[], int obstacleLocations[])
{
    resetBoard(board); // Sets the board cells to default values
    obstacleSetup(board, obstacleLocations); // Sets up the obstacles on the board
    playerSetup(playerList, totalPlayers); // Sets up the players and their data
    initialTokenPlacement(board, totalPlayers, playerList); // Sets up the initial token placement of players' tokens
}