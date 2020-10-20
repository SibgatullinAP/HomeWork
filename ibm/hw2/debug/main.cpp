#include "solver.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  if (argc != 5 && argc != 6)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s Matrix_size Block_size Print_size Formula_type (File_name)\n", argv[0]);
      return -1;
    }

  int matrix_size = atoi (argv[1]);
  int block_size = atoi (argv[2]);
  int print_size = atoi (argv[3]);
  if (matrix_size == 0 || block_size == 0 || print_size == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mMatrix_size, Block_size and Print_size "
              "should be a positive integer.\n");
      return -1;
    }


  int formula_type = atoi (argv[4]);
  if (argc == 5 && ((formula_type == 0 && strcmp (argv[4], "0") != 0)
                    || (formula_type > 4 || formula_type < 0)))
    {
      printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be an integer in [0;4].\n");
      return -1;
    }
  if (argc == 5 && formula_type == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be an integer in [0;4], "
              "it can be equals to 0 iff File_name argument is empty.\n");
      return -1;
    }

  char *file_name = NULL;
  if (argc == 6)
    {
      file_name = argv[5];
      if (formula_type != 0)
        {
          printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be equals to 0"
                  " if File_name argument isn't empty.\n");
          return -1;
        }
    }

  double *A = (double*) malloc (matrix_size * matrix_size * sizeof (double));
  if (A == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for matrix A.\n");
      return -2;
    }
  double *X = (double*) malloc (matrix_size * sizeof (double));
  if (X == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for vector X.\n");
      free (A);
      return -2;
    }
  double *B = (double*) malloc (matrix_size * sizeof (double));
  if (B == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for vector B.\n");
      free (A);
      free (X);
      return -2;
    }

  double *block_1 = (double*) malloc (block_size * block_size * sizeof (double));
  if (block_1 == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for block_1.\n");
      free (A);
      free (X);
      free (B);
      return -2;
    }
  double *block_2 = (double*) malloc (block_size * block_size * sizeof (double));
  if (block_2 == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for for block_2.\n");
      free (A);
      free (X);
      free (B);
      free (block_1);
      return -2;
    }
  double *block_3 = (double*) malloc (2 * block_size * block_size * sizeof (double));
  if (block_3 == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for for block_3.\n");
      free (A);
      free (X);
      free (B);
      free (block_1);
      free (block_2);
      return -2;
    }

  if (argc == 5)
    init_A (A, matrix_size, formula_type);
  else if (argc == 6)
    {
      int ret = read (A, matrix_size, file_name);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
              break;
            case CANNOT_READ_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
              break;
            case INVALID_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                      " (only part of the file is read)\n", file_name);
              break;
            default:
              printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
            }
          free (A);
          free (X);
          free (B);
          free (block_1);
          free (block_2);
          free (block_3);
          return -3;
        }
    }

  init_B (A, B, matrix_size);

  printf ("\x1b[32m[OUTPUT] \x1b[0mMatrix A:\n");
  print (A, matrix_size, matrix_size, print_size);
  printf ("\x1b[32m[OUTPUT] \x1b[0mVector B:\n");
  print (B, matrix_size, 1, print_size);

  double time = clock ();
  int ret = solve_optimized (matrix_size, A, B, X, block_size, block_1, block_2, block_3);
  time  = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\x1b[32m[OUTPUT] \x1b[0mMatrix A:\n");
  print (A, matrix_size, matrix_size, print_size);

  if (ret == INCONSISTENT_SYSTEM)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mInconsistent system\n");
      printf ("\x1b[32m[OUTPUT] \x1b[0mTime: %.4lf\n", time);
    }
  else
    {
      printf ("\n\x1b[32m[OUTPUT] \x1b[0mVector X:\n");
      print (X, matrix_size, 1, print_size);
      printf ("\x1b[32m[OUTPUT] \x1b[0mSolving time: %.2lf\n", time);

      if (argc == 5)
        init_A (A, matrix_size, formula_type);
      else if (argc == 6)
        {
          int ret = read (A, matrix_size, file_name);
          if (ret < 0)
            {
              switch (ret)
                {
                case CANNOT_OPEN_FILE:
                  printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
                  break;
                case CANNOT_READ_FILE:
                  printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
                  break;
                case INVALID_FILE:
                  printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                          " (only part of the file is read)\n", file_name);
                  break;
                default:
                  printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
                }
              free (A);
              free (X);
              free (B);
              free (block_1);
              free (block_2);
              free (block_3);
              return -3;
            }
        }
      init_B (A, B, matrix_size);

      time  = clock ();
      printf ("\x1b[32m[OUTPUT] \x1b[0m||Discrepancy rate||_1 = %10.3e\n"
              , discrepancy_rate_norm_1 (A, X, B, matrix_size));
      time  = (clock () - time) / CLOCKS_PER_SEC;

      printf ("\x1b[32m[OUTPUT] \x1b[0mDiscrepancy rate"
              " calculating time: %.2lf\n", time);
      printf ("\x1b[32m[OUTPUT] \x1b[0m||Error rate||_1 = %10.3e\n"
              , error_rate_norm_1 (X, matrix_size));
    }

  free (A);
  free (X);
  free (B);
  free (block_1);
  free (block_2);
  free (block_3);
  return 0;
}