#include "constants.h"
#include "data_bus.h"
#include "thread_functions.h"
#include "solver.h"
#include "matrix.h"

//-lm -mfpmath=sse -fsignaling-nans -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

int CRUTCH = 0;
int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  //  cpu_set_t cpu;
  //  CPU_ZERO (&cpu);
  //  CPU_SET (get_nprocs() - 1, &cpu);

  //  sched_setaffinity (getpid(), sizeof (cpu), &cpu);

  if (argc != 6 && argc != 7)
    {
      printf ("[ERROR] Please, use: %s Matrix_size Block_size Thread_quantity "
              "Print_size Formula_type (File_name)\n", argv[0]);
      return -1;
    }

  int matrix_size = atoi (argv[1]);
  int block_size = atoi (argv[2]);
  int thread_quantity = atoi (argv[3]);
  int print_size = atoi (argv[4]);
  if (matrix_size <= 0 || block_size <= 0 || thread_quantity <= 0 || print_size <= 0)
    {
      printf ("[ERROR] Matrix_size, Block_size and Print_size should be a positive integer.\n");
      return -1;
    }

  int formula_type = atoi (argv[5]);
  if (argc == 6 && ((formula_type == 0 && strcmp (argv[5], "0") != 0)
                    || (formula_type > 4 || formula_type < 0)))
    {
      printf ("[ERROR] Formula_type should be an integer in [0;4].\n");
      return -1;
    }
  if (argc == 6 && formula_type == 0)
    {
      printf ("[ERROR] Formula_type should be an integer in [0;4], "
              "it can be equals to 0 iff File_name argument is empty.\n");
      return -1;
    }

  char *file_name = nullptr;
  if (argc == 7)
    {
      file_name = argv[6];
      if (formula_type != 0)
        {
          printf ("[ERROR] Formula_type should be equals to 0 if File_name argument isn't empty.\n");
          return -1;
        }
    }

  if (thread_quantity > (matrix_size + block_size - 1) / block_size)
    thread_quantity = (matrix_size + block_size - 1) / block_size;

  using std::unique_ptr;
  using std::nothrow;

  unique_ptr<double[]> matrix_owner (new(nothrow) double[matrix_size * matrix_size]);
  unique_ptr<double[]> x_owner (new(nothrow) double[matrix_size]);
  unique_ptr<double[]> rhs_owner (new(nothrow) double[matrix_size]);
  unique_ptr<double[]> block_1_owner (new(nothrow) double[2 * block_size * block_size]);
  unique_ptr<double[]> block_2_owner (new(nothrow) double[2 * block_size * block_size]);

  double *matrix = matrix_owner.get();
  double *x = x_owner.get();
  double *rhs = rhs_owner.get();
  double *block_1 = block_1_owner.get();
  double *block_2 = block_2_owner.get();

  if (matrix == nullptr|| x == nullptr || rhs == nullptr || block_1 == nullptr || block_2 == nullptr)
    {
      printf ("[ERROR] Not enough memmory for matrix/answer/rhs!\n");
      return -2;
    }

  static pthread_barrier_t barrier;

  unique_ptr <data_bus []> thread_data_owner (new(nothrow) data_bus[thread_quantity]);
  unique_ptr <int []> thread_status_owner (new(nothrow) int[thread_quantity]);
  unique_ptr <pthread_t []> thread_array_owner (new(nothrow) pthread_t[thread_quantity]);

  data_bus *thread_data = thread_data_owner.get();
  int *thread_status = thread_status_owner.get();
  pthread_t *thread_array = thread_array_owner.get();

  memset (thread_status, 0, sizeof (int) * thread_quantity);

  int ret = pthread_barrier_init (&barrier, nullptr, thread_quantity);
  if (ret != 0)
    {
      printf ("[ERROR]: Can not initialize barrier!\n");
      return -4;
    }

  for (int i = 0; i < thread_quantity; i++)
    {
      thread_data[i].A = matrix;
      thread_data[i].X = x;
      thread_data[i].B = rhs;


      thread_data[i].block_1 = block_1;
      thread_data[i].block_2 = block_2;

      thread_data[i].matrix_size = matrix_size;
      thread_data[i].block_size = block_size;
      thread_data[i].print_size = print_size;


      thread_data[i].file_name = file_name;
      thread_data[i].formula_type = formula_type;

      thread_data[i].thread_quantity = thread_quantity;
      thread_data[i].thread_id = i;
      thread_data[i].barrier = &barrier;
      thread_data[i].status = thread_status;
    }

  for (int i = 1; i < thread_quantity; i++)
    {
      ret = pthread_create (thread_array + i, nullptr, &thread_func, thread_data + i);
      if (ret != 0)
        {
          pthread_barrier_destroy (&barrier);
          printf  ("[ERROR]: Can not create thread %d\n", i);
          return -4;
        }
    }

  thread_func (thread_data);

  for (int i = 0; i < thread_quantity; i++)
    {
      if (thread_status[i] != OK)
        {
          pthread_barrier_destroy (&barrier);
          return error_hadler (thread_status[i], file_name);
        }
    }

  printf ("\n%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d p = %d\n",
          argv[0], thread_data[0].residual, thread_data[0].time_total, formula_type,
      matrix_size, block_size, thread_quantity);

  pthread_barrier_destroy (&barrier);
  return 0;
}
