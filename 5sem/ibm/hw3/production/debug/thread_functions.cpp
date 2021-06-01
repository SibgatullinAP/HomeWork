#include "thread_functions.h"
#include "constants.h"
#include "solver.h"
#include "matrix.h"
#include "data_bus.h"

void *thread_func (void *data_common)
{
  data_bus *data = (data_bus*) data_common;

  pthread_barrier_t *barrier = data->barrier;
  const int thread_id = data->thread_id;
  const int thread_quantity = data->thread_quantity;

  int *status = data->status;

  const int matrix_size = data->matrix_size;
  const int block_size = data->block_size;
  const int print_size = data->print_size;

  const char *file_name = data->file_name;
  const int formula_type = data->formula_type;

  double *matrix = data->A;
  double *x = data->X;
  double *rhs = data->B;

  cpu_set_t cpu;
  int nprocs = get_nprocs();
  CPU_ZERO (&cpu);
  CPU_SET ((nprocs - 1 - thread_id) % nprocs, &cpu);
  pthread_setaffinity_np (pthread_self (), sizeof (cpu), &cpu);
  pthread_barrier_wait (barrier);

  thread_memmory_catching_by_initialization (thread_id, thread_quantity, status, barrier,
                                             matrix_size, block_size, matrix, x, rhs);
  thread_init(thread_id, thread_quantity, status, barrier, matrix_size, block_size, matrix, rhs, file_name, formula_type);
  if (status[0] != OK)
    return nullptr;

  thread_print(thread_id, barrier, matrix_size, print_size, matrix, rhs, x);

  data->time_thread = get_cpu_time ();
  data->time_total = get_full_time ();

  thread_solve(thread_id, thread_quantity, status, barrier, matrix_size, block_size, matrix, x, rhs);

  pthread_barrier_wait (barrier);
  for (int i = 0; i < thread_quantity; i++)
    {
      if (status[i] != OK)
        {
          pthread_barrier_wait (barrier);
          return nullptr;
        }
    }

  data->time_thread = get_cpu_time () - data->time_thread;
  data->time_total = get_full_time () - data->time_total;

  thread_print(thread_id, barrier, matrix_size, print_size, matrix, rhs, x);
  thread_init(thread_id, thread_quantity, status, barrier, matrix_size, block_size, matrix, rhs, file_name, formula_type);
  if (status[0] != OK)
    return nullptr;

  thread_residual(thread_id, barrier, matrix_size, matrix, rhs, x, &(data->residual));
  thread_time (thread_id, data->time_thread, data->time_total, barrier);

  pthread_barrier_wait (barrier);
  return nullptr;
}

void thread_memmory_catching_by_initialization (const int thread_id, const int thread_quantity, int *status,
                                                pthread_barrier_t *barrier, const int matrix_size, const int block_size,
                                                double *matrix, double *x, double *rhs)
{
  for (int k = thread_id * block_size; k < matrix_size; k += thread_quantity * block_size)
    {
      for (int i = 0; i < matrix_size; i++)
        for (int j = k; j < matrix_size && j < k + block_size; j++)
          matrix[i * matrix_size + j] = thread_id;

      for (int j = k; j < matrix_size && j < k + block_size; j++)
        {
          rhs[j] = thread_id;
          x[j] = thread_id;
        }
    }

  status[thread_id] = OK;
  pthread_barrier_wait (barrier);
}

void thread_init (const int thread_id, const int thread_quantity, int *status, pthread_barrier_t *barrier,
                  const int matrix_size, const int block_size, double *matrix, double *rhs,
                  const char *file_name, const int formula_type)
{
  if (formula_type != 0)
    thread_init_matrix_by_formula (thread_id, thread_quantity, barrier, matrix_size, block_size, matrix, formula_type);
  else
    thread_read_matrix (thread_id, status, barrier, matrix_size, matrix, file_name);

  thread_init_vector (thread_id, barrier, matrix_size, matrix, rhs);
  pthread_barrier_wait (barrier);
}

