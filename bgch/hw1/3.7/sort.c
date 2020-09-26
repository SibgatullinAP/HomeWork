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

  if (!feof(file))
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
  int i;
  for (i = 0; i < print_limit; i ++)
    printf("\t[%d] = %.4f\n", i, arr[i]);
}

void check (double *arr, int size)
{
  for (int i = 0; i < size - 1; i++)
    {
      if (arr[i] > arr[i+1])
        {
          printf("\x1b[31m[UNSORTED]\x1b[0m\n");
          return;
        }
    }
    printf("\x1b[32m[SORTED]\x1b[0m\n");
}

void heap_sort(double *arr, int size)
{
    int i;
    for (i = (size / 2) - 1; i >= 0; i--)
      create_heap(arr, i, size);

    for (i = size - 1; i >= 0; i--)
      {
        swap(arr, 0, i);
        create_heap(arr, 0, i);
      }
}


void create_heap(double *arr, int root, int bottom)
{
  int flag = 1, max;
  while ((root * 2 <= bottom) && flag)
    {
      if (root * 2 == bottom)
        max = root * 2;
      else
        {
          if (arr[root * 2] > arr[root * 2 + 1])
            max = root * 2;
          else
            max = root * 2 + 1;

          if(arr[root] < arr[max])
            {
                swap(arr, root, max);
                root = max;
            }
          else
            flag = 0;
        }
  }
}

void swap (double *a, int i, int j)
{
  double buff = a[j];
  a[j] = a[i];
  a[i] = buff;
}
