#include "thread_func.h"

void *thread_func (void *arg)
{
  double time = get_cpu_time ();

  Interface *bus = (Interface *) arg;

  pthread_barrier_t *barrier = bus->barrier;
  double *array = bus->array;
  int n = bus->n;
  double *add_mem = bus->add_mem;
  int thread_quantity = bus->thread_quantity;
  int curr_thread = bus->curr_thread;

  int l = (n * curr_thread) / thread_quantity;
  int r = (n * (curr_thread + 1)) / thread_quantity;

  get_line (array, n, l, r, add_mem);
  pthread_barrier_wait (barrier);

  bus->answer = change_line (array, n, l, r, add_mem);
  pthread_barrier_wait (barrier);

  time = get_cpu_time () - time;
  bus->time = time;

  pthread_barrier_wait (barrier);
  return nullptr;
}


double f (int i)
{
  return (double) i;
}

void init_array (double *array, int n)
{
  for (int i = 0; i < n; i++)
    array[i] = f (i);
}

void print_array (double *array, int n)
{
  int n_max = (n > MAX_PRINT ? MAX_PRINT : n);
  for (int i = 0; i < n_max; i++)
    printf ("Arr[%d] = %lf\n", i, array[i]);
}

int read_array (double *array, int n, const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == nullptr)
    return CAN_NOT_OPEN;

  for (int i = 0; i < n; i++)
    {
      if (fscanf (file, "%lf", array + i) != 1)
        return CAN_NOT_READ;
    }

  fclose (file);

  return 0;
}
