#include "common.hpp"
#include "thread_func.hpp"

int
main (int argc, const char * argv [])
{
  Argument * arguments;
  pthread_t stub;
  pthread_barrier_t b;
  size_t * a;
  double t;
  int res;
  int n, p;
  int ret;
  int i;

  if (argc != 3)
    {
      fprintf (stderr, "Use %s n p\n", argv[0]);
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
  a = new size_t [p];

#define DELETE_ARRAY(ptr) if (ptr != nullptr) { delete [] ptr; }

  if (arguments == nullptr || a == nullptr)
    {
      perror ("Can not allocate memory");
      DELETE_ARRAY (arguments);
      DELETE_ARRAY (a);
      return -1;
    }

#undef DELETE_ARRAY

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
      arguments[i].r = &res;
      arguments[i].b = &b;
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

  pthread_barrier_destroy (&b);

  printf ("\n");
  printf ("Result:     %3d\n", res);
  printf ("Astro time (sec): %6.2f\n", t);

  printf("CPU time (sec):");

  for (i = 0; i < p; i++)
    {
      printf (" %6.2f (#%3d)", arguments[i].cpu_time, i);
    }

  printf ("\n");

  delete [] arguments;
  delete [] a;

  return SUCESS;

}
