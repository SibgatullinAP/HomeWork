#include "array.h"

int read (const char *file_name, double *arr, int size)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < size; i ++)
    {
      if (fscanf (file, "%lf", (arr + i)) != 1)
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }
    }

  if (!feof (file))
    {
      fclose (file);
      return INVALID_FILE;
    }

  fclose (file);
  return 0;
}

void randomize (double *arr, int array_size)
{
  srand (0);
  for (int i = 0; i < array_size; i++)
    {
      int denominator = rand() % 10000;
      denominator = (denominator != 0 ? denominator : 19 );
      arr[i] = (double) rand () / (double) denominator;
    }
}


void print (double *arr, int size)
{
  int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (int i = 0; i < print_limit; i ++)
    printf ("\t[%d] = %.4f\n", i, arr[i]);
}

int greatest_common_devisor(int x, int y)
{
  while (y != 0)
    {
      int r = x % y;
      x = y;
      y = r;
    }
  return x;
}

void shift_to_k (double *arr, int size, int shift)
{
  if (size == 0)
    return;

  shift %= size;
  if (shift == 0)
    return;

  if (shift < 0)
    shift += size;

  int i = 0;
  int gcd = greatest_common_devisor (size, shift);
  while (i < gcd)
    {
      int i_inverse = i - shift;
      if (i_inverse < 0)
        i_inverse += size;
      double temp = arr[i_inverse];

      while (i_inverse != i)
        {
          int l = i_inverse - shift;
          if (l < 0)
            l += size;
          arr[i_inverse] = arr[l];
          i_inverse = l;
        }
      arr[i] = temp;
      i++;
    }
}
