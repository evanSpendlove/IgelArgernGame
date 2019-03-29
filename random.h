/*
    Header file to include all functions associated with random number generation.
    Written by: Evan Spendlove (18492656)
*/

#include "gameStructures.h"

/*
    swap() function:
        --> Swaps the data in two integer variables, a and b.
*/
void swap(int *a, int *b);

/*
    fisherShuffle() function:
        --> Shuffles the input array to ensure an unbiased random order
        --> Modifies the input array directly using pointers
        --> Uses fisherShuffle algorithm (source: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
*/
void fisherShuffle(int numbers[], int n);

/*
    diceRoll() function:
        --> Returns a random integer between 1 and 6 using the fisherShuffle() algorithm
*/
int diceRoll(void);