// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


const unsigned int N = 26;

// Hash table
node *table[N];

int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (!file)
    {
        return false;
    }

    char words[LENGTH + 1];

    else
    {

        while (fscanf(file, "%s", words) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                fclose(file);
                return false;
            }

            strcpy(n->word, words);

            n->next = NULL;

            unsigned int index = hash(words);

            n->next = table[index];

            table[index] = n;

            wordcount++;

        }
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    return false;
}
