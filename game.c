/*
    Main file for the Game.
    Project written by: Reuben Mulligan, Evan Spendlove
*/

/* #INCLUDES GO HERE */

#include "gameStructures.h"

#include "gameSetup.h"
#include "gameSetup.c"

#include "gameIO.h"
#include "gameIO.c"

#include "random.h"
#include "random.c"

#include "stackMethods.h"
#include "stackMethods.c"

#include "initialTokens.h"
#include "initialTokens.c"

#include "userinput.h"
#include "userinput.c"

int main(void)
{   
    srand(time(NULL)); // Seeds the rand() function with the current time to properly randomise thigns

    /* Requesting the user to set the total number of players */
    int totalPlayers = 0; // Int for totalPlayers
    int loadSaveGame = 0;

    #ifdef BUG
        printInstruction("How many players are there?\n"); // Prompts user to enter the number of people playing
        validInput(&totalPlayers, 2, 6); // Validates the input within the range 2 - 6
    #endif

    controlPanel(&totalPlayers, &loadSaveGame);
    

    return 0;
}
