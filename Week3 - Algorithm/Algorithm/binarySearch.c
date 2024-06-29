#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
int binarySearch(int array[], int target, int start, int end);

int main(void)
{
    int array[ARRAYSIZE] = {1, 2, 3, 5, 6, 8, 9, 12, 16};
    printArray(array);

    // For Searching Algorithm
    int target = get_int("Please input the number you want to search\n");

    // Binary Search Only worked on sorted array
    int result = binarySearch(array, target, 0, ARRAYSIZE);

    if (result > 0)
    {
        printf("Target Found at the %dth position\n", result + 1); // plus one for 1-based index
    }
    else
    {
        printf("Result Not Found\n");
    }
}

int binarySearch(int array[], int target, int start, int end)
{
    // Linear Search: O(nLogn)
    // Performance: Slower than linear search at smaller amount of elements, excellent for larger
    // dataset Require the array to be sorted at the first place Divide and Conquer
    if (end >= start)
    {
        // Break down the array
        int middle = start + (end - start) / 2;

        // base case, return the middle index when found the target in the middle
        if (array[middle] == target)
            return middle;

        // if the middle value is larger than target, search the left array
        if (array[middle] > target)
        {
            return binarySearch(array, target, start, middle - 1);
        }

        // search the right array instead
        return binarySearch(array, target, middle + 1, end);
    }

    // If not found
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
