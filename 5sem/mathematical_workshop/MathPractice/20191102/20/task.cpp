#include "common.hpp"
#include "task.hpp"

int
calc_count (const char * path, int * count, int * size, double * sum,
            double * beg1, double * beg2, double * end1, double * end2)
{
  FILE * f;
  double x1, x2, x3;

  f = fopen (path, "r");

  if (f == nullptr)
    {
      return CAN_NOT_OPEN;
    }

  *count = fscanf (f, "%lf%lf", &x1, &x2);

  /* empty file. */
  if (*count == EOF)
    {
      *count = *size = 0;
      fclose (f);
      return SUCESS;
    }
  else if (*count == 0)
    {
      fclose (f);
      return CAN_NOT_READ;
    }
  else if (*count == 1)
    {

      if (! feof (f))
        {
          fclose (f);
          return CAN_NOT_READ;
        }

      *beg1 = *end2 = x1;
      *sum = 0;
      *size = 1;
      *count = 0;

      return SUCESS;

    }

  /* *count == 2 */

  *beg1 = x1;
  *beg2 = x2;
  *size = 2;
  *count = 0;

  while (fscanf (f, "%lf", &x3) == 1)
    {

      *size += 1;

      if (x1 > x2 || x2 > x3)
        {
          *count += 1;
          *sum += x2;
        }

      x1 = x2;
      x2 = x3;

    }

  if (!feof (f))
    {
      fclose (f);
      return CAN_NOT_READ;
    }

  *end1 = x1;
  *end2 = x2;

  fclose (f);

  return SUCESS;

}

int
count_great (const char * path, double x)
{
  FILE * f;
  double cur;
  int count;

  f = fopen (path, "r");

  count = 0;

  while (fscanf (f, "%lf", &cur) == 1)
    {
      if (cur > x)
        {
          count ++;
        }
    }

  fclose (f);

  return count;

}
