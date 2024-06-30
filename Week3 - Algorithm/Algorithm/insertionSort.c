#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
void insertionSort(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};

    //For Sorting Algorithm
    printf("Array Before Sorting: \n");
    printArray(array);

    insertionSort(array);

    printf("Array After Sorting: \n");
    printArray(array);
}

void insertionSort(int array[])
{
    // O(n^2)
    // Move item from right (unsorted) to left (sorted)
    int temp;

    for ( int i = 1; i < ARRAYSIZE; i++ )
    {
        for ( int j = i; j > 0; j--)
        {
            // Sorting Condition
            if (array[j] < array[j - 1])
            {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
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
