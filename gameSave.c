/*
    Game Saving and Loading C file:
        --> Contains the functions for saving the current game state to a text file and loading the game from a text file
    Written by: Evan Spendlove (18492656) && Reuben Mulligan (18733589)
*/
#include "gameSave.h"
#include "gameIO.h"

/* SAVE GAME FUNCTIONS */
int save(int totalPlayers, cell board[MAX_ROWS][MAX_COLUMNS], player playerList[totalPlayers], int winningTokens[totalPlayers])
{
    FILE *saveFile; // Create a new file pointer

    if((saveFile = fopen("save.txt", "w")) == NULL) // If the file did not open correctly
    {
        printError("File open failed, exiting save\n"); // Prints an error
        return 2; // Returns an error code
    }
    else // File opening was successful
    {
        /* Print the player information to the file */
        fprintf(saveFile, "--TOTAL PLAYERS--\n%d\n", totalPlayers); // Print the total players
        fprintf(saveFile, "--PLAYER INFORMATION--\n"); // Print player info header

        for(int player = 0; player < totalPlayers; player++) // For each player in the playerList[]
        {
            fprintf(saveFile, "%s %d ", playerList[player].username, playerList[player].userColour); // Print the player's username and colour
            fprintf(saveFile, "%d\n", winningTokens[player]); // Print the player's number of winning tokens
        }

        /* Print the board information to the file */
        for(int row = 0; row < MAX_ROWS; row++) // For each row on the board
        {
            for(int col = 0; col < MAX_COLUMNS; col++) // For each column in each row
            {
                fprintf(saveFile, "--ROW: %D, COLUMN: %D--\n", row, col);
                fprintf(saveFile, "%d\n", board[row][col].obstacle); // Print the obstacle status of the board
                saveStack(saveFile, board[row][col].stackPtr); // Print the stack of the cell
            }
        }

        fclose(saveFile); // Close the file

        return 1; // Return a successful save
    }
    return 0; // Return a non-opening error
}

void saveStack(FILE* file, ListNodePtr node)
{
    if(node == NULL) // If the node is an empty stack
    {
        fprintf(file, "%s\n", "NULL"); // Print NULL
    }
    else // Else, the stack is not empty
    {
        while(node != NULL) // While we aren't at the NULL node
        {
            fprintf(file, "%d ", node->data); // Print the data (i.e. token colour)
            node = node->prevPtr; // Move to the previous node (lower in the stack)
        }
        fprintf(file, "%s\n", "NULL"); // Print the NULL node, signally end of stack
    }
}

/* LOAD GAME FUNCTIONS */
int readPlayerCount(void)
{
    FILE* loadFile; // Initialises a new file pointer

    int totalPlayers; // Integer for storing totalPlayers of the saved game

    if((loadFile = fopen("save.txt", "r")) == NULL) // If the file opening is unsuccessful
    {
        printf("File open failed, exiting load\n"); // Print an error code
        return 2; // Return an error
    }
    else // The file opening was successful
    {
        fscanf(loadFile, "%*[^\n]"); // Skip the 'TOTAL PLAYERS' title line
        fscanf(loadFile, "%d\n", &totalPlayers); // Read in the totalPlayers

        printf("Total players: %d\n", totalPlayers); // Print the total players of the loaded game

        fclose(loadFile); // Close the file
        return totalPlayers; // Return the totalPlayers
    }
    return 0; // Default unsuccessful function-run error
}

int load(int *totalPlayers, cell board[][MAX_COLUMNS], player playerList[], int winningTokens[])
{
    FILE *loadFile; // New file pointer

    char buffer[100]; // Buffer for reading (think: skipping) header lines

    if((loadFile = fopen("save.txt", "r")) == NULL) // If the file did not open correctly
    {
        printf("File open failed, exiting load\n"); // Print an error
        return 2; // Return an error code
    }
    else // Otherwise, the file opened correctly.
    {

        fgets(buffer, 99, loadFile); // Skip the 'TOTAL PLAYERS' title line
        fscanf(loadFile, "%d\n", totalPlayers); // Scan the totalPlayers from the file
        fgets(buffer, 99, loadFile); // Skip the 'PLAYER INFORMATION' title line

        resetBoard(board); // Rese the board

        for(int player = 0; player < *totalPlayers; player++) // For each player
        {
            fscanf(loadFile, "%s %d %d\n", playerList[player].username, &playerList[player].userColour, &winningTokens[player]); // Read in player info
        }

        for(int row = 0; row < MAX_ROWS; row++) // For each row in the board
        {
            for(int col = 0; col < MAX_COLUMNS; col++) // For each column
            {
                if(!feof(loadFile)) // If not at the end of the file
                {
                    fgets(buffer, 99, loadFile); // Skip the 'Row:, Col:' title line
                    fscanf(loadFile, "%d\n", &board[row][col].obstacle); // Scan in the obstacle status

                    loadStack(loadFile, &board[row][col].stackPtr); // Load the stack line
                }
            }
        }

        fclose(loadFile); // Close the file pointer
        return 1; // Return a successful read
    }
    return 0; // Return non-opening error
}

void loadStack(FILE* file, ListNodePtr* node)
{
    char buffer[100]; // Buffer for reading in string to parse
    int data = 0; // Used for storing data of each node

    int read = 0; // Read counter for looping through the string

    fgets(buffer, 99, file); // Read up to 99 (+ null char) char into buffer

    if(strcmp(buffer, "NULL\n") != 0) // If the stack is not NULL
    {
        while(read != -1) // While the read counter has not been flagged
        {
            if(buffer[read] == '0' || buffer[read] == '1' || buffer[read] == '2' || buffer[read] == '3' || buffer[read] == '4' || buffer[read] == '5') // If a valid token colour
            {
                data = buffer[read] - 48; // Converting from ASCII to integer (subtract 48 - ASCII code for '0')
                insert(node, data); // Insert a new node with the data
            }
            else if(buffer[read] == 'N') // Read has reached the null terminator of the stack
            {
                read = -1; // Set read to -1
                break; // Break the loop
            }
            read++; // Increment read
        }
    }
}
