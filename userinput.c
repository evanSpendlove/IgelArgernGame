#include "userinput.h"

// Need to pass numPlayers, b/c you recursively call the function, so it needs to be passed by reference, not value

void controlPanel(int* numPlayers, int* loadSaveGame)
{
    cell board[MAX_ROWS][MAX_COLUMNS]; // Initialises the game board with the max number of rows and columns
    int obstacleLocations[6]; // Used for checking obstacles at each stage of the game

    int selection;

    printInstruction("===================================================\n");
    printInstruction("===================================================\n");
    printInstruction("==                 CONTROL PANEL                 ==\n");
    printInstruction("==   Option                       Current        ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("==   (1) Num Players                 %d           ==\n",*numPlayers);
    printInstruction("==   (2) Load game                   %d           ==\n", *loadSaveGame);
    printInstruction("==                                               ==\n");
    printInstruction("==   (3) Start game                              ==\n");
    printInstruction("==                                               ==\n");
    printInstruction("===================================================\n");
    printInstruction("===================================================\n");

    validInput(&selection, 1, 3);

    switch (selection)
    {
        case 1:
            printInstruction("How many users? (2-6) ");
            validInput(numPlayers, 2, 6);
            printInstruction("Num players: %d\n", *numPlayers);
            controlPanel(numPlayers, loadSaveGame);
            break;

        case 2:
            printInstruction("Do you wish to load a previous saved game? (1 for yes, 0 for no) ");
            validInput(loadSaveGame, 0, 1);
            controlPanel(numPlayers, loadSaveGame);

        case 3:
            if(*numPlayers > 0)
            {
                printInstruction("GAME STARTING in 5\n");
                printInstruction("GAME STARTING in 4\n");
                printInstruction("GAME STARTING in 3\n");
                printInstruction("GAME STARTING in 2\n");
                printInstruction("GAME STARTING in 1\n");
                printInstruction("GAME STARTING\n");
                game(board, *numPlayers, obstacleLocations);
            }
            else
            {
                printError("Please select option (1) and enter the number of players (>2, <=6).\n");
                controlPanel(numPlayers, loadSaveGame);
            } 
        default:
            break;
    }
    
}

void game(cell board[][MAX_COLUMNS], int totalPlayers, int obstacleLocations[])
{
    /* Set up the game */
    enum gameStatus currentGame = to_start;
    player playerList[totalPlayers];

    boardSetup(board, totalPlayers, playerList, obstacleLocations);
    outputBoard(board, totalPlayers);

    currentGame = in_progress;

    #ifdef BUG
        /* Playing the game from here on */
        while(currentGame == in_progress)
        {
            gameTurn(board, totalPlayers, obstacleLocations, currentGame); // DEFINE THIS 
        }
    #endif

    printInstruction("Game Started!\n");
}