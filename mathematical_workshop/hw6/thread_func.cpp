#include "thread_func.h"

void *thread_func (void *arg)
{
  double time = get_cpu_time ();

  Interface *bus = (Interface *) arg;

  pthread_barrier_t *barrier = bus->barrier;
  double *matr = bus->matrix;
  double *min = bus->min;
  double *add_mem = bus->additional_memmory;
  int m = bus->m;
  int n = bus->n;
  int thread_quantity = bus->thread_quantity;
  int curr_thread = bus->curr_thread;

  int l = (n * curr_thread) / thread_quantity;
  int r = (n * (curr_thread + 1)) / thread_quantity;

  for (int i = l; i < r; i++)
    min[i] = find_min (matr, m, n, i);

  get_column_buff (matr, m, n, l, r, add_mem);
  pthread_barrier_wait (barrier);

  bus->answer = change_columns (matr, m, n, add_mem, min, l, r);
  pthread_barrier_wait (barrier);

  time = get_cpu_time () - time;
  bus->time = time;

  pthread_barrier_wait (barrier);
  return nullptr;
}

double f (int i, int j)
{
  j++;
  i++;
  return fabs ((double) i - (double) j);
}

void init_matrix (double *matr, int m, int n)
{
  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        matr[i * n + j] = f (i,j);
    }
}

int read_matrix (double *matr, int m, int n, const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == nullptr)
    return CAN_NOT_OPEN;

  for (int i = 0; i < n * m; i++)
    {
      if (fscanf (file, "%lf", matr + i) != 1)
        return CAN_NOT_READ;
    }

  fclose (file);

  return 0;
}

void print_matrix (double *matr, int m, int n)
{
  int m_max = (m > MAX_PRINT ? MAX_PRINT : m);
  int n_max = (n > MAX_PRINT ? MAX_PRINT : n);

  for (int i = 0; i < m_max; i++)
    {
      for (int j = 0; j < n_max; j++)
        printf ("%-10lf ", matr[i * n + j]);

      printf ("\n");
    }
}
