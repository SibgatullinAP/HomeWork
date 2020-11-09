#include "common.hpp"
#include "thread_func.hpp"

bool
is_prime (size_t k);

void *
thread_func (void * arg)
{
  static size_t prime_count = 0;
  size_t max_prime = 0;

  Argument * data;
  size_t * count_;
  pthread_barrier_t * b;
  size_t n, p, g;
  size_t step;
  double t;

  size_t i, j;

  data = (Argument *) arg;

  n = (size_t) data -> n;
  p = (size_t) data -> p;
  g = (size_t) data -> g;
  b = data -> b;

  count_ = data -> a;

  t = get_cpu_time ();

  step = 0;

  while (prime_count < n)
    {

      count_[g] = 0;

      for (i = (step * p + g) * ALGO_STEP; i < (step * p + g + 1) * ALGO_STEP; i++)
        {
          if (is_prime (i))
            {
              count_[g] ++;
            }
        }

      pthread_barrier_wait (b);

      if (g == 0)
        {

          for (i = 0; i < p; i++)
            {

              if (count_[i] == 0)
                {
                  continue;
                }

              if (prime_count + count_[i] >= n)
                {

                  count_[i] = 0;

                  for (j = (step * p + i) * ALGO_STEP; prime_count < n; j++)
                    {
                      if (is_prime (j))
                        {
                          max_prime = j;
                          prime_count++;
                        }
                    }

                  break;

                }
              else
                {
                  prime_count += count_[i];
                }

            }

        }

      pthread_barrier_wait (b);

      step++;

    }

  pthread_barrier_wait (b);

  t = get_cpu_time () - t;

  data -> cpu_time = t;

  pthread_barrier_wait (b);

  if (g == 0)
    {
      *(data -> r) = max_prime;
    }

  return nullptr;

}

bool
is_prime (size_t k)
{
  size_t i;

  if (k < 2)
    {
      return false;
    }

  if (k == 2)
    {
      return true;
    }

  if (k % 2 == 0)
    {
      return false;
    }

  for (i = 3; i * i <= k; i += 2)
    {
      if (k % i == 0)
        {
          return false;
        }
    }

  return true;

}
