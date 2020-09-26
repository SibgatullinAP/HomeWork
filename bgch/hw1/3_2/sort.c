#include "sort.h"

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

void print (double *arr, int size)
{
  int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (int i = 0; i < print_limit; i ++)
    printf ("\t[%d] = %.4f\n", i, arr[i]);
}

void merge(const double *arr_1, int size_1,
           const double *arr_2, int size_2, double *result)
{
  int i = 0, j = 0, k = 0;
  while ((i < size_1) && (j < size_2))
    {
      if (arr_1[i] < arr_2[j])
        {
          result[k] = arr_1[i];
          i++;
          k++;
        }
      else
        {
          result[k] = arr_2[j];
          j++;
          k++;
        }
    }

  while (i < size_1)
    {
      result[k] = arr_1[i];
      i++;
      k++;
    }

  while (j < size_2)
    {
      result[k] = arr_2[j];
      j++;
      k++;
    }
}
