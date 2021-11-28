#include "io.h"
#include "solve.h"

int main (int argc, char *argv[])
{
  MPI_Init (&argc, &argv);

  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  int comm_size = 0;
  MPI_Comm_size (MPI_COMM_WORLD, &comm_size);

  int my_rank = 0;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  if (argc != 2 && argc != 3)
    {
      printf_to_main_process ("[ERROR]: Please, use: mpirun -np %d %s Length (FileName)\n"
                              , comm_size, argv[0]);
      MPI_Finalize ();
      return 0;
    }

  int arr_length = atoi (argv[1]);
  if (arr_length <= 0)
    {
      printf_to_main_process ("[ERROR]: Length should be positive integer!\n");
      MPI_Finalize ();
      return 0;
    }

  using std::nothrow;
  using std::unique_ptr;

  unique_ptr<double []> array_owner (new(nothrow) double [arr_length]);
  double *array_ptr = array_owner.get ();

  if (argc == 3)
    {
      const char *file_name = argv[2];
      int ret = OK;
      if (my_rank == MAIN_PID)
        ret = read_arr (array_ptr, arr_length, file_name);

      MPI_Bcast (&ret, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);
      if (ret != OK)
        {
          error_hadler (ret, file_name);
          MPI_Finalize ();
          return 0;
        }

      MPI_Bcast (array_ptr, arr_length, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
    }
  else
    init_formula (array_ptr, arr_length);

  printf_to_main_process ("Original sequence:\n");
  print_arr (array_ptr, arr_length);

  double time = MPI_Wtime ();
  int answer = solve (array_ptr, arr_length);
  time = MPI_Wtime () - time;

  printf_to_main_process ("Changed sequence:\n");
  print_arr (array_ptr, arr_length);

  printf_to_main_process ("\nNumber of changed elements: %d\n", answer);

  MPI_Barrier (MPI_COMM_WORLD);
  printf ("Time[%d]: %lf\n", my_rank, time);

  MPI_Finalize ();
  return 0;
}
