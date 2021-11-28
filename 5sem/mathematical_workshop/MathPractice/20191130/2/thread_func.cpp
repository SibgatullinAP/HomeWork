#include "common.hpp"
#include "thread_func.hpp"
#include "task.hpp"

void
print_matrix (double * a, size_t n, size_t m);

void *
thread_func (void * arg)
{

  Argument * data;
  pthread_mutex_t * m_;
  pthread_barrier_t * b_;
  double * a;
  size_t n, m, p, g;
  double * w; // workspace
  size_t l, r;
  double t;

  data = (Argument *) arg;

  a = data -> a;
  n = data -> n;
  m = data -> m;
  p = data -> p;
  g = data -> g;
  m_ = data -> m_;
  b_ = data -> b_;
  w = data -> workspace;

  if (g == 0)
    {
      printf ("Matrix at beg:\n");
      print_matrix (a, n, m);
      fflush (stdout);
    }

  pthread_barrier_wait (b_);

  t = get_cpu_time ();

  l = (m * g) / p;
  r = (m * (g + 1)) / p;

  if (n > 2 && m > 2 && l != r)
    {

      if (l == 0)
        {
          l = 1;
          memcpy (w, a, n * sizeof (double));
        }

      memcpy (w, a + (l - 1) * n, n * sizeof (double));

      if (r == m)
        {
          r = m - 1;
        }

      memcpy (w + n, a + r * n, n * sizeof (double));

      pthread_barrier_wait (b_);

      for (size_t i = l; i < r - 1; i++)
        {
          replace (w, a + i * n, a + (i + 1) * n, n);
        }

      if (r != 1 && l != r)
        {
          replace (w, a + (r - 1) * n, w + n, n);
        }
    }
  else
    {
      pthread_barrier_wait (b_);
    }

  pthread_barrier_wait (b_);

  t = get_cpu_time () - t;

  if (g == 0)
    {
      printf ("Matrix at end:\n");
      print_matrix (a, n, m);
      printf ("CPU time (sec): ");
      fflush (stdout);
    }

  pthread_barrier_wait (b_);

  pthread_mutex_lock (m_);
  printf (" %6.2f (#%3zu)", t, g);
  fflush (stdout);
  pthread_mutex_unlock (m_);

  pthread_barrier_wait (b_);

  if (g == 0)
    {
      printf ("\n");
    }

  return nullptr;

}

void
print_matrix (double * a, size_t n, size_t m)
{
  size_t i, j;

  for (i = 0; i < std::min (MAX_PRINT, m); i++)
    {

      for (j = 0; j < std::min (MAX_PRINT, n); j++)
        {
          printf ("%+6.2f ", a[i * n + j]);
        }

      if (n != std::min (MAX_PRINT, n))
        {
          printf ("...\n");
        }
      else
        {
          printf ("\n");
        }

    }

  if (m != std::min (MAX_PRINT, m))
    {
      for (i = 0; i < std::min (MAX_PRINT, n); i++)
        {
          printf ("       ... ");
        }
      printf ("...\n");
    }

  printf ("\n");

}
