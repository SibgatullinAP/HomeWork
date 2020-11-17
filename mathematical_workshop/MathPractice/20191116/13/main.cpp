#include "common.hpp"
#include "thread_func.hpp"

double
formula (size_t i, size_t n, size_t p);

double
formula (size_t i, size_t, size_t)
{
  return i;
}

int
main (int argc, const char * argv [])
{
  Argument * arguments;
  pthread_t stub;
  pthread_mutex_t m;
  pthread_barrier_t b;
  FILE * f;
  double * a;
  double * s;
  size_t * c;
  bool * is;
  double t;
  size_t n, p;
  size_t ret;
  size_t i;

  if (argc != 3 && argc != 4)
    {
      fprintf (stderr, "Use %s n p [path]\n", argv[0]);
      return -1;
    }

  n = atoi (argv[1]);
  p = atoi (argv[2]);

  if (n < 1 || p < 1)
    {
      fprintf (stderr, "Bad n or p\n");
      return -1;
    }

  arguments = new Argument [p];
  a = new double [n];
  s = new double [2 * p];
  c = new size_t [2 * p];
  is = new bool [p];

#define DELETE_ARRAY(ptr) if (ptr != nullptr) { delete [] ptr; }

  if (arguments == nullptr || a == nullptr
      || s == nullptr || c == nullptr || is == nullptr)
    {
      perror ("Can not allocate memory");
      DELETE_ARRAY (arguments);
      DELETE_ARRAY (a);
      DELETE_ARRAY (s);
      DELETE_ARRAY (c);
      DELETE_ARRAY (is);
      return -1;
    }

#undef DELETE_ARRAY

  if (argc == 3)
    {
      for (i = 0; i < n; i++)
        {
          a[i] = formula (i, n, p);
        }
    }
  else
    {

      f = fopen (argv[3], "r");

      if (f == nullptr)
        {
          fprintf (stderr, "Can not open file %s\n", argv[3]);
          delete [] arguments;
          delete [] a;
          return -1;
        }

      for (i = 0; i < n; i++)
        {
          if (fscanf (f, "%lf", a + i) != 1)
            {
              fprintf (stderr, "Can not read a[%3zu]\n", i);
              delete [] arguments;
              delete [] a;
              return -1;
            }
        }

      fclose (f);

    }

  ret = pthread_mutex_init (&m, nullptr);

  if (ret != 0)
    {
      perror ("pthread_mutex_init");
      delete [] arguments;
      delete [] a;
      return ERROR_PTHREAD;
    }

  ret = pthread_barrier_init (&b, nullptr, p);

  if (ret != 0)
    {
      perror ("pthread_barrier_init");
      delete [] arguments;
      delete [] a;
      return ERROR_PTHREAD;
    }

  for (i = 0; i < p; i++)
    {
      arguments[i].a = a;
      arguments[i].n = n;
      arguments[i].p = p;
      arguments[i].g = i;
      arguments[i].m = &m;
      arguments[i].b = &b;
      arguments[i].s = s;
      arguments[i].c = c;
      arguments[i].is = is;
    }

  t = get_time ();

  for (i = 1; i < p; i++)
    {

      ret = pthread_create (&stub, nullptr, thread_func, arguments + i);

      if (ret != 0)
        {
          perror ("pthread_create");
          abort ();
        }

    }

  thread_func (arguments + 0);

  t = get_time () - t;

  pthread_mutex_destroy (&m);
  pthread_barrier_destroy (&b);

  printf ("Total astro time: %6.2f sec\n", t);
  fflush (stdout);

  delete [] arguments;
  delete [] a;
  delete [] s;
  delete [] c;
  delete [] is;

  return SUCESS;

}
