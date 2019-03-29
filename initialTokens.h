#include "gameStructures.h"

/*
    isValidPlacement() function:
        -->
*/
int isValidPlacement(cell board[][MAX_COLUMNS], const int placedTokenCount, enum colour playerColour);

/*
    userPlaceToken() function:
        -->
*/
void userPlaceToken(cell board[][MAX_COLUMNS], player playerList[], int player, int row, int column);

/*
    initialTokenPlacement() function:
        -->
*/
void initialTokenPlacement(cell board[][MAX_COLUMNS], const int totalPlayers, player playerList[]);
