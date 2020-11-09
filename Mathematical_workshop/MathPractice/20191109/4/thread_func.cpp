#include "common.hpp"
#include "thread_func.hpp"

bool
is_prime (size_t k);

void *
thread_func (void * arg)
{
  static size_t prev_prime = 2;
  static size_t prime_count = 0;
  static size_t max_distance = 0;

  Argument * data;
  size_t * last_, * count_, * dist_;
  pthread_barrier_t * b;
  size_t n, p, g;
  size_t step, prev, curr, first;
  double t;

  size_t i, j;

  data = (Argument *) arg;

  n = (size_t) data -> n;
  p = (size_t) data -> p;
  g = (size_t) data -> g;
  b = data -> b;

  last_ = data -> a;
  count_ = last_ + p;
  dist_ = count_ + p;

  t = get_cpu_time ();

  step = 0;

  while (prime_count < n)
    {

      prev = curr = dist_[g] = count_[g] = 0;
      first = prev_prime;

      for (i = (step * p + g) * ALGO_STEP; i < (step * p + g + 1) * ALGO_STEP; i++)
        {
          if (is_prime (i))
            {

              if (prev == 0)
                {
                  first = prev = i;
                }
              else
                {
                  dist_[g] = std::max (dist_[g], i - prev);
                  prev = i;
                }

              count_[g] ++;

            }
        }

      last_[g] = prev;

      pthread_barrier_wait (b);

      if (count_[g] != 0)
        {

          prev = 0;

          for (i = g; i > 0; i--)
            {
              if (count_[i - 1] != 0)
                {
                  prev = last_[i - 1];
                  break;
                }
            }

          if (prev == 0)
            {
              prev = prev_prime;
            }

          dist_[g] = std::max (dist_[g], first - prev);

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

              if (prime_count + count_[i] > n)
                {

                  prev = curr = dist_[i] = count_[i] = 0;

                  for (j = (step * p + i) * ALGO_STEP; prime_count < n; j++)
                    {
                      if (is_prime (j))
                        {

                          if (prev == 0)
                            {
                              first = prev = j;
                            }
                          else
                            {
                              dist_[i] = std::max (dist_[i], j - prev);
                              prev = j;
                            }

                          prime_count++;

                        }
                    }

                  prev = 0;

                  for (j = i; j > 0; j--)
                    {
                      if (count_[j - 1] != 0)
                        {
                          prev = last_[j - 1];
                          break;
                        }
                    }

                  if (prev == 0)
                    {
                      prev = prev_prime;
                    }

                  dist_[i] = std::max (dist_[i], first - prev);
                  max_distance = std::max (dist_[i], max_distance);

                  break;

                }
              else if (prime_count + count_[i] == n)
                {
                  max_distance = std::max (max_distance, dist_[i]);
                  prime_count += count_[i];
                  break;
                }
              else
                {
                  max_distance = std::max (max_distance, dist_[i]);
                  prime_count += count_[i];
                }

            }

          for (i = p; i > 0; i--)
            {
              if (count_[i - 1] != 0)
                {
                  prev_prime = last_[i - 1];
                  break;
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
      *(data -> r) = max_distance;
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
