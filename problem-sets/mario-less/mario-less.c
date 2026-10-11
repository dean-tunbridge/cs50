#include "cs50.h"
#include <stdio.h>

int main(void)
{

  int height;

  do
  {
    height = get_int("Height: ");
  } while (height < 1);

  for (int row = 1; row <= height; row++)
  {
    int spaces = height - row;

    for (int i = 0; i < spaces; i++)
    {
      printf(" ");
    }

    for (int j = 0; j < row; j++)
    {
      printf("#");
    }
    printf("\n");
  }
}
