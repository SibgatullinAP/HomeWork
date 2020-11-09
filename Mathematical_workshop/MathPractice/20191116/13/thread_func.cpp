#include "common.hpp"
#include "thread_func.hpp"
#include "task.hpp"

void
print_array (double * a, size_t n);

void *
thread_func (void * arg)
{

  Argument * data;
  pthread_mutex_t * m;
  pthread_barrier_t * b;
  double * a;
  size_t n, p, g;
  size_t l, r;
  double t;

  data = (Argument *) arg;

  a = data -> a;
  n = data -> n;
  p = data -> p;
  g = data -> g;
  m = data -> m;
  b = data -> b;

  if (g == 0)
    {
      printf ("Array at beg: ");
      print_array (a, n);
      fflush (stdout);
    }

  pthread_barrier_wait (b);

  t = get_cpu_time ();

  l = (n * g) / p;
  r = (n * (g + 1)) / p;

  double * s_b_, * s_e_;
  size_t * c_b_, * c_e_;
  bool * is_;

  s_b_ = data -> s;
  s_e_ = s_b_ + p;

  c_b_ = data -> c;
  c_e_ = c_b_ + p;

  is_ = data -> is;

  replace (a, l, r, c_b_[g], s_b_[g], c_e_[g], s_e_[g], is_[g]);

  pthread_barrier_wait (b);

  size_t i, j;

  if (is_[g])
    {
      double sum;
      size_t count;

      sum = s_b_[g];
      count = c_b_[g];

      if (g != 0)
        {

          for (j = g; j > 0; j--)
            {

              i = j - 1;

              if ((n * (i + 1)) / p == 0)
                {
                  continue;
                }

              if (a[(n * (i + 1)) / p - 1] <= a[(n * (i + 1)) / p])
                {
                  break;
                }

              sum += s_e_[i];
              count += c_e_[i];

              if (!is_[i])
                {
                  break;
                }

            }

        }

      if (g != p - 1)
        {

          for (i = g + 1; i < p; i++)
            {

              if ((n * i) / p == 0)
                {
                  continue;
                }

              if (a[(n * i) / p - 1] <= a[(n * i) / p])
                {
                  break;
                }

              sum += s_b_[i];
              count += c_b_[i];

              if (!is_[i])
                {
                  break;
                }

            }

        }

      pthread_barrier_wait (b);

      for (i = l; i < r; i++)
        {
          a[i] = sum / count;
        }

    }
  else
    {
      double sum_b, sum_e;
      size_t count_b, count_e;

      sum_b = s_b_[g];
      count_b = c_b_[g];

      if (g != 0)
        {

          for (j = g; j > 0; j--)
            {

              i = j - 1;

              if ((n * (i + 1)) / p == 0)
                {
                  continue;
                }

              if (a[(n * (i + 1)) / p - 1] <= a[(n * (i + 1)) / p])
                {
                  break;
                }

              sum_b += s_e_[i];
              count_b += c_e_[i];

              if (!is_[i])
                {
                  break;
                }

            }

        }

      sum_e = s_e_[g];
      count_e = c_e_[g];

      if (g != p - 1)
        {

          for (i = g + 1; i < p; i++)
            {

              if ((n * i) / p == 0)
                {
                  continue;
                }

              if (a[(n * i) / p - 1] <= a[(n * i) / p])
                {
                  break;
                }

              sum_e += s_b_[i];
              count_e += c_b_[i];

              if (!is_[i])
                {
                  break;
                }

            }

        }

      pthread_barrier_wait (b);

      for (i = 0; i < c_b_[g]; i++)
        {
          a[l + i] = sum_b / count_b;
        }


      for (i = 0; i < c_e_[g]; i++)
        {
          a[r - i - 1] = sum_e / count_e;
        }

    }

  pthread_barrier_wait (b);

  t = get_cpu_time () - t;

  if (g == 0)
    {
      printf ("Array at end: ");
      print_array (a, n);
      printf ("CPU time (sec): ");
      fflush (stdout);
    }

  pthread_barrier_wait (b);

  pthread_mutex_lock (m);
  printf (" %6.2f (#%3zu)", t, g);
  fflush (stdout);
  pthread_mutex_unlock (m);

  pthread_barrier_wait (b);

  if (g == 0)
    {
      printf ("\n");
    }

  return nullptr;

}

void
print_array (double * a, size_t n)
{
  size_t i;

  for (i = 0; i < std::min (n, MAX_PRINT); i++)
    {
      printf ("%6.2f ", a[i]);
    }

  if (n > MAX_PRINT)
    {
      printf (" ...");
    }

  printf ("\n");

}




//if (g == 0)
//  {

//    printf ("|");
//    for (size_t gg = 0; gg < p; gg++)
//      {
//        size_t ll = (n * gg) / p;
//        size_t rr = (n * (gg + 1)) / p;

//        for (size_t ii = ll; ii < rr; ii++)
//          {
//            printf (" %6.2f", a[ii]);
//          }

//        printf (" |");

//      }

//    printf ("\n");


//  }
