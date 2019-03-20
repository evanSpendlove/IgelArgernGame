/*
    C file to include the implementation of all functions associated with random number generation.
    Written by: Evan Spendlove (18492656)
*/

#include "random.h"

void swap(int *a, int *b)
{
    int temp = *a; // Assigns the value in a to the temp variable
    *a = *b; // Assigns the value in b to a
    *b = temp; // Assigns the value in temp (i.e. original value of a) to b
}

void fisherShuffle(int numbers[], int n)
{
    int i, j; /* Initialises i (counter), j (for indexes) */

    for(i = n-1;i >= 0;i--) /* Loops over the array while i >= 0 and starting from the last index */
    {
        j = rand() % (i+1); /* assigns a random index to j using (i+1) for modulo */

        swap(&numbers[i], &numbers[j]); // Swaps the numbers at index i and j
    }
}

int diceRoll(void)
{
    int sidesOfDie[6] = {1,2,3,4,5,6}; // Initialises an array containing all 6 possible outcomes of a diceroll

    fisherShuffle(sidesOfDie, 6); // Randomly shuffles the array

    return sidesOfDie[0]; // Returns the first item of the shuffled array
}