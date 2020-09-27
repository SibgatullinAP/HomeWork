#include "sequences.h"

int rms_deviation (const char *file_name, double *answer)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  int n = 0;
  double sum = 0;
  double sum_of_squares = 0;
  double temp = 0;
  while (fscanf (file, "%lf", &temp) == 1)
    {
      sum += temp;
      sum_of_squares += temp * temp;
      n++;
    }

  if (n == 0)
    {
      if (feof (file))
        {
          fclose (file);
          return EMPTY_FILE;
        }
      else
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

  *answer = sqrt ((sum_of_squares * n - sum * sum) / (n * n * 1.));

  fclose (file);
  return n;
}
