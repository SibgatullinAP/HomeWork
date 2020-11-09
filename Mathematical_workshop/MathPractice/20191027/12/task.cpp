#include "common.hpp"
#include "task.hpp"

int
average_of_min_max (const char * path, double * min__, double * max__)
{
  FILE * f;
  double cur, min, max;

  f = fopen (path, "r");

  if (f == nullptr)
    {
      return CAN_NOT_OPEN;
    }

  if (fscanf (f, "%lf", &cur) != 1)
    {

//      if (!feof (f))
//        {
//          fclose (f);
//          return CAN_NOT_READ;
//        }

//      fclose (f);
//      *result = 0.;
//      return SUCESS;

      fclose (f);
      return CAN_NOT_READ;

    }

  max = min = cur;

  while (fscanf (f, "%lf", &cur) == 1)
    {
      max = std::max (max, cur);
      min = std::min (min, cur);
    }

  if (!feof (f))
    {
      fclose (f);
      return CAN_NOT_READ;
    }

  fclose (f);
  *min__ = min;
  *max__ = max;
  return SUCESS;

}

// считается что файлы открываются читаются и все ок
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
