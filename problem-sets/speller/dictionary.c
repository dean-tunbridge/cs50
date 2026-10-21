// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Init count for word count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  // TODO
  int index = hash(word);
  node *cursor = table[index];

  while (cursor != NULL)
  {
    if (strcasecmp(cursor->word, word) == 0)
    {
      return true;
    }
    else
    {
      cursor = cursor->next;
    }
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
  // Open the dictionary file
  FILE *source = fopen(dictionary, "r");
  if (source == NULL)
  {
    return false;
  }
  // Read each word in the file
  char buffer[LENGTH + 1];

  while (fscanf(source, "%s", buffer) == 1)
  {
    // Add each word to the hash table
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
      fclose(source);
      return false;
    }
    strcpy(new_node->word, buffer);
    int index = hash(buffer);
    new_node->next = table[index];
    table[index] = new_node;
    word_count++;
  }

  // Close the dictionary file
  fclose(source);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  // TODO
  if (word_count <= 0)
  {
    return 0;
  }
  else
  {
    return word_count;
  }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  // TODO

  return false;
}
