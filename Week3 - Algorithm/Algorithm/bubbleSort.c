#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
void bubbleSort(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};

    // For Sorting Algorithm
    printf("Array Before Sorting: \n");
    printArray(array);

    bubbleSort(array);

    printf("Array After Sorting: \n");
    printArray(array);
}

void bubbleSort(int array[])
{
    // O(n^2)
    // Bubble the number to the end of the array
    int temp;
    int swap_counter = -1;

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        // Reset the swap_counter to 0 for each outer loop iteration
        swap_counter = 0;

        for (int j = 0; j < ARRAYSIZE - i; j++) // j < ARRAYSIZE - i because the sorted item has
                                                // been moved to the end of the array after each pass
        {
            // Sorting Condition
            // Sorting ascending, so checking if array[i] > array[j(i.e. i+1)]
            if (array[j] > array[j + 1])
            {
                // Move the array one position to the right, until the correct position
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swap_counter++; // Increment the swap_counter if there is sorting
            }
        }

        // break the outer loop if there is no sorting
        if (swap_counter == 0)
        {
            break;
        }
    }

    return;
}

void printArray(int array[])
{
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
