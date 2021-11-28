#include "common.hpp"
#include "thread_func.hpp"

int
main (int argc, const char * argv [])
{
  Argument * arguments;
  pthread_t stub;
  pthread_barrier_t barrier;
  double * shared_min;
  double * shared_max;
  int * status;
  int * result;
  int p;

  int ret;
  bool need_total;
  int count;

  int i;

  if (argc == 1)
    {
      fprintf (stderr, "Use %s a^1 a^2 ... a^p\n", argv[0]);
      return -1;
    }

  p = argc - 1;

  arguments = new Argument [p];
  shared_min = new double [p];
  shared_max = new double [p];
  status = new int [p];
  result = new int [p];

#define DELETE_ARRAY(ptr) if (ptr != nullptr) { delete [] ptr; }

  if (arguments == nullptr || shared_min == nullptr || shared_max == nullptr
      || status == nullptr || result == nullptr)
    {
      perror ("Can not allocate memory");
      DELETE_ARRAY (arguments);
      DELETE_ARRAY (shared_min);
      DELETE_ARRAY (shared_max);
      DELETE_ARRAY (status);
      DELETE_ARRAY (result);
      return -1;
    }

#undef DELETE_ARRAY

  ret = pthread_barrier_init (&barrier, nullptr, p);

  if (ret != 0)
    {
      perror ("pthread_barrier_init");
      delete [] arguments;
      delete [] shared_min;
      delete [] shared_max;
      delete [] status;
      delete [] result;
      return ERROR_PTHREAD;
    }

  for (i = 0; i < p; i++)
    {
      arguments[i].files = argv + 1;
      arguments[i].shared_min = shared_min;
      arguments[i].shared_max = shared_max;
      arguments[i].status = status;
      arguments[i].result = result;
      arguments[i].p = p;
      arguments[i].g = i;
      arguments[i].barrier = &barrier;
    }

  bzero (shared_min, p * sizeof (double));
  bzero (shared_max, p * sizeof (double));
  bzero (status, p * sizeof (int));
  bzero (result, p * sizeof (int));

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

  pthread_barrier_destroy (&barrier);

  need_total = true;

  for (i = 0; i < p; i++)
    {
      if (status[i] != SUCESS)
        {

          need_total = false;

          if (status[i] == CAN_NOT_OPEN)
            {
              fprintf (stderr, "Can not open file %s\n", argv[i + 1]);
            }
          else if (status[i] == CAN_NOT_READ)
            {
              fprintf (stderr, "Can not read from file %s\n", argv[i + 1]);
            }

        }
    }

  if (need_total)
    {

      count = 0;

      for (i = 0; i < p; i++)
        {
          count += result[i];
        }

      printf ("Total: %d\n", count);

    }

  delete [] arguments;
  delete [] shared_min;
  delete [] shared_max;
  delete [] status;
  delete [] result;

  return SUCESS;

}
