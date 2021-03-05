// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// word counts
unsigned int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (int i = N - 1; i >= 0; i--) {
        node *head = table[i];

        while (head) {
            if (strcasecmp(head->word, word) == 0)
                return true;

            head = head->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    const char *a = word;

    while (*a) {
        sum += *a;
        a++;
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *infile;
    if ((infile = fopen(dictionary, "r")) == NULL)
        return false;

    char *word = malloc((LENGTH + 1) * sizeof(char));
    if (word == NULL)
        return false;

    while (fscanf(infile, "%s", word) != EOF) {
        unsigned int key = hash(word);
        node **head = &table[key];
        node *new_node = malloc(sizeof(node));

        strcpy(new_node->word, word);
        new_node->next = NULL;

        if (*head)
            new_node->next = *head;

        *head = new_node;

        words++;
    }

    free(word);
    fclose(infile);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = N - 1; i >= 0; i--) {
        node *head = table[i], *temp = head;

        while (head) {
            head = head->next;
            free(temp);
            temp = head;
        }
    }
    return true;
}
