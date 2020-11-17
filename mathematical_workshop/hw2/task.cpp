#include "constants.h"
#include "task.h"


int avg (const char *file_name, double *avg_)
{
  FILE * file = fopen (file_name, "r");
  if (file == nullptr)
    return CANNOT_OPEN_FILE;

  double x = 0;
  double sum = 0;
  int counter = 0;

  while (fscanf (file, "%lf", &x) == 1)
    {
      if (x > 0)
        {
          sum += x;
          counter++;
        }
    }

  if (!feof (file))
    {
      fclose (file);
      return CANNOT_READ_FILE;
    }

  fclose (file);
  if (counter == 0)
    return CANNOT_READ_FILE;

  *avg_ = sum / (double) counter;
  return 0;
}

int counter (const char *file_name, double avg)
{
  FILE *file = fopen (file_name, "r");
  double x;
  int answer = 0;

  while (fscanf (file, "%lf", &x) == 1)
    {
      if (x > avg)
        answer++;
    }

  fclose (file);
  return answer;
}