void thread_print (const int thread_id, pthread_barrier_t *barrier, const int matrix_size, int print_size,
                   double *matrix, double *rhs, double *x)
{
  if (thread_id == 0)
    {
      printf ("[OUTPUT] Matrix A:\n");
      print (matrix, matrix_size, matrix_size, print_size);

      printf ("[OUTPUT] Vector B:\n");
      print (rhs, matrix_size, 1, print_size);

      printf ("[OUTPUT] Vector X:\n");
      print (x, matrix_size, 1, print_size);
    }

  pthread_barrier_wait (barrier);
}

void thread_time (int thread_id, double time_thread, double time_total, pthread_barrier_t *barrier)
{
  if (thread_id == 0)
    {
      printf ("\nTotal time: %.2f\n", time_total);
      printf ("CPU time:\n");
    }

  pthread_barrier_wait (barrier);
  printf ("Thread_time[%d] = %5.2f\n", thread_id, time_thread);

  pthread_barrier_wait (barrier);
}

void thread_residual (const int thread_id, pthread_barrier_t *barrier,
                      const int matrix_size, double *matrix, double *rhs, double *x, double *residual)
{
  if (thread_id == 0)
    {
      *residual = discrepancy_rate_norm_1 (matrix, x, rhs, matrix_size);
      printf ("[OUTPUT] ||Discrepancy rate||_1 = %10.3e\n", discrepancy_rate_norm_1 (matrix, x, rhs, matrix_size));
      printf ("[OUTPUT] ||Error rate||_1 = %10.3e\n", error_rate_norm_1 (x, matrix_size));
    }

  pthread_barrier_wait (barrier);
}

double get_cpu_time ()
{
  struct rusage tm;
  getrusage (RUSAGE_THREAD, &tm);
  return (double) (tm.ru_utime.tv_sec + tm.ru_utime.tv_usec / 1e6);
}

double get_full_time ()
{
  struct timeval tm;
  gettimeofday (&tm, 0);
  return (double) (tm.tv_sec + tm.tv_usec / 1e6);
}

