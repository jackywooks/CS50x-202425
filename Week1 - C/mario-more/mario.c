#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    // Prompt user for positive integer between 1 and 8
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);

    // print the n-level pyramid
    for (int i = 0; i < n; i++)
    {
        // printing space before the gap
        for (int j = n; j > i + 1; j--)
        {
            /*
                print the amount of space that relate to the current row,
                i.e. 0th row print n space,
                1th row print n-1 space
            */
            printf(" ");
        }
        // print the hill before the gap
        for (int k = 0; k < i + 1; k++)
        {
            /*
                print the hill that relate to the current row,
                i.e. 0th row prints 1 hill, 1th row prints 2 hill ... ...
            */
            printf("#");
        }

        // print the gap
        printf("  ");

        // print the hill after the gap
        for (int k = 0; k < i + 1; k++)
        {
            /*
                print the hill that relate to the current row,
                i.e. 0th row prints 1 hill, 1th row prints 2 hill ... ...
            */
            printf("#");
        }
        printf("\n");
    }
}
