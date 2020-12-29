#include "constants.h"
#include "task.h"

int change_columns (double *matr, int m, int n, double *add_mem, double *min, int l, int r)
{
  int answer = 0;
  int j = 0;
  double *buff_1 = add_mem + m;
  double *buff_2 = add_mem + 3 * m;
  double *buff_3 = add_mem + 4 * m;

  bool have_left_nbhd = (l != 0);
  bool have_right_nbhd = (r < n);

  if (!have_left_nbhd && !have_right_nbhd)
    {
      if ((r - l) == 1)
        {
          answer += check (nullptr, matr, nullptr, m, n, buff_1, buff_2, min[0]);
          for (int i = 0; i < m; i++)
            matr[i * n] = buff_2[i];
        }


      if ((r - l) == 2)
        {
          answer += check (nullptr, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];


          answer += check (matr + l, matr + l + 1, nullptr, m, n, buff_1, buff_2, min[1]);
          for (int i = 0; i < m; i++)
            {
              matr[l + i * n] = buff_3[i];
              matr[l + 1 + i * n] = buff_2[i];
            }

        }

      if ((r - l) > 2)
        {
          answer += check (nullptr, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];

          for (j = 1; j < (r - l) - 1; j++)
            {
              answer += check (matr + l + j - 1, matr + l + j, matr + l + j + 1, m, n, buff_1, buff_2, min[j]);
              for (int i = 0; i < m; i++)
                {
                  matr[l + j - 1 + i * n] = buff_3[i];
                  buff_3[i] = buff_2[i];
                }
            }


          answer += check (matr + l + j - 1, matr + l + j, nullptr, m, n, buff_1, buff_2, min[j]);
          for (int i = 0; i < m; i++)
            {
              matr[l + j + i * n] = buff_2[i];
              matr[l + j - 1 + i * n] = buff_3[i];
            }
        }
      return answer;

    }
  else if (have_left_nbhd && have_right_nbhd)
    {
      if ((r - l) == 1)
        {
          answer += check_tailed (add_mem, matr + l, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            matr[l + i * n] = buff_2[i];
        }


      if ((r - l) == 2)
        {
          answer += check_tailed_left (add_mem, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];


          answer += check_tailed_right (matr + l, matr + l + 1, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + 1]);
          for (int i = 0; i < m; i++)
            {
              matr[l + i * n] = buff_3[i];
              matr[l + 1 + i * n] = buff_2[i];
            }
        }

      if ((r - l) > 2)
        {
          answer += check_tailed_left (add_mem, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];

          for (j = 1; j < (r - l) - 1; j++)
            {
              answer += check (matr + l + j - 1, matr + l + j, matr + l + j + 1, m, n, buff_1, buff_2, min[l + j]);
              for (int i = 0; i < m; i++)
                {
                  matr[l + j - 1 + i * n] = buff_3[i];
                  buff_3[i] = buff_2[i];
                }
            }

          answer += check_tailed_right (matr + l + j - 1, matr + l + j, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + j]);
          for (int i = 0; i < m; i++)
            {
              matr[l + j + i * n] = buff_2[i];
              matr[l + j - 1 + i * n] = buff_3[i];
            }
        }
      return answer;
    }

  else if (have_left_nbhd && !have_right_nbhd)
    {

      if ((r - l) == 1)
        {
          answer += check_tailed_left (add_mem, matr + l, nullptr, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            matr[l + i * n] = buff_2[i];
        }

      if ((r - l) == 2)
        {
          answer += check_tailed_left (add_mem, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];


          answer += check (matr + l, matr + l + 1, nullptr, m, n, buff_1, buff_2, min[l + 1]);
          for (int i = 0; i < m; i++)
            {
              matr[l + i * n] = buff_3[i];
              matr[l + 1 + i * n] = buff_2[i];
            }
        }

      if ((r - l) > 2)
        {
          answer += check_tailed_left (add_mem, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];


          for (j = 1; j < (r - l) - 1; j++)
            {
              answer += check (matr + l + j - 1, matr + l + j, matr + l + j + 1, m, n, buff_1, buff_2, min[l + j]);
              for (int i = 0; i < m; i++)
                {
                  matr[l + j - 1 + i * n] = buff_3[i];
                  buff_3[i] = buff_2[i];
                }
            }


          answer += check (matr + l + j - 1, matr + l + j, nullptr, m, n, buff_1, buff_2, min[l + j]);
          for (int i = 0; i < m; i++)
            {
              matr[l + j + i * n] = buff_2[i];
              matr[l + j - 1 + i * n] = buff_3[i];
            }
        }

      return answer;
    }
  else if (!have_left_nbhd && have_right_nbhd)
    {
      if ((r - l) == 1)
        {
          answer += check_tailed_right (nullptr, matr + l, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            {
              matr[l + i * n] = buff_2[i];
            }
        }

      if ((r - l) == 2)
        {
          answer += check (nullptr, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];


          answer += check_tailed_right (matr + l, matr + l + 1, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + 1]);
          for (int i = 0; i < m; i++)
            {
              matr[l + i * n] = buff_3[i];
              matr[l + 1 + i * n] = buff_2[i];
            }
        }

      if ((r - l) > 2)
        {
          answer += check (nullptr, matr + l, matr + l + 1, m, n, buff_1, buff_2, min[l + 0]);
          for (int i = 0; i < m; i++)
            buff_3[i] = buff_2[i];

          for (j = 1; j < (r - l) - 1; j++)
            {
              answer += check (matr + l + j - 1, matr + l + j, matr + l + j + 1, m, n, buff_1, buff_2, min[l + j]);
              for (int i = 0; i < m; i++)
                {
                  matr[l + j - 1 + i * n] = buff_3[i];
                  buff_3[i] = buff_2[i];
                }
            }


          answer += check_tailed_right (matr + l + j - 1, matr + l + j, add_mem + 2 * m, m, n, buff_1, buff_2, min[l + j]);
          for (int i = 0; i < m; i++)
            {
              matr[l + j + i * n] = buff_2[i];
              matr[l + j - 1 + i * n] = buff_3[i];
            }
        }

      return answer;
    }

  return answer;
}

