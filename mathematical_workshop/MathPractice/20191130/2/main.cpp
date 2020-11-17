#include "common.hpp"
#include "thread_func.hpp"

double
formula (size_t i, size_t n, size_t m, size_t p);

double
formula (size_t, size_t, size_t, size_t)
{
  return rand ();
//  return i;
}

int
main (int argc, const char * argv [])
{
  Argument * arguments;
  pthread_t stub;
  pthread_mutex_t m_;
  pthread_barrier_t b_;
  FILE * f;
  double * a;
  double * workspace;
  double t;
  size_t n, m, p;
  size_t ret;
  size_t i, j;

  if (argc != 4 && argc != 5)
    {
      fprintf (stderr, "Use %s n(col) m(row) p [path]\n", argv[0]);
      return BAD_ARGS;
    }

  n = atoi (argv[1]);
  m = atoi (argv[2]);
  p = atoi (argv[3]);

  if (n < 1 || m < 1 || p < 1)
    {
      fprintf (stderr, "Bad n or m or p\n");
      return BAD_ARGS;
    }

  arguments = new Argument [p];
  a = new double [n * m];
  workspace = new double [2 * p * n];

#define DELETE_ARRAY(ptr) if (ptr != nullptr) { delete [] ptr; }

  if (arguments == nullptr || a == nullptr || workspace == nullptr)
    {
      perror ("Can not allocate memory");
      DELETE_ARRAY (arguments);
      DELETE_ARRAY (a);
      DELETE_ARRAY (workspace);
      return BAD_ALLOC;
    }

#undef DELETE_ARRAY

  if (argc == 4)
    {
      srand (1998);
      for (i = 0; i < m; i++)
        {
          for (j = 0; j < n; j++)
            {
              a[i * n + j] = formula (i, n, m, p);
            }
        }
    }
  else
    {

      f = fopen (argv[4], "r");

      if (f == nullptr)
        {
          fprintf (stderr, "Can not open file %s\n", argv[3]);
          delete [] arguments;
          delete [] a;
          delete [] workspace;
          return CAN_NOT_OPEN;
        }

      for (i = 0; i < n * m; i++)
        {
          if (fscanf (f, "%lf", a + i) != 1)
            {
              fprintf (stderr, "Can not read a[%5zu]\n", i);
              delete [] arguments;
              delete [] a;
              delete [] workspace;
              return CAN_NOT_READ;
            }
        }

      fclose (f);

    }

  ret = pthread_mutex_init (&m_, nullptr);

  if (ret != 0)
    {
      perror ("pthread_mutex_init");
      delete [] arguments;
      delete [] a;
      delete [] workspace;
      return ERROR_PTHREAD;
    }

  ret = pthread_barrier_init (&b_, nullptr, p);

  if (ret != 0)
    {
      perror ("pthread_barrier_init");
      delete [] arguments;
      delete [] a;
      delete [] workspace;
      return ERROR_PTHREAD;
    }

  for (i = 0; i < p; i++)
    {
      arguments[i].a = a;
      arguments[i].n = n;
      arguments[i].m = m;
      arguments[i].p = p;
      arguments[i].g = i;
      arguments[i].m_ = &m_;
      arguments[i].b_ = &b_;
      arguments[i].workspace = workspace + 2 * i * n;
    }

  t = get_time ();

  for (i = 1; i < p; i++)
    {

      ret = pthread_create (&stub, nullptr, thread_func, arguments + i);

      if (ret != 0)
        {
          char buf[1 << 8];
          sprintf (buf, "pthread_create on thread #%3zu", i);
          perror (buf);
          abort ();
        }

    }

  thread_func (arguments + 0);

  t = get_time () - t;

  pthread_mutex_destroy (&m_);
  pthread_barrier_destroy (&b_);

  printf ("Total astro time: %6.2f sec\n", t);
  fflush (stdout);

  delete [] arguments;
  delete [] a;
  delete [] workspace;

  return SUCESS;

}
