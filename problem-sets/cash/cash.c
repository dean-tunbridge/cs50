#include "cs50.h"
#include <stdio.h>

int main(void)
{
  int change;

  do
  {
    change = get_int("Change owed: ");
  } while (change <= 0);

  int coins = 0;
  int quarter = 25;
  int dime = 10;
  int nickel = 5;

  coins += change / quarter;
  change = change % quarter;
  coins += change / dime;
  change = change % dime;
  coins += change / nickel;
  change = change % nickel;
  coins += change;

  printf("%i\n", coins);
}
