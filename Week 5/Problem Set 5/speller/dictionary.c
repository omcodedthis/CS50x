// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 73716082;

// Hash table
node *table[N];

// stores dictionary size
unsigned int dictionary_size[1];



// check() determines the hash of the word and then checks whether this word is in the linked list
// with that specific hash value. If it is present, true is returned, else false is returned.
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}



// hash() hashes a word to a number. This is done by applying a formula where the int value of each char
// in the word is raised to the power of its index in the word. The value for each char/letter in the
// word is added to hash_value using a for-loop. If the end of the word is reached, where current_char is
// '\0' (NULL), the hash_value is returned as there are no more chars to hash. The hash fn ensures that
// the order of the chars are specific, where different series of chars will yield different hash values.
// The max number of chars used is 5 as beyond this, the tradeoff of time to space is too high (space is
// in the order of GBs which is too big for a spell checker).
unsigned int hash(const char *word)
{
    int length = strlen(word);
    int hash_value = 0;
    for (int i = 0; i < 6; i++)
    {
        int current_char = tolower(word[i]) - 97;

        if (current_char < 0)
        {
            return hash_value;
        }

        hash_value += pow(current_char, i);
    }
    return hash_value;
}



// load() loads dictionary into memory, returning true if successful, else false if unsuccessful.
bool load(const char *dictionary)
{
    // opens the dictionary.txt file for reading, if the file can't be opened (fopen returns
    // NULL) false is returned.
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        return false;
    }

    // total_words_added & dict_word are variables that store the total words added & an array
    // to store the word from the dictionary respectively.
    int total_words_added = 0;
    char dict_word[LENGTH + 1];

    // This while-loop scans for each word in the dictionary.txt file, the loop ends when
    // fscanf returns EOF, meaning no words left to read.
    while (fscanf(infile, "%s", dict_word) != EOF)
    {
        // creates a pointer, named cursor and allocates memory the size of an node to itself.
        // If memory cannot be allocated (NULL), false is returned.
        node *cursor = malloc(sizeof(node));
        if (cursor == NULL)
        {
            return false;
        }

        // copies the word from the dictionary into the word array of the node.
        strcpy(cursor->word, dict_word);

        // determines a hash value for the word.
        unsigned int hash_value = hash(dict_word);

        // adds the node to a linked list of with that specific hash value in the hash table.
        cursor->next = table[hash_value];
        table[hash_value] = cursor;

        total_words_added++;
    }

    // stores the total words added to a global array dictionary_size for it to be called by size() &
    // closes the file opened.
    dictionary_size[0] = total_words_added;
    fclose(infile);
    return true;
}



// size returns number of words in dictionary if loaded, else 0 if not yet loaded by calling an array
// of size 1 (dictionary_size) and returning the element stored in index 0.
unsigned int size(void)
{

    return dictionary_size[0];
}



// unload() unloads dictionary from memory by freeing up each node in the linked list, in each index,
// of the hash table, table[N]. true is returned if unload was successful & false is the unload was
// unsuccessful.
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }

        if (i == (N - 1))
        {
            return true;
        }

    }
    return false;
}