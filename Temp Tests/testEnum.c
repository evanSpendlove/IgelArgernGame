
#include <stdio.h>

int main(void)
{
    enum col { red, blue, green };

    enum col col2 = red;

    printf("%d", col2);

    if(col2 == 0)
    {
        printf("Indices work!\n");
    }

    enum col col3 = blue;

    printf("Col3: %d\n", col3);

    col3 = col2;

    printf("Col3: %d\n", col3);

    return 0;
}