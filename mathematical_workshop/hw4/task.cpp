#include "constants.h"
#include "task.h"


void get_line (double *array, int n, int l, int r, double *add_mem)
{
  bool a_have_next = (r < n);
  bool a_have_after_next = (r < (n - 1));
  bool a_have_prev = (l != 0);

  if (a_have_prev)
    add_mem[0] = array[l - 1];

  if (a_have_next)
    add_mem[1] = array[r];

  if (a_have_after_next)
    add_mem[2] = array[r + 1];
}

int change_line (double *array, int n, int l, int r, double *add_mem)
{

  double *arr_tmp = array + l;
  double a_prev;
  double a_curr;
  double a_next;
  double a_after_next;
  double a_changed;

  int answer = 0;

  bool a_have_next = (r < n);
  bool a_have_after_next = (r < n - 1);
  bool a_have_prev = (l != 0);

  if ((r - l) == 1)
    {
      if (a_have_prev && a_have_next && a_have_after_next && a_have_next)
        {
          arr_tmp[0] = (add_mem[0] + arr_tmp[0] + add_mem[1] + add_mem[2]) / 4;
          return 1;
        }
      return 0;
    }

  if ((r - l) == 2)
    {
      if (a_have_prev && a_have_next && a_have_after_next)
        {

          a_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = add_mem[1];

          arr_tmp[0] = (a_prev + a_curr + a_next + a_after_next) / 4;

          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 2;
        }

      if (a_have_next && a_have_after_next)
        {
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = add_mem[1];
          a_after_next = add_mem[2];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 1;
        }

      if (a_have_prev && a_have_after_next)
        {

          a_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = add_mem[1];

          arr_tmp[0] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 1;
        }


      if (a_have_prev && a_have_next && a_have_after_next && a_have_next)
        {
          arr_tmp[0] = (add_mem[0] + arr_tmp[0] + add_mem[1] + add_mem[2]) / 4;
          return 1;
        }

      return 0;
    }

  if ((r - l) == 3)
    {
      if (a_have_prev && a_have_next && a_have_after_next)
        {

          a_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          arr_tmp[0] = (a_prev + a_curr + a_next + a_after_next) / 4;

          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[1];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          arr_tmp[2] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 3;
        }

      if (a_have_prev && a_have_next)
        {
          a_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          arr_tmp[0] = (a_prev + a_curr + a_next + a_after_next) / 4;

          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[1];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 2;
        }
      if (a_have_prev)
        {
          a_prev = add_mem[0];
          a_curr = arr_tmp[0];
          a_next = arr_tmp[1];
          a_after_next = arr_tmp[2];

          arr_tmp[0] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 1;
        }
      if (a_have_next && a_have_after_next)
        {
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = arr_tmp[2];
          a_after_next = add_mem[1];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          a_prev = a_curr;
          a_curr = a_next;
          a_next = a_after_next;
          a_after_next = add_mem[2];

          arr_tmp[2] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 2;
        }
      if (a_have_next)
        {
          a_prev = arr_tmp[0];
          a_curr = arr_tmp[1];
          a_next = arr_tmp[2];
          a_after_next = add_mem[1];

          arr_tmp[1] = (a_prev + a_curr + a_next + a_after_next) / 4;

          return 1;
        }

      return 0;
    }

  int i = (a_have_prev ? 0 : 1);

  a_prev = (a_have_prev ? add_mem[0] : arr_tmp[i - 1]);
  a_curr = arr_tmp[i];
  a_next = (((r - l) <= 2) ? 0 : arr_tmp[i + 1]);
  a_after_next = (((r - l - i) < 3) ? 0 : arr_tmp[i + 2]);

  a_changed = (a_prev + a_curr + a_next + a_after_next) / 4;

  for (; i < (r - l) - 3; i++)
    {
      a_changed = (a_prev + a_curr + a_next + a_after_next) / 4;

      arr_tmp[i] = a_changed;

      a_prev = a_curr;
      a_curr = a_next;
      a_next = a_after_next;
      a_after_next = arr_tmp[i + 3];

      answer++;
    }

  a_changed = (a_prev + a_curr + a_next + a_after_next) / 4;
  a_prev = a_curr;
  arr_tmp[i] = a_changed;



  if (a_have_next)
    {
      a_curr = array[r - 2];
      a_next = array[r - 1];
      a_after_next = add_mem[1];
      a_changed = (a_prev + a_curr + a_next + a_after_next) / 4;

      answer++;

      a_prev = array[r - 2];
      array[r - 2] = a_changed;

      if (a_have_after_next)
        {
          a_curr = array[r - 1];
          a_next = add_mem[1];
          a_after_next = add_mem[2];

          a_changed = (a_prev + a_curr + a_next + a_after_next) / 4;

          answer++;

          a_prev = array[r - 1];
          array[r - 1] = a_changed;
        }
    }

  return answer + 1;
}
