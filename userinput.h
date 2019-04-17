/*
    userInput.h header file
*/

#include "gameStructures.h"
#include "gameIO.h"

void controlPanel(int* numPlayers, int* loadSaveGame);
void game(cell board[][MAX_COLUMNS], int totalPlayers, int obstacleLocations[]);