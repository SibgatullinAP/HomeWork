#include "sequences.h"

//1_1
int rebuild_sequnce (const char *file_name, int k)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  int curr = 0;
  int counter_1 = 0;
  int is_first_seq = 0;
  bool ans_is_changed = false;
  int answer = 0;
  int temp = 0;
  int spacing = 0;
  while (fscanf (file, "%d", &curr) == 1)
    {
      temp = curr;
      int curr_bit = 1;
      for (; temp > 1; temp >>= 1)
        curr_bit <<= 1;

      while (curr_bit)
        {
          temp = curr & curr_bit;
          curr_bit >>= 1;

          if (temp == 0)
            {
              printf ("0");
              if (counter_1 >= k)
                {
                  if (is_first_seq)
                    {
                      spacing -= (counter_1 + is_first_seq);
                      if (spacing && (spacing < answer || !ans_is_changed))
                        {
                          ans_is_changed = true;
                          answer = spacing;
                        }
                      spacing = counter_1;
                    }
                  is_first_seq = counter_1;
                }
              spacing++;
              counter_1 = 0;
            }
          else
            {
              printf ("1");
              spacing ++;
              counter_1 ++;
            }

          if (!is_first_seq && counter_1 == 1)
            spacing = 1;
        }
    }

  if (!feof (file))
    {
      fclose (file);
      return CANNOT_READ_FILE;
    }

  fclose (file);

  if (temp && is_first_seq && (counter_1 >= k))
    {
      spacing -= (counter_1 + is_first_seq);
      if (spacing && (spacing < answer || !ans_is_changed))
        answer = spacing;
    }

  if (answer < 0)
    return INVALID_FILE;

  if (!ans_is_changed)
    return 0;

  return answer;
}

//1_2
int check (const char *file_name_1, const char *file_name_2)
{
  FILE *file_1 = fopen (file_name_1, "r");
  if (file_1 == NULL)
    return CANNOT_OPEN_FILE_1;

  FILE *file_2 = fopen (file_name_2, "r");
  if (file_2 == NULL)
    {
      fclose (file_1);
      return CANNOT_OPEN_FILE_2;
    }

  double b_prev = 0;
  if (fscanf (file_2, "%lf", &b_prev) != 1)
    {
      if (feof (file_2))
        {
          fclose (file_1);
          fclose (file_2);
          return EMPTY_FILE_2;
        }
      else
        {
          fclose (file_1);
          fclose (file_2);
          return CANNOT_READ_FILE_2;
        }
    }

  double b_curr = 0;
  if (fscanf (file_2, "%lf", &b_curr) != 1)
    {
      if (feof (file_2))
        {
          fclose (file_1);
          fclose (file_2);
          return 1;
        }
      else
        {
          fclose (file_1);
          fclose (file_2);
          return CANNOT_READ_FILE_2;
        }
    }

  b_prev = b_curr;
  double a_prev = 0;
  double a_curr = 0;
  if (fscanf (file_1, "%lf%lf", &a_prev, &a_curr) != 2)
    {
      if (fscanf (file_2, "%lf", &b_curr) != 1)
        {
          if (feof (file_2))
            {
              fclose (file_1);
              fclose (file_2);
              return 1;
            }
          else
            {
              fclose (file_1);
              fclose (file_2);
              return CANNOT_READ_FILE_1;
            }
        }
      if (feof (file_1))
        {
          fclose (file_1);
          fclose (file_2);
          return INVALID_FILE_1;
        }

      fclose (file_1);
      fclose (file_2);
      return CANNOT_READ_FILE_1;
    }

  double a_next = 0;
  while (fscanf (file_2, "%lf", &b_curr) == 1)
    {
      if (fscanf (file_1, "%lf", &a_next) != 1)
        {
          if (feof (file_1))
            {
              fclose (file_1);
              fclose (file_2);
              return INVALID_FILE_1;
            }

          fclose (file_1);
          fclose (file_2);
          return CANNOT_READ_FILE_1;
        }
      if ((2. * b_prev > a_prev + a_next || 2. * b_prev < a_prev + a_next))
        {
          fclose (file_1);
          fclose (file_2);
          return 0;
        }

      a_prev = a_curr;
      a_curr = a_next;
      b_prev = b_curr;
    }

  if (!feof (file_2))
    {
      fclose (file_1);
      fclose (file_2);
      return INVALID_FILE_2;
    }

  fclose (file_1);
  fclose (file_2);
  return 1;
}

//1_3
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

  *answer = sqrt ((sum_of_squares * n - sum * sum) / ((double) (n * n)));

  fclose (file);
  return n;
}

//1_4
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