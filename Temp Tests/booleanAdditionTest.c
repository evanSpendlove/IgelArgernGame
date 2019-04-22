#include <stdio.h>
#include <stdbool.h>

int sumArray(const int size, const bool array[size])
{
    int sum = 0;

    for(int i = 0; i < size; i++)
    {
        sum += array[i];
        printf("Sum: %d, Array[i]: %d\n", sum, array[i]);
    }

    return sum;
}

int main(void)
{
    bool array[5] = {true, true, false, true, false};
    int sum = 0;

    sum = sumArray(5, array);

    printf("Sum of array: %d\n", sum);


}