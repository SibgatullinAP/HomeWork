#include "solve.h"

bool is_changing (double prev, double curr, double next)
{
  double tmp = (prev + next) / 2.0;
  return (curr < tmp);
}

int solve (double *array, int size)
{
  int comm_size = 0;
  MPI_Comm_size (MPI_COMM_WORLD, &comm_size);

  int my_rank = 0;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  int begin = (size * my_rank) / comm_size;
  int end = (size * (my_rank + 1)) / comm_size;

  int loop_begin = (1 > begin) ? 1 : begin;
  int loop_end = (size - 1 < end) ? size - 1 : end;

  double sum = 0.0;
  int count = 0;

  for (int i = loop_begin; i < loop_end; i++)
    if (is_changing (array[i - 1], array[i], array[i + 1]))
      {
        sum += array[i];
        count++;
      }

  double total_sum;
  MPI_Allreduce (&sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  int total_count;
  MPI_Allreduce (&count, &total_count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  double average = (total_count == 0) ? 0 : (total_sum / total_count);

  if (loop_begin < loop_end)
    {
      double prev = array[loop_begin - 1];
      double curr = array[loop_begin];
      double next = array[loop_begin + 1];

      for (int i = loop_begin; i < loop_end; i++)
        {
          next = array[i + 1];
          if (is_changing (prev, curr, next))
            array[i] = average;

          prev = curr;
          curr = next;
        }
    }

  if (my_rank == MAIN_PID)
    {
      for (int i = 1; i < comm_size; i++)
        {
          begin = (size * i) / comm_size;
          end = (size * (i + 1)) / comm_size;
          MPI_Recv (array + begin, end - begin, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
  else
    MPI_Send (array + begin, end - begin, MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);

  return total_count;
}