void thread_solve (const int thread_id, const int thread_quantity, int *status, pthread_barrier_t *barrier,
                   const int matrix_size, const int block_size, double *matrix, double *x, double *rhs)
{
  int block_quantity_dev = matrix_size / block_size;
  int block_quantity_reminder = matrix_size % block_size;

  int j, k;
  int block_size_squared = block_size * block_size;

  using std::unique_ptr;
  using std::nothrow;

  unique_ptr<double []> block_1_owner (new(nothrow) double[2 * block_size_squared]);
  unique_ptr<double []> block_2_owner (new(nothrow) double[2 * block_size_squared]);
  unique_ptr<double []> block_4_owner (new(nothrow) double[block_size_squared]);
  unique_ptr<double []> block_5_owner (new(nothrow) double[block_size_squared]);
  unique_ptr<double []> block_column_owner (new(nothrow) double[matrix_size * block_size]);

  double *block_1 = block_1_owner.get();
  double *block_2 = block_2_owner.get();
  double *block_3 = block_1 + block_size_squared;
  double *block_4 = block_4_owner.get();
  double *block_5 = block_5_owner.get();
  double *block_column = block_column_owner.get();

  double norm = norm_1 (matrix, matrix_size);
  double eps = (1 < norm ? 1 : norm) * EPS;

  pthread_barrier_wait(barrier);

  int shift = (thread_id ? thread_id : thread_quantity);

  int i = 0;
  for (i = 0; i < block_quantity_dev; i++)
    {
      bool is_additional_work = i % thread_quantity == thread_id;
      if (block_size != 1)
        {
          get_block(matrix, matrix_size, block_column, block_size, i, i, block_quantity_dev, block_quantity_reminder);

          if(diagonalize_block(block_column, block_size, block_size, block_2, eps) < 0)
            {
              status[thread_id] = INCONSISTENT_SYSTEM;
              return;
            }

          for (j = i + shift; j < block_quantity_dev; j += thread_quantity)
            {
              get_block (matrix, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
              traverse_block (block_1, block_size, block_size, block_2);
              set_block (matrix, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0 && is_additional_work)
            {
              j = block_quantity_dev;
              get_block (matrix, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
              traverse_block (block_1, block_size, block_quantity_reminder, block_2);
              set_block (matrix, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
            }

          pthread_barrier_wait (barrier);
          if (is_additional_work)
            {
              set_block(matrix, matrix_size, block_column, block_size, i, i, block_quantity_dev, block_quantity_reminder);

              get_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
              traverse_vector (block_1, block_size, block_size, block_2);
              set_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
            }
        }

      pthread_barrier_wait (barrier);
      for (int j = i; j < block_quantity_dev; j++)
        get_block (matrix, matrix_size, block_column + j * block_size_squared,
                   block_size, j, i, block_quantity_dev, block_quantity_reminder);

      for (j = i + 1; j < block_quantity_dev; j++)
        {
          get_block_from_buff (block_column, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          get_block_from_buff (block_column, matrix_size, block_5, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_column + i * block_size_squared, block_column + j * block_size_squared, block_size, block_size, block_size, block_2, eps);
          zeroing_block (block_4, block_5, block_size, block_size, block_size, block_2, eps);

          set_block_to_buff (block_column, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          set_block_to_buff (block_column, matrix_size, block_5, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          for (k = i + shift; k < block_quantity_dev; k += thread_quantity)
            {
              get_block (matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_size, block_size, block_2, block_size_squared);

              set_block(matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0 && is_additional_work)
            {
              k = block_quantity_dev;

              get_block (matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_size, block_quantity_reminder, block_2, block_size_squared);

              set_block(matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          if (is_additional_work)
            {
              get_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
              get_block_vector (rhs, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);

              traverse_vector_zeroing (block_1, block_3, block_size, block_size, block_2);

              set_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
              set_block_vector (rhs, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);
            }
        }

      pthread_barrier_wait (barrier);
      if (is_additional_work)
        for (int j = i; j < block_quantity_dev; j++)
          set_block (matrix, matrix_size, block_column + j * block_size_squared,
                     block_size, j, i, block_quantity_dev, block_quantity_reminder);


      pthread_barrier_wait (barrier);
      if (block_quantity_reminder != 0)
        {
          j = block_quantity_dev;

          get_block (matrix, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          get_block (matrix, matrix_size, block_5, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_4, block_5, block_size, block_quantity_reminder, block_size, block_2, eps);

          for (k = i + shift; k < block_quantity_dev; k += thread_quantity)
            {
              get_block (matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_quantity_reminder, block_size, block_2, block_size_squared);

              set_block(matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0 && is_additional_work)
            {
              k = block_quantity_dev;
              get_block (matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size,
                                      block_quantity_reminder, block_quantity_reminder, block_2, block_size_squared);

              set_block(matrix, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(matrix, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          pthread_barrier_wait (barrier);
          if (is_additional_work)
            {
              set_block(matrix, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);
              set_block(matrix, matrix_size, block_5, block_size, j, i, block_quantity_dev, block_quantity_reminder);

              get_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
              get_block_vector (rhs, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);

              traverse_vector_zeroing (block_1, block_3, block_size, block_quantity_reminder, block_2);

              set_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
              set_block_vector (rhs, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);
            }
        }

      pthread_barrier_wait(barrier);
      if (fabs (matrix[i + i * matrix_size]) < eps)
        {
          status[thread_id] = INCONSISTENT_SYSTEM;
          return;
        }
    }

  if (block_quantity_reminder != 0)
    {
      i = block_quantity_dev;
      get_block(matrix, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);

      if(diagonalize_block(block_4, block_size, block_size, block_2, eps) < 0)
        {
          status[thread_id] = INCONSISTENT_SYSTEM;
          return;
        }

      pthread_barrier_wait(barrier);
      if (i % thread_quantity == thread_id)
        {
          set_block(matrix, matrix_size, block_4, block_size, i, i, block_quantity_dev, block_quantity_reminder);

          get_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          traverse_vector (block_1, block_size, block_quantity_reminder, block_2);
          set_block_vector (rhs, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
        }
    }

  pthread_barrier_wait (barrier);
  if (thread_id == 0)
    {
      double *Ak;
      double temp = 0;
      for (k = matrix_size - 1; k >= 0; k--)
        {
          Ak = matrix + k;
          temp = Ak[k * matrix_size];
          rhs[k] /= temp;
          for (j = 0; j < k; j++)
            {
              temp = Ak[j * matrix_size];
              rhs[j] -= rhs[k] * temp;
            }
        }
      memcpy (x, rhs, matrix_size * sizeof (double));
    }

  pthread_barrier_wait (barrier);
}
