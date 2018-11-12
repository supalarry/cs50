// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <strings.h>
// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// i think the problem is that the linked list doesnt work properly, because it does not work properly
// when there are two words with the same letter in the dictionary. check if it is inserted properly!!!

// not only that, but the amount of words in the text is one less than in dictionary

// Represents a hash table
node *hashtable[N];

// String copy function to insert a word into node's word field.
void    ft_strcpy(char *str1, char *str2)
{
    int i;

    i = 0;
    while(str2[i] != '\0')
    {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0';
}
// Create first block of link list, thus initializing link list at a specific index
node    *ft_create(char *word)
{
    node *n;
    n = malloc(sizeof(node));
    ft_strcpy(n->word, word);
    n->next = NULL;
    return (n);
}

// Insert node at the start of link list. Return address of new node and set head pointer of array equal to it.
node    *ft_insert(node *head, char *word)
{
    node *n;
    n = malloc(sizeof(node));
    ft_strcpy(n->word, word);
    n->next = head;
    return (n);
}

// Compare strings to know if the word is in dictionary. If letter is upper case then make it lower case and compare.
int     ft_strcmp(char *one, const char *two)
{
    int i = 0;
    while (one[i] != '\0' && two[i] != '\0' && (one[i] == two[i] || one[i] == two[i] + 32))
    {
        i++;
    }
    if (one[i] - two[i] == 0)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false

bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        int index = hash(word);
        if (hashtable[index] == NULL)
        {
            hashtable[index] = ft_create(word);
        }
        else
        {
            hashtable[index] = ft_insert(hashtable[index], word);
        }
    }
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr->next)
            {
                counter++;
            }
        }
    }
    if (counter != 0)
    {
        return (counter);
    }
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    if (hashtable[index] != NULL)
    {
        for (node *ptr = hashtable[index]; ptr != NULL; ptr = ptr->next)
        {
            if (ft_strcmp(ptr->word, word))
            {
                return true;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false

void    unload_link(node *head)
{
    node *head_copy = head;
    if (head == NULL)
    {
        return;
    }
    else
    {
        return (unload_link(head_copy->next));
    }
    free(head_copy);
}

bool unload(void)
{
    /* we use recursion and go until next is null, then we free current node*/
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            unload_link(hashtable[i]);
            counter++;
        }
    }
    for (int i = 0; i < N; i++)
    {
        if(hashtable[i] == NULL)
        {
            counter++;
        }
    }
    if (counter == 26)
    {
        return true;
    }
    return false;
}
