#include <cs50.h>
#include <stdio.h>

// ARRAYSIZE of the array
#define ARRAYSIZE 9

// Prototype
void printArray(int array[]);
void mergeSort(int array[], int arraylength);
void merge(int leftArray[], int rightArray[], int array[], int leftSize, int rightSize);

int main(void)
{
    int array[ARRAYSIZE] = {9, 5, 7, 3, 2, 1, 4, 6, 8};

    // For Sorting Algorithm
    printf("Array Before Sorting: \n");
    printArray(array);

    mergeSort(array, ARRAYSIZE);

    printf("Array After Sorting: \n");
    printArray(array);
}

void mergeSort(int array[], int arraylength)
{
    // O(nLogn)
    // Divide and Conquer

    if (arraylength <= 1)
        return; // base case

    // divide the array into two subarrays
    int middle = arraylength / 2;
    int leftArray[middle];
    int rightArray[arraylength - middle];

    int i = 0; // Index for left array
    int j = 0; // index for right array

    // add the content of the array to left array and right array
    for (; i < arraylength; i++)
    {
        if (i < middle)
        {
            leftArray[i] = array[i];
        }
        else
        {
            rightArray[j] = array[i];
            j++;
        }
    }

    // recursive call of the merge sort of left array
    mergeSort(leftArray, middle);
    // recursive call of the merge sort of right array
    mergeSort(rightArray, arraylength - middle);
    // merge the array together
    merge(leftArray, rightArray, array, middle, arraylength - middle);
}

void merge(int leftArray[], int rightArray[], int array[], int leftSize, int rightSize)
{
    // Indices of the arrays
    int i = 0, l = 0, r = 0;

    // looping through the left array and right array at the same time
    while (l < leftSize && r < rightSize)
    {
        // Sorting Condition
        if (leftArray[l] < rightArray[r])
        {
            // update the original array to the left's one
            array[i] = leftArray[l];
            i++;
            l++;
        }
        else
        {
            // update the original array to the right's one
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    // handling the remaining item in the left array or right array
    while (l < leftSize)
    {
        array[i] = leftArray[l];
        i++;
        l++;
    }
    while (r < rightSize)
    {
        array[i] = rightArray[r];
        i++;
        r++;
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
