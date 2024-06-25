// A program calculate the readability lv. of the text input
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Initiate Global Output character array
char output[16];

// Prototype
string checkReadability(string textInput, char *result);
int countLetter(string textInput);
int countWord(string textInput);
int countSentence(string textInput);

int main(void)
{
    // Accept User input to get the text
    string textInput = get_string("Text: ");
    printf("%s\n", checkReadability(textInput, output));
}

string checkReadability(string textInput, char *result)
{
    int letterCount = countLetter(textInput);
    int wordCount = countWord(textInput);
    int sentenceCount = countSentence(textInput);
    // Get the average no. of letter per 100 words in the text
    // average letter per 100 = total number of letter / total number of word * 100;
    float L = ((float) letterCount / (float) wordCount) * 100.0;
    // Get the average number of sentences per 100 words in the text
    // average sentences per 100 = total number of sentance / total number of word * 100;
    float S = ((float) sentenceCount / (float) wordCount) * 100.0;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        sprintf(result, "Before Grade 1");
    }
    else if (index <= 16)
    {
        sprintf(result, "Grade %d", index);
    }
    else
    {
        sprintf(result, "Grade 16+");
    }
    return result;
}

// Helper Function to count the no. of letter in the text
int countLetter(string textInput)
{
    int letterCount = 0;
    for (int i = 0, length = strlen(textInput); i < length; i++)
    {
        // check if character in the text is alphabet
        if (isalpha(textInput[i]))
        {
            letterCount++;
        }
    }
    return letterCount;
}

// Helper Function to count the no. of word in the text
int countWord(string textInput)
{
    int wordCount = 0;
    for (int i = 0, length = strlen(textInput); i < length; i++)
    {
        // check the word by space
        if ((isalpha(textInput[i]) && isspace(textInput[i + 1])) ||
            (isalpha(textInput[i]) && ispunct(textInput[i + 1]) && textInput[i + 1] != '\'' &&
             textInput[i + 1] != '-'))
        {
            wordCount++;
        }
    }
    return wordCount;
}

// Helper Function to count the no. of sentence in the text
int countSentence(string textInput)
{
    int sentenceCount = 0;
    for (int i = 0, length = strlen(textInput); i < length; i++)
    {
        // check the end punctuation
        if (textInput[i] == '.' || textInput[i] == '?' || textInput[i] == '!')
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}
