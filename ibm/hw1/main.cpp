#include "solver.h"



int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW);

  if (argc != 5 && argc != 6)
    {
      printf ("[ERROR] Please, use: %s Matrix_size Print_size EPS_precision Formula_type (File_name)\n", argv[0]);
      return -1;
    }

  int matrix_size = atoi (argv[1]);
  int print_size = atoi (argv[2]);
  if (matrix_size == 0 ||  print_size == 0)
    {
      printf ("[ERROR] Matrix_size and Print_size should be a positive integer.\n");
      return -1;
    }

  double eps = 0;
  if (sscanf (argv[3], "%lf", &eps) != 1)
    {
      printf ("[ERROR] EPS_precision should be a real number in scientific notation.\n");
      return -1;
    }

  int formula_type = atoi (argv[4]);
  if (argc == 5 && ((formula_type == 0 && strcmp (argv[4], "0") != 0)
                    || (formula_type > 4 || formula_type < 0)))
    {
      printf ("[ERROR] Formula_type should be an integer in [0;4].\n");
      return -1;
    }
  if (argc == 5 && formula_type == 0)
    {
      printf ("[ERROR] Formula_type should be an integer in [0;4], "
              "it can be equals to 0 iff File_name argument is empty.\n");
      return -1;
    }

  char *file_name = nullptr;
  if (argc == 6)
    {
      file_name = argv[5];
      if (formula_type != 0)
        {
          printf ("[ERROR] Formula_type should be equals to 0"
                  " if File_name argument isn't empty.\n");
          return -1;
        }
    }

  using std::unique_ptr;
  using std::nothrow;

  unique_ptr<double[]> matrix_owner (new(nothrow) double[matrix_size * matrix_size]);
  unique_ptr<double[]> eigenvalues_array_owner (new(nothrow) double[matrix_size]);
  unique_ptr<double[]> add_mem_owner (new(nothrow) double[2 * (matrix_size - 1)]);

  double *matrix = matrix_owner.get();
  double *eigenvalues_array = eigenvalues_array_owner.get();
  double *add_mem = add_mem_owner.get();


  if (matrix == nullptr || eigenvalues_array == nullptr ||  add_mem == nullptr)
    {
      printf ("[ERROR] Not enough memmory.\n");
      return -2;
    }

  int ret = 0;

  if (argc == 5)
    init_matrix (matrix, matrix_size, formula_type);
  else if (argc == 6)
    {
      ret = read (matrix, matrix_size, file_name);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("[ERROR] Can't open %s\n", file_name);
              break;
            case CANNOT_READ_FILE:
              printf ("[ERROR] Can't read %s\n", file_name);
              break;
            case INVALID_FILE:
              printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name);
              break;
            default:
              printf ("[ERROR] Unknown error\n");
            }
          return -3;
        }
    }

  printf ("[OUTPUT] Matrix:\n");
  print (matrix, matrix_size, matrix_size, print_size);

  double norm = calc_norm(matrix, matrix_size);
  double t_1, t_2;
  int itteration = find_eigenvalues (matrix, eigenvalues_array, add_mem, matrix_size, eps, norm, &t_1, &t_2, formula_type);

  printf ("\n[OUTPUT] Vector (eigenvalues):\n");
  print (eigenvalues_array, 1, matrix_size, print_size);

  if (argc == 5)
    init_matrix (matrix, matrix_size, formula_type);
  else if (argc == 6)
    {
      ret = read (matrix, matrix_size, file_name);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("[ERROR] Can't open %s\n", file_name);
              break;
            case CANNOT_READ_FILE:
              printf ("[ERROR] Can't read %s\n", file_name);
              break;
            case INVALID_FILE:
              printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name);
              break;
            default:
              printf ("[ERROR] Unknown error\n");
            }
          return -3;
        }
    }

  printf ("%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
          argv[0], residual_1 (matrix, eigenvalues_array, matrix_size) / norm,
      residual_2 (matrix, eigenvalues_array, matrix_size) / norm, itteration, itteration / matrix_size, t_1, t_2);


  return 0;
}
