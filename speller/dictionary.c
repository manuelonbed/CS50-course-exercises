// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int dictSize = 0; // size of dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

node *create_node(char *word);

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);
    node *nodeHead = table[hash_index];
    while (nodeHead != NULL)
    {
        if (strcasecmp(nodeHead -> word, word) == 0)
        {
            return true;
        }
        nodeHead = nodeHead -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    dictSize = 0;
    // Open dictionary file
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        return false;
    }

    // Initiate table elements to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Read strings from file one at a time
    char word[LENGTH + 1];
    node *prevHead = NULL;
    node *newNode = NULL;
    while (fscanf(dictFile, "%s", word) != EOF)
    {
        dictSize++;
        newNode = create_node(word);  // New node
        prevHead = table[hash(word)]; // Store head of table element
                                      // Hash word to obtain a hash value
        // Insert node into hash table at that location
        if (prevHead == NULL) // When head is empty
        {
            table[hash(word)] = newNode;
        }
        else
        {
            table[hash(word)] = newNode; // New head equals to new node
            newNode->next = prevHead; // Next node of new node (or new head) points to previous head
        }
    }

    fclose(dictFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        node *currentNode = table[i];

        while (currentNode != NULL)
        {
            node *tempNode = currentNode -> next;
            free (currentNode);
            currentNode = tempNode;
        }
    }
    return true;
}

node *create_node(char *word)
{
    // Allocate space for new node
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return NULL; // Return NULL when malloc fails
    }

    strcpy(n->word, word); // copy word into the node
    n->next = NULL;        // node next pointer to null

    return n; // return node
}
