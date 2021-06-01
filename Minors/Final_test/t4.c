#include <stdio.h>
int is_happy_number (int number)
{
  int sum = 0;

  for (int i = 1; i <= number / 2; i++)
    if (number % i == 0)
      sum += i;

  if (number == sum)
    return 1;

  return 0;
}

int main (void)
{
  int number;
  scanf ("%d", &number);
    
  for (; number; scanf ("%d", &number))
    if (is_happy_number (number))
      printf ("%d ", number);
    

  printf("\n");
  return 0;
}