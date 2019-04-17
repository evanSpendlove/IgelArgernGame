#include <stdio.h>
#include <stdlib.h>
#include "gameStructures.h"

int save(cell board[6][9], player playerList[], enum gameStatus, int turnCount){

    FILE *fp;

    if((fp = fopen("save.txt", "w")) == NULL){
        printf("File open failed, exiting save");
        return 2;
    }else{
        
    }

}