#include <stdio.h>
#include <pthread.h>


class args
{
public:
  int p = 0;
  int k = 0;

public:
  args () = default;
  ~args () = default;
};

void *thread_function (void *p)
{
  args *a = (args *)p;
  int p_ = a->p;
  int k_ = a->k;

  printf ("Hello from thread %d (out of %d)\n", k_, p_);

  return 0;
}

int main (int argc, char *argv[])
{
  int p, k;
  args *a;
  pthread_t *tids;

  if (argc != 2 || sscanf (argv[1], "%d", &p) != 1 || p <= 0)
    {
      printf ("Usage: %s p\n", argv[0]);
      return 1;
    }

  a = new args [p];
  if (!a)
    {
      printf ("Cannot allocate memmory!\n");
      return 2;
    }
  for (k = 0; k < p; k++)
    {
      a[k].k = k;
      a[k].p = p;
    }

  tids = new pthread_t [p];
  if (!tids)
    {
      printf ("Cannot allocate tids!\n");
      delete [] a;
      return 3;
    }
  for (k = 0; k < p; k++)
    {
      if (pthread_create (tids + k, 0, &thread_function, a + k) != 0)
        {
          printf ("Cannot create thread %d\n", k);
        }
    }
  /* С этого момента есть P + 1 поток: main + P созданных.*/

  for (k = 0; k < p; k++)
    {
      pthread_join (tids[k], 0); // ожидать завершения
    }

  delete [] tids;
  delete [] a;
  return 0;
}
