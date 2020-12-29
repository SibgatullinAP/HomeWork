#include "solver.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW);

  if (argc != 3 && argc != 4 && argc != 5)
    {
      printf ("[ERROR] Please, use: %s M-th_element Matrix_size (File_name_matrix) (File_name_X_0)\n", argv[0]);
      return -1;
    }

  int m_th = 0;
  if (sscanf (argv[1], "%d", &m_th) != 1 || m_th < 0)
    {
      printf ("[ERROR] M-th_element should be a non-negative integer!\n");
      return -1;
    }

  int matrix_size = 0;
  if (sscanf (argv[2], "%d", &matrix_size) != 1 || matrix_size < 0)
    {
      printf ("[ERROR] Matrix_size should be a positive integer!\n");
      return -1;
    }

  char *file_name_A = nullptr;
  char *file_name_X_0 = nullptr;

  if (argc >= 4)
    file_name_A = argv[3];

  if (argc == 5)
    file_name_X_0 = argv[4];

  double *matrix_A = new double [matrix_size * matrix_size];
  if (matrix_A == nullptr)
    {
      printf ("[ERROR] Not enough memmory for Matrix!\n");
      return -2;
    }

  double *X = new double [matrix_size];
  if (X == nullptr)
    {
      delete [] matrix_A;
      printf ("[ERROR] Not enough memmory for Vector X!\n");
      return -2;
    }

  double *X_0 = new double [matrix_size];
  if (X == nullptr)
    {
      delete [] matrix_A;
      delete [] X;
      printf ("[ERROR] Not enough memmory for Vector X!\n");
      return -2;
    }

  int ret = 0;
  if (file_name_A)
    {
      ret = read (matrix_A, matrix_size, matrix_size, file_name_A);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("[ERROR] Can't open %s\n", file_name_A);
              break;
            case CANNOT_READ_FILE:
              printf ("[ERROR] Can't read %s\n", file_name_A);
              break;
            case INVALID_FILE:
              printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name_A);
              break;
            default:
              printf ("[ERROR] Unknown error\n");
            }

          delete [] matrix_A;
          delete [] X;
          delete [] X_0;

          return -3;
        }
    }
  else
    init_A (matrix_A, matrix_size);

  if (file_name_X_0)
    {
      ret = read (X_0, matrix_size, 1, file_name_X_0);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("[ERROR] Can't open %s\n", file_name_X_0);
              break;
            case CANNOT_READ_FILE:
              printf ("[ERROR] Can't read %s\n", file_name_X_0);
              break;
            case INVALID_FILE:
              printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name_X_0);
              break;
            default:
              printf ("[ERROR] Unknown error\n");
            }

          delete [] matrix_A;
          delete [] X;
          delete [] X_0;

          return -3;
        }
    }
  else
    init_X0 (X_0, matrix_size);

  printf("[OUTPUT] Matrix A:\n");
  print (matrix_A, matrix_size, matrix_size, MAX_PRINT);

  printf("[OUTPUT] Vector X_0:\n");
  print (X_0, matrix_size, 1, MAX_PRINT);

  double time = clock ();
  double answer = solve_1 (matrix_A, X, X_0, matrix_size, m_th);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf("[OUTPUT] Vector X_m:\n");
  print (X, matrix_size, 1, MAX_PRINT);
  printf ("[OUTPUT] Answer: %10.3e\n", answer);
  printf ("[OUTPUT] Elapsed: %10.3e\n", time);

  delete [] matrix_A;
  delete [] X;
  delete [] X_0;

  return 0;
}
