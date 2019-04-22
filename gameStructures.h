/*
    This header file includes all of the structure definitions and constants required by the game.
    Written by: Evan Spendlove (18492656) and Reuben Mulligan (18733589)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#ifndef gameStructures_h
    #define gameStructures_h

        /* PRINT COLOURS */
        #define PRINT_RED     "\x1b[31m" // Escape code to print text in red
        #define PRINT_BLUE    "\x1b[34m" // Escape code to print text in blue
        #define PRINT_GREEN   "\x1b[32m" // Escape code to print text in green
        #define PRINT_MAGENTA "\x1b[35m" // Escape code to print text in magenta
        #define PRINT_CYAN    "\x1b[36m" // Escape code to print text in cyan
        #define PRINT_YELLOW  "\x1b[33m" // Escape code to print text in yellow
        #define PRINT_RESET   "\x1b[0m" // Resets print colour to white

        #define MAX_COLUMNS 9
        #define MAX_ROWS 6
        #define MAX_TOKENS_PER_STACK 24
        #define MAX_USERS 6

        /* Enumerations – used for keeping track of the status of different things */
        /*
            Obstacle Status:
            -> Active – The obstacle is enabled and there are tokens to the left of it
            -> Inactive – Not an obstacle or all tokens are to the right of it
        */
        enum obstacleStatus { inactive, active };

        /*
            Game Status:
            -> to_start – Game not started yet
            -> in_progress – Game in progress
            -> complete – Game has been completed, i.e. a player has won
        */
        enum gameStatus { to_start, in_progress, complete, saved };

        /*
            Colour:
            -> The various possible colours of the tokens and users
        */
        enum colour { Red, Blue, Green, Magenta, Cyan, Yellow };

        /* Typedef and structure creation */

        typedef struct listNode {
             int data; // Stores the token colour (from the enum colour)
             struct listNode *prevPtr; // Links this node to the previous one (i.e. further down in the stack)
        }ListNode;  
        
        typedef ListNode *ListNodePtr; // Typedefing a pointer for ease of use

        typedef struct token // Token structure
        {
            enum colour tokenColour; // Stores the colour of the token
        }token;

        typedef struct cell
        {
            ListNodePtr stackPtr; // Each cell can store up to 24 (6 players, 4 tokens each) tokens in its stack
            enum obstacleStatus obstacle; // Obstacle status for each cell
        }cell;

        typedef struct player
        {
            char username[100]; // Stores the username of the player
            enum colour userColour; // Stores the colour of the token
            ListNodePtr userStack; // Stores the user's stack of tokens
        }player;
 
#endif