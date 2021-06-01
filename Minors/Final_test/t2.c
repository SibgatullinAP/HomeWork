#include <stdio.h>

int count_beatles (int number)
{
  int count = 0;

  for (int i = 0; i <= number; i += 8)
  {
    if ((number - i) % 6 == 0)
    {
      count++;
    }
  }

  if (number == 0)
    return 0;

  return count;
}

int main (void)
{
  int number;
  scanf ("%d", &number);

  printf ("%d\n", count_beatles (number));
  return 0;
}