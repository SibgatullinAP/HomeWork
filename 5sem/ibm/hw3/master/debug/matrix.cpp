#include "matrix.h"
#include "constants.h"

void thread_init_matrix_by_formula (const int thread_id, const int thread_quantity, pthread_barrier_t *barrier,
                         const int matrix_size, const int block_size, double *matrix, const int formula_type)
{
  for (int k = thread_id * block_size; k < matrix_size; k += thread_quantity * block_size)
    {
      for (int i = 0; i < matrix_size; i++)
        for (int j = k; j < matrix_size && j < k + block_size; j++)
          matrix[i * matrix_size + j] = formula (formula_type, matrix_size, i, j);
    }

  pthread_barrier_wait (barrier);
}

void thread_read_matrix (const int thread_id, int *status, pthread_barrier_t *barrier,
                         const int matrix_size, double *matrix, const char *file_name)
{
    if (thread_id == 0)
    status[thread_id] = read (matrix, matrix_size, file_name);

  pthread_barrier_wait (barrier);
}

void thread_init_vector (const int thread_id, pthread_barrier_t *barrier, const int matrix_size, double *matrix, double *vector)
{
  if (thread_id == 0)
    init_rhs (matrix, vector, matrix_size);

  pthread_barrier_wait (barrier);
}

int read (double *matrix, int matrix_size, const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < matrix_size; i++)
    {
      for (int j = 0; j < matrix_size; j++)
        {
          if (fscanf (file, "%lf", matrix + i * matrix_size + j) != 1)
            {
              fclose (file);
              return CANNOT_READ_FILE;
            }
        }
    }

  fclose (file);
  return 0;
}

double formula(int formula_type, int matrix_size, int i, int j)
{
  i += 1;
  j += 1;

  switch (formula_type)
    {
    case 1:
      return (double) matrix_size - (i > j ? i : j) + 1;
    case 2:
      return (double) (i > j ? i : j);
    case 3:
      return fabs (i - j);
    case 4:
      return 1. / (i + j - 1);
    default:
      return 1;
    }
}

void init_matrix (double *matrix, int matrix_size, int formula_type)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = matrix + i * matrix_size;
      for (int j = 0; j < matrix_size; j++)
        Ai[j] = formula(formula_type, matrix_size, i, j);
    }
}

void init_rhs (double *matrix, double *rhs, int matrix_size)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = matrix + i * matrix_size;
      double sum = 0;
      for (int j = 0; j < matrix_size; j += 2)
        sum += Ai[j];

      rhs[i] = sum;
    }
}

void print (const double *matrix, int matrix_size_m, int matrix_size_n, int print_size)
{
  int m = (matrix_size_m > print_size ? print_size : matrix_size_m);
  int n = (matrix_size_n > print_size ? print_size : matrix_size_n);

  for (int i = 0; i < m; i++)
    {
      const double *Ai = matrix + i * matrix_size_n;
      for (int j = 0; j < n; j++)
        printf (" %10.3e", Ai[j]);

      printf ("\n");
    }
}


int error_hadler (int error_code, const char *object_name)
{
  switch (error_code)
    {
    case CANNOT_OPEN_FILE:
      printf ("[ERROR] Can't open %s\n", object_name);
      break;
    case CANNOT_READ_FILE:
      printf ("[ERROR] Can't read %s\n", object_name);
      break;
    case INVALID_FILE:
      printf ("[ERROR] Invalid file %s (only part of the file is read)\n", object_name);
      break;
    case INCONSISTENT_SYSTEM:
      printf ("[ERROR] Inconsistent system\n");
      break;
    default:
      printf ("[ERROR] Unknown error\n");
    }

  return -3;
}
