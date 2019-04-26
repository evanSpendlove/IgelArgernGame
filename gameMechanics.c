/*
    Game Mechanics C file:
        --> Contains game control and management functions, and various utility functions which allow game mechanics to be implemented
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameMechanics.h"
#include "gameSave.h"

/* GAME CONTROL FUNCTIONS */
void game(cell board[][MAX_COLUMNS], int totalPlayers, bool loadSaveGame)
{
    /* Set up the game */
    enum gameStatus currentGame = to_start; // Game status
    int obstacleLocations[6] = {3,6,4,5,2,7}; // The index = row, the value = column

    player playerList[totalPlayers]; // List of players
    int winningTokens[totalPlayers]; // Winning token count of each player

    memset(winningTokens, 0, sizeof(winningTokens[0])*totalPlayers); // Set the default value for all elements of winningTokens[] to 0


    /* Checking if loading a saved game, or starting a new game */


    if(loadSaveGame == 1) // If the user wants a saved game to be loaded
    {
        load(&totalPlayers, board, playerList, winningTokens); // load the game from save.txt
    }
    else // Otherwise, they are starting a new game
    {
        boardSetup(board, totalPlayers, playerList, obstacleLocations); // Set up the new game with players and a board
    }


    outputBoard(board, totalPlayers); // Output the current board

    currentGame = in_progress; // Update the game status to in_progres


    /* Playing the game from here on */


    while(currentGame == in_progress) // While the game is in_progress
    {
        for(int currentPlayer = 0; currentPlayer < totalPlayers; currentPlayer++) // For each player in the playerList[]
        {
            gameTurn(board, totalPlayers, playerList, currentPlayer, winningTokens, obstacleLocations, currentGame); // Call gameTurn()
            
            if(winningTokens[max(totalPlayers, winningTokens)] == 3) // If any player has three tokens in the final column (i.e. they've won)
            {
                currentGame = complete; // Set game status to complete
                printWinners(totalPlayers, winningTokens, playerList); // Print the winners of the game
                break; // End the loop
            }
        }

        if(promptSaveGame() == 1) // If the user has requested to save the game
        {
            save(totalPlayers, board, playerList, winningTokens); // Save the game
            currentGame = saved; // Set the game status to saved
        }      
    }
}

void gameTurn(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int obstacleLocations[], enum gameStatus currentGame)
{
    int choice, dieSelectedRow;

    /* Part 1: Rolling the dice */
    printInstruction("It's "); // Prompts the user to roll the dice
    printUsername(playerList[currentPlayer]); // Prints the current player's username in their chosen colour (Helpful: Remind you of what colour you are)
    printInstruction("'s turn! Please type 1 to roll the dice: ");

    validInput(&choice, 1, 1); // Validates that they inputted a 1 to roll the dice
    dieSelectedRow = diceRoll(); // stores the result of the rolled dice

    printInstruction("You rolled a %d!\n", dieSelectedRow); // Updates user with the results of their roll

    /* Part 2: Moving sideways */
    moveSideways(board, totalPlayers, playerList, currentPlayer); // Calls moveSideways()

    /* Part 3: Moving a token forwards */
    moveForwards(board, totalPlayers, playerList, currentPlayer, winningTokens, dieSelectedRow); // Calls moveForwards()

    obstacleCheck(board, obstacleLocations); // Checks if all obstacles are still valid
}

