#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
  // Make sure program was run with just one command-line argument
  if (argc != 2)
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }
  // Make sure every character in argv[1] is a digit
  for (int i = 0; i < strlen(argv[1]); i++)
  {
    if (!isdigit(argv[1][i]))
    {
      return 1;
    }
  }

  // Convert argv[1] from a `string` to an `int`
  int KEY = atoi(argv[1]);
  // Prompt user for plaintext
  string text = get_string("plaintext: ");
  // For each character in the plaintext:
  for (int i = 0; i < strlen(text); i++)
  {
    // Rotate the character if it's a letter
    if (isalpha(text[i]))
    {
      if (isupper(text[i]))
      {
        text[i] = ((text[i] - 'A') + KEY) % 26 + 'A';
      }
      else if (islower(text[i]))
      {
        text[i] = ((text[i] - 'a') + KEY) % 26 + 'a';
      }
    }
  }

  printf("ciphertext: %s\n", text);
  return 0;
}
