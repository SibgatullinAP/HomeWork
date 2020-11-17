#include "interpolations.h"

int read (char *file_name, int array_length, double *arr)
{
  FILE *file = fopen (file_name, "r");
  if (file == nullptr)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < array_length; i++)
    {
      if (fscanf (file, "%lf", arr + i) != 1)
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }
    }

  fclose (file);
  return 1;
}

void print (int array_length, double *arr)
{
  int print_max = (array_length > MAX_PRINT ? MAX_PRINT : array_length);

  for (int i = 0; i < print_max; i++)
    printf ("%lf\n", arr[i]);
}

double lagr_interpolation (int array_length, double x_0, double *x, double *y)
{
  double sum = 0;
  double temp = 0;

  for (int i = 0; i < array_length; i++)
    {
      temp = 1.0;
      for (int j = 0; j < array_length; j++)
        {
          if (i != j)
            temp *= (x_0 - x[j]) / (x[i] - x[j]);
        }
      sum += temp * y[i];
    }
  return sum;
}

double lagr_interpolation_div_diff (int array_length, double x_0, double *x, double *y)
{
  double sum = 0;

  int i = 0;
  for (i = 1; i < array_length; i++)
    {
      for (int j = array_length - 1; j >= i; j--)
        y[j] = (y[j] - y[j - 1]) / (x[j] - x[j - i]);
    }

  for (i = array_length - 1; i > 0; i--)
    {
      sum += y[i];
      sum *= (x_0 - x[i - 1]);
    }

  sum += y[0];

  return sum;
}

double lagr_interpolation_deriv (int array_length, double x_0, double *x, double *y, double *d)
{
  int i = 0;
  for (i = array_length - 1; i > 0; i--)
    y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);

  int j = 0;
  for (i = 2; i < 2 * array_length; i++)
    {
      for (j = 2 * array_length - 1; j >= i; j--)
        {
          if(j & 1)
            {
              d[j / 2] = (d[j / 2] - y[j / 2]) / (x[j / 2] - x[(j - i) / 2]);
            }
          else
            y[j / 2] = (y[j / 2] - d[j / 2 - 1]) / (x[j / 2] - x[(j - i) / 2]);
        }
    }

  double sum = d[array_length - 1];
  for (i = 2 * array_length - 2; i >= 0; i--)
    {
      if (!(i & 1))
        sum = sum * (x_0 - x[i / 2]) + y[i / 2];
      else
        sum = sum * (x_0 - x[i / 2]) + d[i / 2];
    }

  return sum;
}
