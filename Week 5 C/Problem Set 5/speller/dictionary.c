// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int final_size;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 250000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash of word to check
    unsigned int index = hash(word);
    // Traverse linked list looking for our word case-insensitively
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// CITATION: in understanding how to write a hash function, I made use of an
// explanation by Jacob Sorber. I modified line 62 from his explanation.
unsigned int hash(const char *word)
{
    // Hash function
    int length_of_word = strlen(word);
    // Make all incoming words lowercase, so that consistent hashes will be produced
    char word_lowered[LENGTH + 1];
    for (int i = 0; i < length_of_word; i++)
    {
        word_lowered[i] = tolower(word[i]);
    }

    unsigned int hash_index_value = 0;
    for (int i = 0; i < length_of_word; i++)
    {
        hash_index_value += word_lowered[i];
        hash_index_value = (hash_index_value * word_lowered[i]) % N;
    };
    return hash_index_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return false;
    }
    // int count = 0;
    char word[LENGTH + 1]; // i.e. our LENGTH + 1 for the null terminator
    while (fscanf(file, "%s", word) != EOF)
    {
        unsigned int index = hash(word);
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Error allocating memory for a new node.");
            return false;
        }
        strcpy(new_node->word, word);  // put the word into the new node struct
        new_node->next = table[index]; // put the next node pointer into the struct
        table[index] = new_node;       // insert the node into the table
        final_size++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return final_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            node *tmp = table[i];
            while (cursor != NULL)
            {
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            };
        }
    }
    return true;
}
