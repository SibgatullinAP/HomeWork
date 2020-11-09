#include "common.hpp"
#include "thread_func.hpp"

int
main (int argc, const char * argv [])
{
  Argument * arguments;
  pthread_t stub;
  pthread_barrier_t barrier;
  double * shm1, * shm2;
  int * file_size;
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
  shm1 = new double [p];
  shm2 = new double [p];
  file_size = new int [p];
  status = new int [p];
  result = new int [p];

#define DELETE_ARRAY(ptr) if (ptr != nullptr) { delete [] ptr; }

  if (arguments == nullptr || shm1 == nullptr || shm2 == nullptr
      || file_size == nullptr || status == nullptr || result == nullptr)
    {
      perror ("Can not allocate memory");
      DELETE_ARRAY (arguments);
      DELETE_ARRAY (shm1);
      DELETE_ARRAY (shm2);
      DELETE_ARRAY (file_size);
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
      delete [] shm1;
      delete [] shm2;
      delete [] file_size;
      delete [] status;
      delete [] result;
      return ERROR_PTHREAD;
    }

  for (i = 0; i < p; i++)
    {
      arguments[i].file = argv[i + 1];
      arguments[i].shm1 = shm1;
      arguments[i].shm2 = shm2;
      arguments[i].file_size = file_size;
      arguments[i].status = status;
      arguments[i].result = result;
      arguments[i].p = p;
      arguments[i].g = i;
      arguments[i].barrier = &barrier;
    }

  bzero (shm1, p * sizeof (double));
  bzero (shm2, p * sizeof (double));
  bzero (file_size, p * sizeof (int));
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
  delete [] shm1;
  delete [] shm2;
  delete [] file_size;
  delete [] status;
  delete [] result;

  return SUCESS;

}
