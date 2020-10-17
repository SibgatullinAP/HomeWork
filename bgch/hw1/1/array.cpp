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
  for (int i = 0; i < print_limit; i++)
    printf ("\t[%d] = %.4f\n", i, arr[i]);
}

//2_1
int occurrences (double *arr, int array_size, char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  int answer = 0;

  bool last_is_in_pattern = false;
  int pattern_length = -1;
  double temp = 0;
  int i = 0;
  while (fscanf (file, "%lf", &temp) == 1)
    {
      if ((temp > arr[i] || temp < arr[i]))
        {
          last_is_in_pattern = true;
          pattern_length = i;
          i = 0;
        }
      else
        {
          i++;
          if (i == array_size)
            {
              answer++;
              last_is_in_pattern = false;
              pattern_length = i - 1;
              i = 0;
            }
        }

      for ( ; pattern_length >= 0; pattern_length--)
        {
          int j = 0;
          for (i = 0; j + last_is_in_pattern < pattern_length; j++, i++)
            {
              if ((arr[array_size - pattern_length + j] > arr[i]
                   || arr[array_size - pattern_length + j] < arr[i]))
                break;
            }

          if (j + last_is_in_pattern >= pattern_length)
            {
              if (last_is_in_pattern)
                {
                  if (!(temp > arr[i] || temp < arr[i]))
                    {
                      i++;
                      last_is_in_pattern = false;

                      break;
                    }
                  else
                    i = 0;
                }
              else
                break;
            }
          else
            i = 0;
        }
    }

  if (!feof (file))
    {
      fclose (file);
      return INVALID_FILE;
    }

  fclose (file);
  return answer;
}


//2_2
int shift (double *arr, int size, double x)
{

  int shift = 0;
  for (int i = 0; i < size; i++)
    {
      if (arr[i] < x)
        shift++;
      else
        arr[i - shift] = arr[i];
    }
  return size - shift;
}

//2_3
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