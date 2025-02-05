/*
    COMP10050 - Assignment 2
        Main C File - Igel Agern Game Implementation
        Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
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

#include "gameSave.h"
#include "gameSave.c"

int main(void)
{   
    srand(time(NULL)); // Seeds the rand() function with the current time to properly randomise thigns

    int totalPlayers = 0; // Int for totalPlayers
    int loadSaveGame = false; // Used for checking if the user has requested to load a saved game file

    controlPanel(&totalPlayers, &loadSaveGame); // Calls controlPanel() to start the main program

    return 0;
}
