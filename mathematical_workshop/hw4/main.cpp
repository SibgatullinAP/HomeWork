#include "constants.h"
#include "thread_func.h"

int main (int argc, const char * argv [])
{
  if (argc != 3 && argc != 4)
    {
      fprintf (stderr, "Use %s thread_qunatity n (filename)\n", argv[0]);
      return -1;
    }

  int ret = 0;
  int thread_quantity = atoi (argv[1]);
  int n = atoi (argv[2]);
  if (n < 1 || thread_quantity < 1)
    {
      printf ("[ERROR] n, thread_quantity should be a postivie integer number!\n");
      return -1;
    }

  if (thread_quantity > n)
    {
      printf ("ATTENTION! thread_quantity more than numbers elements in array,"
              " column numbers will be used as thread_quantity!\n");
      thread_quantity = n;
    }

  Interface *bus = new Interface [thread_quantity];
  if (bus == nullptr)
    {
      printf ("[ERROR] Not enough memmory for bus array!\n");
      return -2;
    }

  double *arr = new double [n];
  if (arr == nullptr)
    {
      printf ("[ERROR] Not enough memmory for array!\n");
      delete [] bus;

      return -2;
    }

  pthread_t *thread_arr = new pthread_t [thread_quantity];
  if (thread_arr == nullptr)
    {
      printf ("[ERROR] Can't initialize thread!\n");
      delete [] bus;
      delete [] arr;

      return -2;
    }

  pthread_barrier_t barrier;
  ret = pthread_barrier_init (&barrier, nullptr, thread_quantity);
  if (ret != 0)
    {
      printf ("[ERROR] Internal error!");
      delete [] bus;
      delete [] arr;

      return -2;
    }

  if (argc == 3)
    init_array (arr, n);
  else
    {
      int ret = read_array (arr, n, argv [3]);
      if (ret < 0)
        {
          switch (ret)
            {
            case CAN_NOT_OPEN:
              printf ("[ERROR] Can't open %s \n", argv[3]);
              break;

            case CAN_NOT_READ:
              printf ("[ERROR] Can't read %s \n", argv[3]);
              break;

            default:
              printf ("[ERROR] Unknown error\n");
            }

          delete [] bus;
          delete [] arr;
          delete [] thread_arr;

          return -3;
        }
    }

  for (int i = 0; i < thread_quantity; i++)
    {
      bus[i].barrier = &barrier;
      bus[i].array = arr;
      bus[i].n = n;
      bus[i].thread_quantity = thread_quantity;
      bus[i].curr_thread = i;
      bus[i].answer = 0;
      memset (bus[i].add_mem, 0, 6 * sizeof (double));
    }

  printf ("Array before function:\n");
  print_array (arr, n);

  double time = get_time ();
  for (int i = 1; i < thread_quantity; i++)
    {
      ret = pthread_create (thread_arr + i, nullptr, &thread_func, bus + i);
      if (ret != 0)
        {
          printf ("[ERROR] Can't initialize thread!\n");
          delete [] bus;
          delete [] arr;
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

  printf ("\nArray after function:\n");
  print_array (arr, n);

  printf ("\n");
  for (int i = 0; i < thread_quantity; i++)
    printf ("Time of %d-th thread: %lf\n", i, bus[i].time);

  printf ("\nTotal time: %6.2f sec\n", time);
  printf ("Answer: %6.2f\n", answer);

  pthread_barrier_destroy (&barrier);

  delete [] bus;
  delete [] arr;
  delete [] thread_arr;

  return 0;
}
