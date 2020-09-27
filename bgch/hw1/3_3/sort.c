#include "sort.h"

int read (const char *file_name, double *arr, int size)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  int i;
  for (i = 0; i < size; i ++)
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

void print (double *arr, int size)
{
  int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (int i = 0; i < print_limit; i ++)
    printf("\t[%d] = %.4f\n", i, arr[i]);
}


int array_redbuilding (double *arr, int size, double x)
{
  int left = 0;
  int right = size - 1;
  while (left <= right)
    {
      while (arr[left] < x)
        left++;
      while (arr[right] > x)
        right--;
      if (left <= right)
        {
          swap (arr, left, right);
          right--;
          left++;
        }
    }

  return left;
}

void swap (double *a, int i, int j)
{
  double buff = a[j];
  a[j] = a[i];
  a[i] = buff;
}
