#include "constants.h"
#include "task.h"


void get_line (double *array, int n, int l, int r, double *add_mem)
{
  bool a_have_next = (r < n);
  bool a_have_after_next = (r < (n - 1));
  bool a_have_prev = (l != 0);
  bool a_have_pre_prev = (l >= 2);

  if (a_have_pre_prev)
    add_mem[0] = array[l - 2];

  if (a_have_prev)
    add_mem[1] = array[l - 1];

  if (a_have_next)
    add_mem[2] = array[r];

  if (a_have_after_next)
    add_mem[3] = array[r + 1];
}

int avg (double *array, double *average, int n, int l, int r, double *add_mem)
{
  double *arr_tmp = array + l;
  int answer = 0;
  int i = 0;

  bool a_have_next = (r < n);
  bool a_have_after_next = (r < (n - 1));
  bool a_have_prev = (l != 0);
  bool a_have_pre_prev = (l >= 2);

  double a_pre_prev;
  double a_prev;
  double a_curr;
  double a_next;
  double a_after_next;

  if ((r - l) == 1)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }

        }
      return 0;
    }

  if ((r - l) == 2)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }
      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {

          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }
        }
      return 0;
    }

  if ((r - l) == 3)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }

      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }
        }

      if (a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {

          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }
        }

      if (!a_have_pre_prev && !a_have_prev && a_have_next && a_have_after_next)
        {

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              return 1;
            }
        }
    }

  if ((r - l) == 4)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[1];
          a_curr = arr_tmp[3];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }

      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }
      if (a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }
          return answer;
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[1];
          a_curr = arr_tmp[3];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }
      if (!a_have_pre_prev && !a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[1];
          a_curr = arr_tmp[3];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }
          return answer;
        }
      if (!a_have_pre_prev && !a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              *average += a_curr;
              answer++;
            }

          return answer;
        }
    }


  if ((r - l) >= 5)
    {
      if (!a_have_pre_prev && a_have_prev)
        {
          i = 1;
          a_pre_prev = add_mem[1];
          a_prev = arr_tmp[i - 1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];
        }


      if (a_have_pre_prev && a_have_prev)
        {
          i = 0;
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];

        }

      if (!a_have_pre_prev && !a_have_prev)
        {
          i = 2;
          a_pre_prev = arr_tmp[i - 2];
          a_prev = arr_tmp[i - 1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];
        }


      for (; i < (r - l) - 3; i++)
        {
          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              *average += a_curr;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = arr_tmp[i + 3];
        }


      if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
        {
          answer++;
          *average += a_curr;
        }

      a_pre_prev = a_prev;
      a_prev = a_curr;

      if (a_have_next)
        {
          a_curr = array[r - 2];
          a_next = array[r - 1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              *average += a_curr;
            }
        }

      a_pre_prev = a_prev;
      a_prev = a_curr;

      if (a_have_after_next)
        {
          a_curr = array[r - 1];
          a_next = add_mem[2];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              *average += a_curr;
            }
        }

      return answer;
    }

  return answer;
}

int change_line (double *array, int n, int l, int r, double *add_mem)
{
  double *arr_tmp = array + l;
  int answer = 0;
  int i = 0;

  bool a_have_next = (r < n);
  bool a_have_after_next = (r < (n - 1));
  bool a_have_prev = (l != 0);
  bool a_have_pre_prev = (l >= 2);

  double a_pre_prev;
  double a_prev;
  double a_curr;
  double a_next;
  double a_after_next;


  if ((r - l) == 1)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              return 1;
            }

        }
      return 0;
    }

  if ((r - l) == 2)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          return answer;
        }
      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              return 1;
            }
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              return 1;
            }
        }
      return 0;
    }

  if ((r - l) == 3)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {

          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          return answer;
        }

      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              return 1;
            }
        }

      if (a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              return 1;
            }
        }

      if (!a_have_pre_prev && !a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              return 1;
            }
        }
    }

  if ((r - l) == 4)
    {
      if (a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[3] = add_mem[5];
              answer++;
            }

          return answer;
        }

      if (a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          return answer;
        }
      if (a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[0] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }
          return answer;
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && a_have_after_next)
        {

          a_pre_prev = add_mem[1];
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = arr_tmp[2];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[3] = add_mem[5];
              answer++;
            }

          return answer;
        }
      if (!a_have_pre_prev && !a_have_prev && a_have_next && a_have_after_next)
        {
          a_pre_prev = arr_tmp[0];
          a_prev = arr_tmp[1];
          a_curr = arr_tmp[2];
          a_next = arr_tmp[3];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[3] = add_mem[5];
              answer++;
            }

          return answer;
        }
      if (!a_have_pre_prev && a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = arr_tmp[2];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          return answer;
        }

      if (!a_have_pre_prev && a_have_prev && !a_have_next && !a_have_after_next)
        {
          a_pre_prev = add_mem[1];
          a_curr = arr_tmp[1];
          a_after_next = arr_tmp[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[1] = add_mem[5];
              answer++;
            }
          return answer;
        }
      if (!a_have_pre_prev && !a_have_prev && a_have_next && !a_have_after_next)
        {
          a_pre_prev = arr_tmp[0];
          a_curr = arr_tmp[2];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              arr_tmp[2] = add_mem[5];
              answer++;
            }

          return answer;
        }
    }

  if ((r - l) >= 5)
    {
      if (!a_have_pre_prev && a_have_prev)
        {
          i = 1;
          a_pre_prev = add_mem[1];
          a_prev = arr_tmp[i - 1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];
        }


      if (a_have_pre_prev && a_have_prev)
        {
          i = 0;
          a_pre_prev = add_mem[0];
          a_prev = add_mem[1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];

        }

      if (!a_have_pre_prev && !a_have_prev)
        {
          i = 2;
          a_pre_prev = arr_tmp[i - 2];
          a_prev = arr_tmp[i - 1];
          a_curr = arr_tmp[i];
          a_next = arr_tmp[i + 1];
          a_after_next = arr_tmp[i + 2];
        }


      for (; i < (r - l) - 3; i++)
        {
          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              arr_tmp[i] = add_mem[5];
            }

          a_pre_prev = a_prev;
          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = arr_tmp[i + 3];
        }


      if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
        {
          answer++;
          arr_tmp[i] = add_mem[5];
        }

      a_pre_prev = a_prev;
      a_prev = a_curr;

      if (a_have_next)
        {
          a_curr = array[r - 2];
          a_next = array[r - 1];
          a_after_next = add_mem[2];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              array[r - 2] = add_mem[5];
            }
        }

      a_pre_prev = a_prev;
      a_prev = a_curr;

      if (a_have_after_next)
        {
          a_curr = array[r - 1];
          a_next = add_mem[2];
          a_after_next = add_mem[3];

          if (a_pre_prev * a_after_next > 0 && a_curr < sqrt (a_pre_prev * a_after_next))
            {
              answer++;
              array[r - 1] = add_mem[5];
            }
        }

      return answer;
    }

  return answer;
}
