// Average three number using an array, a constant and a helper function
#include <cs50.h>
#include <stdio.h>

// Global Variable, Constant
const int N = 3;

// Prototype
float average(int length, int array[]);

int main(void)
{
    // using single variable for score
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;

    printf("Average: %f\n", (score1 + score2 + score3) / 3.0);

    // using array to store score
    int scores[N];
    // Using Loop to get scores
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score ");
    }

    printf("Average: %f\n", average(N, scores));
}

float average(int length, int array[])
{
    // Calculate average
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }

    return sum / (float) length;
}
