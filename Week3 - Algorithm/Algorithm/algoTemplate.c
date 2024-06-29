#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};

    //For Searching Algorithm
    //int target = get_int("Please input the number you want to search\n");
    //For Sorting Algorithm
    //printf("Array Before Sorting: \n");
    printArray(array);
}

void printArray(int array[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
