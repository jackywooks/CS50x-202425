// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>



#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table, by a prime no.
const unsigned int N = 1777;

// create a global variable to store the no. of word in the dict
int dict_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert the input word to lower case, in order to provide the correct hash result
    int word_length = strlen(word);
    char* lower_word = malloc(word_length + 1);
    for (int i = 0; i < word_length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[word_length] = '\0';

    // hash the word to find the index in the hash table
    int index = hash(lower_word);

    // create a new pointer points to the table of the index
    node *ptr = table[index];

    while (ptr != NULL)
    {
        if (strcmp(ptr->word, lower_word) == 0)
        {
            free(lower_word);
            return true;
        }
        ptr = ptr->next;
    }

    free(lower_word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    int word_length = strlen(word);
    int ascii_sum = 0;

    for ( int i = 0; i < word_length; i++)
    {
        ascii_sum += word[i] * i;
    }

    return ascii_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        printf("Unable to open dictionary file");
        return false;
    }

    // read each word in the dictionary, separated by /n
    // add them into the hashtable
    char buffer[LENGTH + 1];
    int result;


    while ((result = fscanf(dict, "%s", buffer)) != EOF)
    {
        if (result != 1)
        {
            return false;
        }

        // Create a new node to store the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Failed to create Node");
            return false;
        }
        // Copy the word into the node
        strcpy(new_node->word, buffer);

        // Hasing function
        int index = hash(new_node->word);

        // insert new node at the beginning of the table
        new_node->next = table[index];
        table[index] = new_node;
        dict_words++;
    }

    // close the dictionary
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *counter = table[i];
        while (tmp != NULL)
        {
            counter = tmp;
            tmp = tmp->next;
            free(counter);
        }
    }
    return true;
}
