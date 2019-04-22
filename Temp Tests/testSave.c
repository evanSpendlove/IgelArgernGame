#include <stdio.h>


/* load */
void load(int* totalPlayers)
{
    FILE *loadFile;

    if((loadFile = fopen("testSave.txt", "r")) == NULL)
    {
        printf("Error\n");
    }
    else
    {
        fscanf(loadFile, "%*[^\n]"); // Skip a line in the file
        fscanf(loadFile, "%d\n", totalPlayers);
    }

    fclose(loadFile);
}


/* save */
void save(int totalPlayers)
{
    FILE *filePtr;

    if((filePtr = fopen("testSave.txt", "w")) == NULL)
    {
        printf("Error\n");
    }
    else
    {
        fprintf(filePtr, "TOTAL PLAYERS\n%d\n", totalPlayers);
    }

    fclose(filePtr);
    
}


int main(void)
{
    int totalPlayers;

    totalPlayers = 5;

    int newTotal = 0;

    save(totalPlayers);

    printf("Total players: %d\n", totalPlayers);

    load(&newTotal);

    printf("Total players: %d\n", newTotal);

}