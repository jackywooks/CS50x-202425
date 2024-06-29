#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
void selectionSort(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};

    // For Sorting Algorithm
    printf("Array Before Sorting: \n");
    printArray(array);

    selectionSort(array);

    printf("Array After Sorting: \n");
    printArray(array);
}

void selectionSort(int array[])
{
    // O(n^2)
    // Move the smallest number to the leftmost of the array, and do it one by one

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        // Create Variable to store the temp smallest value, and index
        int smallest_Value = array[i];
        int smallest_Index = i;

        for (int j = i + 1; j < ARRAYSIZE; j++)
        {
            // Sorting Condition
            if (smallest_Value > array[j]) // Effectively compare if the value is the smallest from
                                           // left side of the array to right side
            {
                smallest_Value = array[j];
                smallest_Index = j;
            }
        }

        // No swap if smallest value is already at i
        if (smallest_Index != i)
        {
            array[smallest_Index] = array[i];
            array[i] = smallest_Value;
        }
    }
}

void printArray(int array[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
