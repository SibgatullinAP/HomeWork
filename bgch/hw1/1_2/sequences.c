#include "sequences.h"

int check (const char *file_name_1, const char *file_name_2)
{
  FILE *file_1 = fopen (file_name_1, "r");
  if (file_1 == NULL)
    return CANNOT_OPEN_FILE_1;

  FILE *file_2 = fopen (file_name_2, "r");
  if (file_2 == NULL)
    {
      fclose (file_1);
      return CANNOT_OPEN_FILE_1;
    }

  double a_prev = 0;
  double b_prev = 0;
  if (fscanf (file_1, "%lf", &a_prev) != 1)
    {
      if (fscanf (file_2, "%lf", &b_prev))
        {
          fclose (file_1);
          fclose (file_2);
          return EMPTY_FILE_2;
        }
      fclose (file_1);
      fclose (file_2);
      return EMPTY_FILE_1;
    }
  if (fscanf (file_2, "%lf", &b_prev) != 1)
    {
      fclose (file_1);
      fclose (file_2);
      return EMPTY_FILE_2;
    }

  double a_curr = 0;
  if (fscanf (file_1, "%lf", &a_curr) != 1 )
    {
      fclose (file_1);
      fclose (file_2);
      return CANNOT_READ_FILE_1;
    }
  double b_curr = 0;
  if (fscanf (file_2, "%lf", &b_curr) != 1 )
    {
      fclose (file_1);
      fclose (file_2);
      return CANNOT_READ_FILE_2;
    }
  b_prev = b_curr;

  int answer = 1;
  double a_next = 0;
  while (fscanf (file_1, "%lf", &a_next) == 1
         && fscanf (file_2, "%lf", &b_curr) == 1)
    {
      if ((2. * b_prev > a_prev + a_next || 2. * b_prev < a_prev + a_next))
        answer = 0;

      a_prev = a_curr;
      a_curr = a_next;
      b_prev = b_curr;
    }
  if (!feof (file_2) && feof (file_1))
    {
      while (fscanf (file_2, "%lf", &b_prev) == 1);
      answer = 0;
    }
  if (!feof (file_1) && feof (file_2))
    {
      while (fscanf (file_1, "%lf", &a_prev) == 1);
    }

  if (!feof (file_1))
    {
      fclose (file_1);
      fclose (file_2);
      return INVALID_FILE_1;
    }
  if (!feof (file_2))
    {
      fclose (file_1);
      fclose (file_2);
      return INVALID_FILE_2;
    }


  fclose (file_1);
  fclose (file_2);
  return answer;
}
