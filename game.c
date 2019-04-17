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

#include "stackMethods.h"
#include "stackMethods.c"

#include "gameMechanics.h"
#include "gameMechanics.c"

int main(void)
{   
    srand(time(NULL)); // Seeds the rand() function with the current time to properly randomise thigns

    /* Requesting the user to set the total number of players */
    int totalPlayers = 0; // Int for totalPlayers
    int loadSaveGame = 0;

    controlPanel(&totalPlayers, &loadSaveGame);

    return 0;
}
