#include "cs50.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
  // Prompt the user for some text
  string text = get_string("Text: ");

  // Count the number of letters, words, and sentences in the text
  int letters = count_letters(text);
  int words = count_words(text);
  int sentences = count_sentences(text);

  float L = 0.0;
  float S = 0.0;

  L = ((float)letters / words) * 100;
  S = ((float)sentences / words) * 100;

  // Compute the Coleman-Liau index
  // index = 0.0588 * L - 0.296 * S - 15.8
  int grade = round(0.0588 * L - 0.296 * S - 15.8);
  // Print the grade level
  if (grade < 1)
  {
    printf("Before Grade 1\n");
  }
  else if (grade >= 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    printf("Grade %i\n", grade);
  }

  return 0;
}

int count_letters(string text)
{

  int letters = 0;
  // Return the number of letters in text
  for (int i = 0; i < strlen(text); i++)
  {
    if (isalpha(text[i]))
    {
      letters++;
    }
  }
  return letters;
}

int count_words(string text)
{
  int words = 1;
  // Return the number of words in text
  for (int i = 0; i < strlen(text); i++)
  {
    if (isspace(text[i]))
    {
      words++;
    }
  }
  return words;
}

int count_sentences(string text)
{
  int sentences = 0;
  // Return the number of sentences in text
  for (int i = 0; i < strlen(text); i++)
  {
    if (text[i] == '.' || text[i] == '!' || text[i] == '?')
    {
      sentences++;
    }
  }
  return sentences;
}