int check (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min)
{
  for (int i = 0; i < m; i++)
    {
      buff_1[i] = center[i * n];
      buff_2[i] = center[i * n];
    }

  int answer = 0;

  if (m > 2)
    {
      for (int i = 1; i < m - 1; i++)
        {
          double prev = buff_1[i - 1];
          double curr = buff_1[i];
          double next = buff_1[i + 1];
          if (curr <= next && curr <= prev
              && ((left != nullptr && curr <= left[i * n]) || left == nullptr)
              && ((right != nullptr && curr <= right[i * n]) || right == nullptr))
            {
              answer++;
              buff_2[i] = min;
            }
        }

      double first = buff_1[0];
      if ((first <=  buff_1[1])
          && ((left != nullptr && first <= left[0]) || left == nullptr)
          && ((right != nullptr && first <= right[0]) || right == nullptr))
        {
          answer++;
          buff_2[0] = min;
        }

      double last = buff_1[m - 1];
      if ((last <= buff_1[m - 2])
          && ((left != nullptr && last <= left[(m - 1) * n]) || left == nullptr)
          && ((right != nullptr && last <= right[(m - 1) * n]) || right == nullptr))
        {
          answer++;
          buff_2[(m - 1)] = min;
        }
    }

  return answer;
}

int check_tailed (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min)
{
  for (int i = 0; i < m; i++)
    {
      buff_1[i] = center[i * n];
      buff_2[i] = center[i * n];
    }

  int answer = 0;

  if (m > 2)
    {
      for (int i = 1; i < m - 1; i++)
        {
          double prev = buff_1[i - 1];
          double curr = buff_1[i];
          double next = buff_1[i + 1];
          if (curr <= next && curr <= prev
              && ((left != nullptr && curr <= left[i]) || left == nullptr)
              && ((right != nullptr && curr <= right[i]) || right == nullptr))
            {
              answer++;
              buff_2[i] = min;
            }
        }

      double first = buff_1[0];
      if ((first <=  buff_1[1])
          && ((left != nullptr && first <= left[0]) || left == nullptr)
          && ((right != nullptr && first <= right[0]) || right == nullptr))
        {
          answer++;
          buff_2[0] = min;
        }

      double last = buff_1[m - 1];
      if ((last <= buff_1[m - 2])
          && ((left != nullptr && last <= left[(m - 1)]) || left == nullptr)
          && ((right != nullptr && last <= right[(m - 1)]) || right == nullptr))
        {
          answer++;
          buff_2[(m - 1)] = min;
        }
    }

  return answer;
}

