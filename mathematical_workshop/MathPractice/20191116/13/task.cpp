#include "common.hpp"
#include "task.hpp"

void
replace (double * a, size_t l, size_t r,
         size_t & c_b, double & s_b,
         size_t & c_e, double & s_e,
         bool & is_same)
{
  size_t i, j;

  if (l == r)
    {
      c_b = c_e = 0;
      s_b = s_e = 0;
      is_same = true;
      return;
    }

  c_b = c_e = 1;
  s_b = a[l];
  s_e = a[r - 1];

  for (i = l + 1; i < r; i++)
    {
      if (a[i - 1] > a[i])
        {
          c_b += 1;
          s_b += a[i];
        }
      else
        {
          break;
        }
    }


  for (j = r - 1; j > l; j--)
    {

      i = j - 1;

      if (a[i] > a[i + 1])
        {
          c_e += 1;
          s_e += a[i];
        }
      else
        {
          break;
        }

    }

  if (c_b == r - l && c_e == r - l)
    {
      is_same = true;
      return;
    }

  is_same = false;

  double sum;
  size_t count;

  for (i = l + c_b + 1; i < r - c_e; )
    {

      if (a[i - 1] > a[i])
        {


          sum = a[i - 1];
          count = 1;

          for (j = i; a[j - 1] > a[j]; j++)
            {
              sum += a[j];
              count += 1;
            }

          for (j = 0; j < count; j++)
            {
              a[i + j - 1] = sum / count;
            }

          i += count;

        }
      else
        {
          i++;
        }

    }

}


















