#include <stdio.h>
#include <string.h>

int main(void)
{
    int array[5];

    memset(array, 0, sizeof(int)*5); // Need to multiply by size

    for(int i = 0; i < 5; i++)
    {
        printf("%d\n", array[i]);
    }

    return 0;

}