void moveSideways(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer)
{
    int choice = -1; // Used for storing user input

    printInstruction("Do you want to move a token sideways (0 for No, 1 for Yes)? "); // Prompt user to move a token sideways
    validInput(&choice, 0, 1); // Take user input

    if(choice == 1) // If the user wants to move a token sideways
    {
        int row = 0, column = 0; // Initialise row and column
        bool validTokenChoice = false; // Initialise boolean for looping until a valid token choice is made

        while(validTokenChoice != true) // While the user hasn't selected a valid token to move
        {
            printInstruction("In which row is this token? "); // Prompt user to select a row
            validInput(&row, 1,6); // Take user input and store in row

            printInstruction("In which column is this token? "); // Prompt user to select a column
            validInput(&column, 1, 9); // Take user input and store in column

            validTokenChoice = isUsersToken(row-1, column-1, playerList[currentPlayer].userColour, board); // Verify that the user owns the chosen token

            validTokenChoice = validTokenInRow(board, row-1, column-1, column-1); // Checks if the token exists and that it isn't on an obstacle

            if(validTokenChoice == false) // If either the user doesn't own the token, or it isn't a valid token (tested by validTokenInRow)
            {
                printError("Invalid token choice, please pick a token of your colour on top of a stack that isn't on an obstacle.\n"); // Print an error
            }
        }

        int newRow = -1; // Set newRow to -1

        if(row == 1) // If the row chosen is the first row
        {
            printInstruction("You can only move this token down one row (to row: %d), press 1 to confirm: ", row+1); // The token can only be moved down
            validInput(&newRow, 1, 1); // Only accept 1 as input
        }
        else if(row == 6) // If the row chosen is the final row
        {
            printInstruction("You can only move this token up one row (to row: %d), press 0 to confirm: ", row-1); // The token can only be moved up one row
            validInput(&newRow, 0, 0); // Only accept 0 as input
        }
        else // Otherwise, the row is somewhere in the middle
        {
            printInstruction("Would you like to move the token up one row (row: %d), or down one row (row: %d)\n(0 for up, 1 for down)? ", row-1, row+1); // Prompt user
            validInput(&newRow, 0, 1); // Accept valid input
        }
        
        if(newRow == 0) // If they want to move the token up a row
        {
            int check = moveToken(&board[row-1][column-1].stackPtr, &board[row-2][column-1].stackPtr); // Move it up (-2) a row
            while(check == 0{
                printError("Error occured during movement of token, trying again\n\n");
                check = moveToken(&board[row-1][column-1].stackPtr, &board[row-2][column-1].stackPtr);
            } 
        }
        else // Otherwise, they want to move it down a row
        {
            int check2 = moveToken(&board[row-1][column-1].stackPtr, &board[row][column-1].stackPtr); // Move it down (+-0) a row
            while(check2 == 0){
                printError("An error occured during movement of a token, trying again\n\n");
                check2 = moveToken(&board[row-1][column-1].stackPtr, &board[row][column-1].stackPtr);
            }
        }
       
        outputBoard(board, totalPlayers); // Output the board after the token has been moved sideways 

    }
}

void moveForwards(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int dieSelectedRow)
{
    int choice = -1; // Choice for storing user input
    bool moveIsPossible = validTokenInRow(board, dieSelectedRow-1, 0, 7); // Boolean which stores whether or not there is any token that can be moved in the dieSelectedRow
    bool validMoveMade = false; // Boolean for tracking if a valid forwards move has been made

    if(moveIsPossible == true) // If there is a token that can be moved in this row
    {
        while(validMoveMade != true) // While the user hasn't selected a valid move to be made
        {
            printInstruction("Which token in row %d do you wish to move forward (Type the column number)? ", dieSelectedRow); // Prompt user
            validInput(&choice, 1, 8); // Take player input

            if(validTokenInRow(board, dieSelectedRow-1, choice-1, choice-1) == true) // If the chosen token is a valid token choice
            {
                if(choice == 8) // If the token is to be moved into the final column (i.e. to become a winning token)
                {
                    updateWinningTokens(board, totalPlayers, playerList, winningTokens, dieSelectedRow-1, choice-1); // Update winningTokens[] with this token
                }

                if(moveToken(&board[dieSelectedRow-1][choice-1].stackPtr, &board[dieSelectedRow-1][choice].stackPtr) == 0){
                    printError("An error occured during token move, breaking\n\n");
                    return;
                } // Move the token
                outputBoard(board, totalPlayers); // Output the new bord

                validMoveMade = true; // Update boolean
            }
            else // Otherwise, it isn't a valid token
            {
                printError("Sorry, there is not token that can be moved in this row/column, please select another.\n"); // Print an error
            }
        } 
    }
    else // Otherwise, there are no tokens in this row that can be moved
    {
        printError("Sorry, there are no tokens in this row that you can move.\n"); // Print an error
    }
}

int promptSaveGame(void)
{
    int choice = 0; // Stores user input

    printInstruction("Would you like to save the current game position and exit the game?\n(1 for yes, 0 for no)\n"); // Prompts user to save game
    validInput(&choice, 0, 1); // Records their response within the range 0 and 1

    return choice; // Returns the user's choice
}

/* GAME MANAGEMENT FUNCTIONS */
void updateWinningTokens(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int winningTokens[], int row, int column)
{
    int tokenOwner = -1; // Used for the storing the index of the player who owns the winning token

    for(int player = 0; player < totalPlayers && tokenOwner == -1; player++) // Looping through all players while a tokenOwner hasn't been found
    {
        if(isUsersToken(row, column, playerList[player].userColour, board) == 1) // If the player owns the winning token
        {
            tokenOwner = player; // Set the player as the token Owner
        }
    }

    winningTokens[tokenOwner]++; // Increment the winning token count of the token owner
}

void printWinners(int totalPlayers, int winningTokens[totalPlayers], player playerList[totalPlayers])
{
    sortNetwork(totalPlayers, playerList, winningTokens); // Calls sortNetwork() and passes the player data 

    /* Print the results screen */
    printInstruction("===================================================\n"); 
    printInstruction("                 GAME RESULTS                      \n");
    printInstruction("   Ranking       Player               Token Count  \n");

    for(int player = 0; player < totalPlayers; player++) // For each player
    {
        printInstruction("      %d          %-26s%d\n", player+1, playerList[player].username, winningTokens[player]); // Print the player's rank, name and winningTokenCount
    }

    printInstruction("\n\t\tThe winner was: %s\n", playerList[0].username); // Print the winner
    printInstruction("===================================================\n"); // End results screen
}

bool isUsersToken(int row, int column, enum colour userColour, cell board[][MAX_COLUMNS])
{
    if(returnTopValue(board[row][column].stackPtr) == userColour) // If the colour of the token passed by argument is the same as the user colour
    {
        return true; // Return true
    }
    else
    {
        return false; // Else, return false (i.e. not the user-specified's token)
    }
}

bool validTokenInRow(cell board[MAX_ROWS][MAX_COLUMNS], int row, int lower, int upper)
{
    bool validToken = false; // Set boolean to false by default

    for(int column = lower; column <= upper && validToken == false; column++) // Looping through the columns from the lower bound to the upper bound (inclusive), provided no validToken has been found
    {
        if(isStackEmpty(board[row][column].stackPtr) != 1 && board[row][column].obstacle == inactive) // If the stack is not empty and there isn't an obstacle in the square
        {
            validToken = true; // Set the boolean to true
        }
    }

    return validToken; // Return the boolean validToken
}

void obstacleCheck(cell board[][MAX_COLUMNS], int obstacleLocations[])
{
    bool noTokensInColumn[7] = {true, true, true, true, true, true, true}; // Array of booleans for keeping track of empty columns
    bool flag = false; // Flag used when checking noTokensInColumn[] for each obstacle

    /* First check if every column has no tokens in it */
    for(int column = 0; column < 7; column++) // For each column
    {
        for(int row = 0; row < MAX_ROWS; row++) // For each row in that column
        {
            if(isStackEmpty(board[row][column].stackPtr) != 1) // If the stack is not empty
            {
                noTokensInColumn[column] = false; // Set the relevant boolean to false
            }
        }
    }

    for(int obstacle = 0; obstacle < 6; obstacle++) // For each obstacle
    {
        for(int columnCheck = 0; columnCheck < obstacleLocations[obstacle] && flag == false; columnCheck++) // Checking each column up to the obstacle
        {
            if(noTokensInColumn[columnCheck] == false) // If there are tokens in that column
            {
                flag = true; // Set the flag to true
            }
        }

        if(flag == false) // If the flag is still false (i.e. no tokens in every column before the obstacle)
        {
            board[obstacle][obstacleLocations[obstacle]].obstacle = inactive; // Set the obstacle to inactive
        }

        flag = false; // Reset flag
    }
}

/* UTILITY FUNCTIONS */

int max(const int size, const int array[size])
{
    int max = 0; // Integer for storing index of current maximum value

    for(int i = 0; i < size; i++) // Loop through each element of the array
    {
        if(array[i] > array[max]) // If the current element is greater than the current max
        {
            max = i; // Set the current element as the new max
        }
    }
    return max; // Return the index of the max element found
}

int diceRoll(void)
{
    return ((rand() % 6) + 1); // Return a random number between 1 and 6
}

void swap(player *a, player *b, int *x, int *y)
{
    if(*x < *y) // If the winning tokens count of player a is greater than that of player b
    {
        /* Swap each player in the list */
        player temp = *a; // Set temp to a
        *a = *b; // Set a to b
        *b = temp; // Set b to temp (i.e. a)

        /* Swap each player's token count */
        int tempInt = *x; 
        *x = *y;
        *y = tempInt;
    }
}

void sortNetwork(int totalPlayers, player p[], int values[totalPlayers])
{
    switch(totalPlayers) /* Uses different sorting networks based on the number of players */
    {
        case 2: /* Sorting Network for 2 inputs */
            swap(&p[0], &p[1], &values[0], &values[1]); /* Only one comparator needed when two inputs */
            break; /* Exit switch */
        case 3: /* Sorting Network for 3 inputs */
            swap(&p[1], &p[2], &values[1], &values[2]);
            swap(&p[0], &p[2], &values[0], &values[2]);
            swap(&p[0], &p[1], &values[0], &values[1]);
            break; /* Exit switch */
        case 4: /* Sorting Network for 4 inputs */
            swap(&p[0], &p[1], &values[0], &values[1]);
            swap(&p[2], &p[3], &values[2], &values[3]);
            swap(&p[0], &p[2], &values[0], &values[2]);
            swap(&p[1], &p[3], &values[1], &values[3]);
            swap(&p[1], &p[2], &values[1], &values[2]);
            break; /* Exit switch */
        case 5: /* Sorting Network for 5 inputs */
            swap(&p[0], &p[1], &values[0], &values[1]);
            swap(&p[3], &p[4], &values[3], &values[4]);
            swap(&p[2], &p[4], &values[2], &values[4]);
            swap(&p[2], &p[3], &values[2], &values[3]);
            swap(&p[0], &p[3], &values[0], &values[3]);
            swap(&p[0], &p[2], &values[0], &values[2]);
            swap(&p[1], &p[4], &values[1], &values[4]);
            swap(&p[1], &p[3], &values[1], &values[3]);
            swap(&p[1], &p[2], &values[1], &values[2]);
            break; /* Exit switch */
        case 6: /* Sorting Network for 6 inputs */
            swap(&p[1], &p[2], &values[1], &values[2]);
            swap(&p[0], &p[2], &values[0], &values[2]);
            swap(&p[0], &p[1], &values[0], &values[1]);
            swap(&p[4], &p[5], &values[4], &values[5]);
            swap(&p[3], &p[5], &values[3], &values[5]);
            swap(&p[3], &p[4], &values[3], &values[4]);
            swap(&p[0], &p[3], &values[0], &values[3]);
            swap(&p[1], &p[4], &values[1], &values[4]);
            swap(&p[2], &p[5], &values[2], &values[5]);
            swap(&p[2], &p[4], &values[2], &values[4]);
            swap(&p[1], &p[3], &values[1], &values[3]);
            swap(&p[2], &p[3], &values[2], &values[3]);
            break; /* Exit switch */
        default:
            printError("Error: Cannot sort 1 player or more than 6 players.\n"); /* If the number of players is <2 or >6, then there's a problem */
    }
}

