#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
int linearSearch(int array[], int target);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};
    printArray(array);

    int target = get_int("Please input the number you want to search\n");

    int result = linearSearch(array, target);
    if (result > 0)
    {
        printf("Target Found at %dth position\n", result + 1);
    }
    else
    {
        printf("Result Not Found\n");
    }
}

int linearSearch(int array[], int target)
{
    // Linear Search: O(n)
    // Loop throught the array iteratively, to find the target
    // Performance: OK
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        if (array[i] == target)
        {
            return i;
        }
    }
    return -1;
}

void printArray(int array[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
