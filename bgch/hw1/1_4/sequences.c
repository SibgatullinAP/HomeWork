#include "sequences.h"

int type_of_sequence (const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  double a_prev;
  if (fscanf (file, "%lf", &a_prev) != 1)
    {
      if (!feof (file))
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }

      fclose (file);
      return EMPTY_FILE;
    }

  double a_present;
  if (fscanf (file, "%lf", &a_present) != 1)
    {
      if (!feof (file))
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }

      fclose (file);
      return SEQ_TYPE_NOT_ENOUGH_DATA;
    }

  double a_next;
  if (fscanf (file, "%lf", &a_next) != 1)
    {
      if (feof (file))
        {
          if (!(a_next > a_present || a_next < a_present))
            {
              fclose (file);
              return SEQ_TYPE_CONST;
            }
          else
            {
              fclose (file);
              return SEQ_TYPE_NOT_ENOUGH_DATA;
            }
        }

      fclose (file);
      return SEQ_TYPE_UNKNOWN;
    }

  int answer = SEQ_TYPE_UNKNOWN;
  if (!(a_next * a_prev > a_present * a_present)
      && !(a_next * a_prev < a_present * a_present))
    answer = SEQ_TYPE_GEOMETRICAL_PROGRESSION;
  if (!(a_next - a_present > a_present - a_prev)
      && !(a_next - a_present > a_present - a_prev))
    answer = SEQ_TYPE_ARITHMETICAL_PROGRESSION;
  if (!(a_next > a_present || a_next < a_present)
      && !(a_present > a_prev || a_present < a_prev))
    answer = SEQ_TYPE_CONST;

  a_prev = a_present;
  a_present = a_next;

  while (fscanf (file, "%lf", &a_next) == 1)
    {
      if (((a_next - a_present > a_present - a_prev)
           || (a_next - a_present < a_present - a_prev))
          && answer == SEQ_TYPE_ARITHMETICAL_PROGRESSION)
        answer = SEQ_TYPE_UNKNOWN;
      if ((a_next * a_prev > a_present * a_present
           || (a_next * a_prev < a_present * a_present))
          && answer == SEQ_TYPE_GEOMETRICAL_PROGRESSION)
        answer = SEQ_TYPE_UNKNOWN;
      if (((a_next > a_present || a_next < a_present)
           || (a_present > a_prev || a_present < a_prev))
          && answer == SEQ_TYPE_CONST)
        answer = SEQ_TYPE_UNKNOWN;

      a_prev = a_present;
      a_present = a_next;
    }

  if (!feof (file))
    {
      fclose (file);
      return INVALID_FILE;
    }

  fclose (file);
  return answer;
}
