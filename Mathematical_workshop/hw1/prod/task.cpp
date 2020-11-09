#include "task.h"

int task (const char * file_name)
{
  FILE * file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  double x_prev, x_curr, x_next;
  if (fscanf (file, "%lf%lf", &x_prev, &x_curr) != 2)
    {
      if (!feof (file))
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }

      fclose (file);
      return 0;
    }

  int ret = 0;
  while (fscanf (file, "%lf", &x_next) == 1)
    {
      if (x_prev < x_curr && x_prev < x_next)
        ret++;

      x_prev = x_curr;
      x_curr = x_next;
    }

  if (!feof (file))
    {
      fclose (file);
      return CANNOT_READ_FILE;
    }

  fclose (file);
  return ret;
}
