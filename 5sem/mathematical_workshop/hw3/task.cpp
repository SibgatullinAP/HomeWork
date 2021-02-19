#include "constants.h"
#include "task.h"


int min_finder (const char *file_name, double *min_)
{
  FILE * file = fopen (file_name, "r");
  if (file == nullptr)
    return CANNOT_OPEN_FILE;

  double min_answer = 0;
  if (fscanf (file, "%lf", &min_answer) != 1)
    {
      if (!feof (file))
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }

      fclose (file);
      return 0;
    }

  int counter = 0;
  double x = 0;
  while (fscanf (file, "%lf", &x) == 1)
    {
      counter++;
      if (x < min_answer)
        min_answer = x;
    }

  if (!feof (file))
    {
      fclose (file);
      return CANNOT_READ_FILE;
    }

  fclose (file);

  *min_ = min_answer;
  if (counter == 0)
    return 0;

  return 1;
}

int counter (const char *file_name, double min)
{
  FILE *file = fopen (file_name, "r");
  double x;
  int answer = 0;

  while (fscanf (file, "%lf", &x) == 1)
    {
      if (x < (min * 0.5))
        answer++;
    }

  fclose (file);
  return answer;
}
