#include <stdio.h>


void controlPanel(){
    int numPlayers, loadSaveGame, selection;
    numPlayers = 0;
    loadSaveGame = 0;
    printf("===================================================\n");
    printf("===================================================\n");
    printf("==                 CONTROL PANEL                 ==\n");
    printf("==   Option                       Current        ==\n");
    printf("==                                               ==\n");
    printf("==   (1) Num Players                 %d          ==\n",numPlayers);
    printf("==   (2) Load game                   %d          ==\n", loadSaveGame);
    printf("==                                               ==\n");
    printf("==   (3) Start game                              ==\n");
    printf("==                                               ==\n");
    printf("===================================================\n");
    printf("===================================================\n");

    scanf("%d",&selection);
    while(selection > 3 || selection < 1){
        clear();
        printf("Invalid selection try again: ");
        scanf("%d", &selection);
    }

    switch (selection)
    {
        case 1:
            printf("How many users? (2-6) ");
            scanf("%d", &numPlayers);
            while(numPlayers > 6 || numPlayers < 1){
                clear();
                printf("Invalid input try again: ");
                scanf("%d", &numPlayers);
            }
            controlPanel();
            break;

        case 2:
            printf("Do you wish to load a previous saved game? (1 for yes, anything else for no) ");
            scanf("%d", &loadSaveGame);
            controlPanel();

        case 3:
            printf("GAME STARTING in 5\n");
            printf("GAME STARTING in 4\n");
            printf("GAME STARTING in 3\n");
            printf("GAME STARTING in 2\n");
            printf("GAME STARTING in 1\n");
            printf("GAME STARTING\n");
            game();
        default:
            break;
    }
    
}

void clear(void){
  while (getchar() != '\n');
}