int check_tailed_left (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min)
{

  for (int i = 0; i < m; i++)
    {
      buff_1[i] = center[i * n];
      buff_2[i] = center[i * n];
    }

  int answer = 0;

  if (m > 2)
    {
      for (int i = 1; i < m - 1; i++)
        {
          double prev = buff_1[i - 1];
          double curr = buff_1[i];
          double next = buff_1[i + 1];
          if (curr <= next && curr <= prev
              && ((left != nullptr && curr <= left[i]) || left == nullptr)
              && ((right != nullptr && curr <= right[i * n]) || right == nullptr))
            {
              answer++;
              buff_2[i] = min;
            }

        }

      double first = buff_1[0];
      if ((first <=  buff_1[1])
          && ((left != nullptr && first <= left[0]) || left == nullptr)
          && ((right != nullptr && first <= right[0]) || right == nullptr))
        {
          answer++;
          buff_2[0] = min;
        }


      double last = buff_1[m - 1];
      if ((last <= buff_1[m - 2])
          && ((left != nullptr && last <= left[(m - 1)]) || left == nullptr)
          && ((right != nullptr && last <= right[(m - 1) * n]) || right == nullptr))
        {
          answer++;
          buff_2[(m - 1)] = min;
        }

    }

  return answer;
}

int check_tailed_right (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min)
{

  for (int i = 0; i < m; i++)
    {
      buff_1[i] = center[i * n];
      buff_2[i] = center[i * n];
    }

  int answer = 0;

  if (m > 2)
    {
      for (int i = 1; i < m - 1; i++)
        {
          double prev = buff_1[i - 1];
          double curr = buff_1[i];
          double next = buff_1[i + 1];
          if (curr <= next && curr <= prev
              && ((left != nullptr && curr <= left[i * n]) || left == nullptr)
              && ((right != nullptr && curr <= right[i]) || right == nullptr))
            {
              answer++;
              buff_2[i] = min;
            }
        }

      double first = buff_1[0];
      if ((first <=  buff_1[1])
          && ((left != nullptr && first <= left[0]) || left == nullptr)
          && ((right != nullptr && first <= right[0]) || right == nullptr))
        {
          answer++;
          buff_2[0] = min;
        }

      double last = buff_1[m - 1];
      if ((last <= buff_1[m - 2])
          && ((left != nullptr && last <= left[(m - 1) * n]) || left == nullptr)
          && ((right != nullptr && last <= right[(m - 1)]) || right == nullptr))
        {
          answer++;
          buff_2[(m - 1)] = min;
        }

    }

  return answer;
}

void get_column_buff (double *matr, int  m, int n, int l, int r, double *add_mem)
{
  if (l != 0 && r < n)
    {
      for (int i = 0; i < m; i++)
        {
          add_mem[i] = matr[(l - 1) + i * n];
          add_mem[i + 2 * m] = matr[r + i * n];
        }
    }
  else if (l == 0 && r < n)
    {
      for (int i = 0; i < m; i++)
        add_mem[i + 2 * m] = matr[r + i * n];

    }
  else if (l != 0 && r >= n)
    {
      for (int i = 0; i < m; i++)
        add_mem[i] = matr[(l - 1) + i * n];

    }
}

double find_min (double *matr, int m, int n, int j_)
{
  double min = matr[j_];

  for (int i = 0; i < m; i++)
    min = (matr[j_ + i * n] < min ? matr[j_ + i * n] : min);

  return min;
}
