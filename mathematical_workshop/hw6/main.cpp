#include "constants.h"
#include "thread_func.h"

int main (int argc, const char * argv [])
{
  if (argc != 4 && argc != 5)
    {
      fprintf (stderr, "Use %s thread_qunatity m n (filename)\n", argv[0]);
      return -1;
    }

  int ret = 0;
  int thread_quantity = atoi (argv[1]);
  int m = atoi (argv[2]);
  int n = atoi (argv[3]);
  if (n < 1 || m < 1 || thread_quantity < 1)
    {
      printf ("[ERROR] m, n, thread_quantity should be a postivie integer number!\n");
      return -1;
    }

  if (thread_quantity > n)
    {
      printf ("ATTENTION! thread_quantity more than columns numbers, column numbers will be used as thread_quantity!\n");
      thread_quantity = n;
    }

  Interface *bus = new Interface [thread_quantity];
  if (bus == nullptr)
    {
      printf ("[ERROR] Not enough memmory for bus array!\n");
      return -2;
    }

  double *matr = new double [m * n];
  if (matr == nullptr)
    {
      printf ("[ERROR] Not enough memmory for matrix!\n");
      delete [] bus;

      return -2;
    }

  double *additional_memmory = new double [5 * thread_quantity * m];
  if (additional_memmory == nullptr)
    {
      printf ("[ERROR] Not enough memmory for matrix!\n");
      delete [] bus;
      delete [] matr;

      return -2;
    }

  double *min = new double [n];
  if (additional_memmory == nullptr)
    {
      printf ("[ERROR] Not enough memmory for matrix!\n");
      delete [] bus;
      delete [] matr;
      delete [] additional_memmory;

      return -2;
    }

  pthread_t *thread_arr = new pthread_t [thread_quantity];
  if (thread_arr == nullptr)
    {
      printf ("[ERROR] Can't initialize thread!\n");
      delete [] bus;
      delete [] matr;
      delete [] min;
      delete [] additional_memmory;

      return -2;
    }

  pthread_barrier_t barrier;
  ret = pthread_barrier_init (&barrier, nullptr, thread_quantity);
  if (ret != 0)
    {
      printf ("[ERROR] Internal error!");
      delete [] bus;
      delete [] matr;
      delete [] min;
      delete [] additional_memmory;
      delete [] thread_arr;

      return -2;
    }

  if (argc == 4)
    init_matrix(matr, m, n);
  else
    {
      int ret = read_matrix (matr, m, n, argv [4]);
      if (ret < 0)
        {
          switch (ret)
            {
            case CAN_NOT_OPEN:
              printf ("[ERROR] Can't open %s \n", argv[4]);
              break;

            case CAN_NOT_READ:
              printf ("[ERROR] Can't read %s \n", argv[4]);
              break;

            default:
              printf ("[ERROR] Unknown error\n");
            }

          delete [] bus;
          delete [] matr;
          delete [] min;
          delete [] additional_memmory;
          delete [] thread_arr;

          return -3;
        }
    }

  memset (min, 0, n * sizeof (double));
  memset (additional_memmory, 0, 5 * thread_quantity * m * sizeof (double));

  for (int i = 0; i < thread_quantity; i++)
    {
      bus[i].barrier = &barrier;
      bus[i].matrix = matr;
      bus[i].m = m;
      bus[i].n = n;
      bus[i].thread_quantity = thread_quantity;
      bus[i].curr_thread = i;
      bus[i].answer = 0;
      bus[i].additional_memmory = additional_memmory + 5 * i * m;
      bus[i].min = min;
    }

  printf ("Matrix before function:\n");
  print_matrix (matr, m, n);

  double time = get_time ();
  for (int i = 1; i < thread_quantity; i++)
    {
      ret = pthread_create (thread_arr + i, nullptr, &thread_func, bus + i);
      if (ret != 0)
        {
          printf ("[ERROR] Can't initialize thread!\n");
          delete [] bus;
          delete [] matr;
          delete [] min;
          delete [] additional_memmory;
          delete [] thread_arr;
          return -4;
        }
    }

  thread_func (bus);
  time = get_time () - time;

  for (int i = 1; i < thread_quantity; i++)
    pthread_join (thread_arr[i], 0);

  double answer = 0;
  for (int i = 0; i < thread_quantity; i++)
    answer += bus[i].answer;

  printf ("Matrix after function:\n");
  print_matrix (matr, m, n);

    printf ("\n");
    for (int i = 0; i < thread_quantity; i++)
      printf ("Time of %d-th thread: %lf\n", i, bus[i].time);

  printf ("\nTotal time: %6.2f sec\n", time);
  printf ("Answer: %6.2f\n", answer);

  pthread_barrier_destroy (&barrier);

  delete [] bus;
  delete [] matr;
  delete [] min;
  delete [] additional_memmory;
  delete [] thread_arr;

  return 0;
}
