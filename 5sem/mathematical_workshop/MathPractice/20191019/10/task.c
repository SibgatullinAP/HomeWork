#include <stdio.h>
#include "task.h"


int
task (const char * path)
{
  FILE * f;
  double x1, x2, x3;
  int ret;

  f = fopen (path, "r");

  if (f == NULL)
    {
      return CANT_OPEN_FILE;
    }

  if (fscanf (f, "%lf%lf", &x1, &x2) != 2)
    {

      if (!feof (f))
        {
          fclose (f);
          return CANT_READ_FILE;
        }

      fclose (f);
      return 0;

    }

  ret = 0;

  while (fscanf (f, "%lf", &x3) == 1)
    {

      if (x1 < x2 && x1 < x3)
        {
          ret++;
        }

      x1 = x2;
      x2 = x3;

    }

  if (!feof (f))
    {
      fclose (f);
      return CANT_READ_FILE;
    }

  fclose (f);

  return ret;

}
