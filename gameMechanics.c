/*
    C file containing the implementation for functions dealing with token movement and values
    after the game has been initialised and set up.
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/

#include "gameMechanics.h"
#include "gameSave.h"

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

// Delete if not implementing the new obstacle check
int sumArray(const int size, const bool array[])
{
    int sum = 0; // Used for storing the sum of the elements of the array

    for(int i = 0; i < size; i++) // Loops through each element of the array
    {
        sum += array[i]; // Adds the array element to the sum
    }

    return sum; // Returns the sum of the array
}

// COMMENT AND FINISH
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

    for(int i = 0; i < 7; i++)
    {
        //printf("Obstacle in Col %d: %d\n", i, noTokensInColumn[i]);
    }

    #ifdef newObstacleMethod

    /* Now check if every column before each obstacle has no tokens in it */

    // Starting with last obstacle.

    for(int obstacle = 7; obstacle > 2; obstacle--)
    {
        if(sumArray(obstacle, noTokensInColumn) == 0)
        {

        }
    }

    #endif

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
            //printf("Flag for %d, %d is false!\n", obstacle, obstacleLocations[obstacle]);
            board[obstacle][obstacleLocations[obstacle]].obstacle = inactive;
            //printf("Status of obstacle at (%d/%d) is: %d\n", obstacle, obstacleLocations[obstacle], board[obstacle][obstacleLocations[obstacle]].obstacle);
        }

        flag = false; // Reset flag
    }
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
    switch(totalPlayers) /* Uses different sorting networks based on the number of users */
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
            printf("Error: Cannot sort 1 user or more than 6 users.\n"); /* If the number of users is <2 or >6, then there's a problem */
    }
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
        printWinners(totalPlayers, winningTokens, playerList);
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
            if(winningTokens[max(totalPlayers, winningTokens)] == 3) // If any user has three tokens in the final column (i.e. they've won)
            {
                currentGame = complete; // Set game status to complete
                printWinners(totalPlayers, winningTokens, playerList); // Print the winners of the game
                break; // End the loops
            }
        }

        if(promptSaveGame() == 1) // If the user has request to save the game
        {
            save(totalPlayers, board, playerList, winningTokens); // Save the game
            currentGame = saved; // Set the game status to saved
        }      
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

// COMMENT
void gameTurn(cell board[][MAX_COLUMNS], int totalPlayers, player playerList[totalPlayers], int currentPlayer, int winningTokens[], int obstacleLocations[], enum gameStatus currentGame)
{
    int choice, dieSelectedRow;

    /* Part 1: Rolling the dice */
    printInstruction("It's "); // Prompts the user to roll the dice
    printUsername(playerList[currentPlayer]); // Prints the current player's username in their chosen colour (Helpful: Remind you of what colour you are)
    printInstruction("'s turn! Please type 1 to roll the dice: ");

    validInput(&choice, 1, 1);
    printError("Please select which row you desire: ");
    validInput(&dieSelectedRow, 1, 6);

    #ifdef BUG
        validInput(&choice, 1, 1); // Validates that they inputted a 1 to roll the dice
        dieSelectedRow = diceRoll(); // stores the result of the rolled dice
    #endif
    printInstruction("You rolled a %d!\n", dieSelectedRow);

    /* Part 2: Moving sideways */
    printInstruction("Do you want to move a token sideways (0 for No, 1 for Yes)? ");
    validInput(&choice, 0, 1);

    if(choice == 1)
    {
        int row = 0, column = 0;
        bool validTokenChoice = false;

        while(validTokenChoice != true)
        {
            printInstruction("In which row is this token? ");
            validInput(&row, 1,6);

            printInstruction("In which column is this token? ");
            validInput(&column, 1, 9);

            validTokenChoice = isUsersToken(row-1, column-1, playerList[currentPlayer].userColour, board);

            if(validTokenChoice == false)
            {
                printInstruction("Invalid token choice, please pick a token of your colour on top of a stack.\n");
            }
        }

        int newRow = -1;

        if(row == 1)
        {
            printInstruction("You can only move this token down one row (to row: %d), press 1 to confirm: ", row-1);
            validInput(&newRow, 1, 1);
        }
        else if(row == 6)
        {
            printInstruction("You can only move this token up one row (to row: %d), press 0 to confirm: ", row+1);
            validInput(&newRow, 0, 0);
        }
        else
        {
            printInstruction("Would you like to move the token up one row (row: %d), or down one row (row: %d)\n(0 for up, 1 for down)? ", row-1, row+1);
            validInput(&newRow, 0, 1);   
        }
        
        if(newRow == 0)
        {
            moveToken(&board[row-1][column-1].stackPtr, &board[row-2][column-1].stackPtr);
        }
        else
        {
            moveToken(&board[row-1][column-1].stackPtr, &board[row][column-1].stackPtr);
        }
       
        outputBoard(board, totalPlayers);   

    }
    /* Part 3: Moving a token forwards */
    bool moveIsPossible = validTokenInRow(board, dieSelectedRow-1, 0, 7);
    bool validMoveMade = false;

    if(moveIsPossible == true)
    {
        while(validMoveMade != true)
        {
            printInstruction("Which token in row %d do you wish to move forward (Type the column number)? ", dieSelectedRow);
            validInput(&choice, 1, 8);

            if(validTokenInRow(board, dieSelectedRow-1, choice-1, choice-1) == true)
            {
                if(choice == 8)
                {
                    // NEED TO CHECK THAT IT'S YOUR TOKEN
                    printf("Choice: %d, Current Player: %d, Winning Tokens: %d\n", choice, currentPlayer, winningTokens[currentPlayer]);
                    winningTokens[currentPlayer]++;
                }
                else
                {
                    printf("Choice: %d, Current Player: %d, Winning Tokens: %d\n", choice, currentPlayer, winningTokens[currentPlayer]);
                }
                moveToken(&board[dieSelectedRow-1][choice-1].stackPtr, &board[dieSelectedRow-1][choice].stackPtr);
                outputBoard(board, totalPlayers);
                validMoveMade = true;
            }
            else
            {
                printError("Sorry, there is not token that can be moved in this row/column, please select another.\n");
            }
        } 
    }
    else
    {
        printError("Sorry, there are no tokens in this row that you can move.\n");
    }

    obstacleCheck(board, obstacleLocations);
}

// COMMENT
int promptSaveGame(void)
{
    int choice = 0; // Stores user input

    printInstruction("Would you like to save the current game position and exit the game?\n(1 for yes, 0 for no)\n"); // Prompts user to save game
    validInput(&choice, 0, 1); // Records their response within the range 0 and 1

    return choice; // Returns the user's choice
}