#include "func.h"

#include "constants.h"

double f_1 (double x)
{
  return x;
}

double f_2 (double x)
{
  return -1.0 * x * x + 1.0;
}

double f_3 (double x)
{
  return x * x * x - 2.0 * x * x + x;
}

double f_4 (double x)
{
  if (x < 0)
    {
      printf ("[ERROR] x should be > 0, due to domain of square root funtion. Will be used |X| instead of X\n");
      return sqrt (fabs (x)) - 3.0;
    }
  else
    return sqrt (x) - 3.0;
}

double f_5 (double x)
{
  return 1.0 / (x * x + 1.0);
}

double d_1 (double x)
{
  (void) x;
  return 1.0;
}

double d_2 (double x)
{
  return -2.0 * x;
}

double d_3 (double x)
{
  return 3.0 * x * x - 4.0 * x + 1.0;
}

double d_4 (double x)
{
  return 1.0 / (2.0 * sqrt (x));
}

double d_5 (double x)
{
  return -1.0 * (2.0 * x) / ((x * x + 1.0) * (x * x + 1.0));
}
