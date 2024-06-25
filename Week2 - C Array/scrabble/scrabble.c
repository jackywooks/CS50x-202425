// A program to accept a string from two player, calculate the scrabble points of the string, and
// print the winner.
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype
string winner(string p1, string p2);
int calculateScore(string input);

int main(void)
{
    // Prompt Two User to input two string
    string p1Input = get_string("Player1: ");
    string p2Input = get_string("Player2: ");

    printf("%s\n", winner(p1Input, p2Input));

    // Calculate the score of two string
    // determine the winner
}

string winner(string p1, string p2)
{
    int p1Score = calculateScore(p1);
    int p2Score = calculateScore(p2);

    if (p1Score == p2Score)
    {
        return "Tie!";
    }
    else if (p1Score > p2Score)
    {
        return "Player 1 wins";
    }
    else
    {
        return "Player 2 wins";
    }
}

int calculateScore(string input)
{
    // Use an array to store the point of each character
    int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    // calculate the score by looping inside the string, add the sum of the score
    int score = 0;
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        // Check if the character input is alphabet
        if (isupper(input[i]) || islower(input[i]))
        {
            char c = toupper(input[i]);
            // Using the ASCII table to get the index
            int index = c - 'A';
            score += points[index];
        }
    }
    return score;
}
