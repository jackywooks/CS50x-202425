#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototype
string encryptText(string plaintext, string key);
bool keyValidation(string key);

int main(int argc, string argv[])
{
    // Single Command Line to accept the key
    // Program Must have exactly one argument
    //  argc != 2 as the execution of the file count as the 1st argument
    if (argc != 2)
    {
        printf("Missing or more than one command-line argument\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contains 26 character.\n");
        return 1;
    }
    else if (!keyValidation(argv[1]))
    {
        // key invlaid not 26 char or have !isalpha or not have each letter exactly once
        // Key case-insensitive
        printf("Key Validation Failed, All characters in the key must be alphabet and unique. \n");
        return 1;
    }
    // store the argv[1] to key
    string key = argv[1];

    // ask user to input plaintext
    string plaintext = get_string("plaintext: ");

    // return ciphertext
    printf("ciphertext: %s\n", encryptText(plaintext, key));

    return 0;
}

/**
 * Encryption Function
 * @param plaintext the user input plain text for encryption
 * @param key the user pre-defined key
 * @return encrypted text
 */
string encryptText(string plaintext, string key)
{
    // preserve case, capitalized letters must remain capitalized letters; lowercase letters must
    // remain lowercase letters. allocate memory to string, by the size of plaintext + 1
    string encryptedText = malloc(strlen(plaintext) + 1);
    int index = 0;

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            index = plaintext[i] - 'A';
            encryptedText[i] = toupper(key[index]);
        }
        else if (islower(plaintext[i]))
        {
            index = plaintext[i] - 'a';
            encryptedText[i] = tolower(key[index]);
        }
        else // handling case that the text is not alphabet
        {
            encryptedText[i] = plaintext[i];
        }
    }

    // Add Null end character to encryptedText
    encryptedText[strlen(plaintext)] = '\0';

    return encryptedText;
}

/**
 * Helper Function to check if the string is all alphabets, and the alphabet does not repeat
 * @param key the key user input for encryption
 * @return return if the key is valid, vice versa
 */
bool keyValidation(string key)
{
    // Create a temporary character array to store the each alphabet of the key to prevent
    // duplication
    char tempKey[26] = "";
    int counter = 0;

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // check if the key is all alphabet
        if (isalpha(key[i]))
        {
            for (int j = 0, len2 = strlen(tempKey); j < len2; j++)
            {
                // check if the key[i] is in the tempKey array
                // if yes, return false
                if (key[i] == tempKey[j] && key[i] != '\0')
                {
                    return false;
                }
            }
            // if not, store it in the array
            tempKey[counter] = key[i];
            tempKey[counter + 1] = '\0';
            counter++;
        }
        else
        {
            return false;
        }
    }
    return true;
}
