#include "constants.h"
#include "matrix.h"
#include "arguments.h"
#include "solver.h"

int main (int argc, char *argv[])
{
  arguments args;
  MPI_Init (&argc, &argv);

  double total_time = clock ();

  if (!args.set_all_arguments(argc, argv))
    {
      MPI_Finalize ();
      return 0;
    }

  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  using std::unique_ptr;
  using std::nothrow;

  unique_ptr<double[]> matrix_owner (new(nothrow) double[args.get_memmory_size_for_matrix ()]);
  unique_ptr<double[]> x_owner (new(nothrow) double[args.get_matrix_size ()]);
  unique_ptr<double[]> rhs_owner (new(nothrow) double[args.get_matrix_size ()]);
  unique_ptr<double[]> block_1_owner (new(nothrow) double[2 * args.get_block_size () * args.get_block_size ()]);
  unique_ptr<double[]> block_2_owner (new(nothrow) double[2 * args.get_block_size () * args.get_block_size ()]);
  unique_ptr<double[]> block_column_owner (new(nothrow) double[args.get_block_size () * args.get_matrix_size ()]);

  double *matrix = matrix_owner.get();
  double *x = x_owner.get();
  double *rhs = rhs_owner.get();
  double *block_1 = block_1_owner.get();
  double *block_2 = block_2_owner.get();
  double *block_column = block_column_owner.get();

  if (matrix == nullptr|| x == nullptr || rhs == nullptr || block_1 == nullptr || block_2 == nullptr)
    {
      printf_to_main_process ("[ERROR] Not enough memmory for matrix/answer/rhs!\n");
      MPI_Finalize ();
      return 0;
    }

  if (!args.get_formula_type ())
    {
      int ret = read_matrix_mpi (args, matrix, block_column);
      if (ret != OK)
        {
          error_hadler(ret, args.get_file_name ());

          MPI_Finalize ();
          return 0;
        }
      init_vector_mpi (args, matrix, rhs, block_column);
    }
  else
    {
      init_matrix_mpi (args, matrix);
      init_vector_by_formula (args, rhs);
    }

  printf_to_main_process ("[OUTPUT] Matrix A:\n");
  print_matrix_mpi (args, matrix, block_column);

  printf_to_main_process ("[OUTPUT] Vector B:\n");
  if (args.get_rank () == MAIN_PID)
    print (rhs, args.get_matrix_size (), 1, args.get_print_size (), args.get_print_size ());

  double time = clock ();
  int ret = solve_mpi (args, matrix, x, rhs, block_column, block_1, block_2);
  if (ret != OK)
    {
      error_hadler(ret, args.get_file_name ());
      MPI_Finalize ();
      return 0;
    }
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf_to_main_process ("[OUTPUT] Vector X:\n");
  if (args.get_rank () == MAIN_PID)
    print (x, args.get_matrix_size (), 1, args.get_print_size (), args.get_print_size ());

  if (!args.get_formula_type ())
    {
      int ret = read_matrix_mpi (args, matrix, block_column);
      if (ret != OK)
        {
          error_hadler(ret, args.get_file_name ());

          MPI_Finalize ();
          return 0;
        }
      init_vector_mpi (args, matrix, rhs, block_column);
    }
  else
    {
      init_matrix_mpi (args, matrix);
      init_vector_by_formula (args, rhs);
    }

  double residual = residual_mpi (args, matrix, rhs, x, block_column, block_1);

  total_time = (clock () - time) / CLOCKS_PER_SEC;
  printf_to_main_process ("Total time %lf\n", total_time);


  printf_to_main_process ("\n%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d\n",
                          argv[0], residual, time, args.get_formula_type (), args.get_matrix_size (), args.get_block_size ());

  MPI_Finalize ();
  return 0;
}
