#include "solver.h"

int CRUTCH = 0;

int main (int argc, char *argv[])
{
  bool is_terminal = isatty (fileno (stdout));
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW|FE_UNDERFLOW);

  cpu_set_t cpu;
  CPU_ZERO (&cpu);
  CPU_SET (get_nprocs() - 1, &cpu);

  sched_setaffinity (getpid(), sizeof (cpu), &cpu);

  if (argc != 5 && argc != 6)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
                "%s Matrix_size Block_size Print_size Formula_type (File_name)\n", argv[0]);
      else
        printf ("[ERROR] Please, use: %s Matrix_size Block_size Print_size Formula_type (File_name)\n", argv[0]);
      return -1;
    }

  int matrix_size = atoi (argv[1]);
  int block_size = atoi (argv[2]);
  int print_size = atoi (argv[3]);
  if (matrix_size == 0 || block_size == 0 || print_size == 0)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mMatrix_size, Block_size and Print_size "
                "should be a positive integer.\n");
      else
        printf ("[ERROR] Matrix_size, Block_size and Print_size should be a positive integer.\n");

      return -1;
    }


  int formula_type = atoi (argv[4]);
  CRUTCH = formula_type;
  if (argc == 5 && ((formula_type == 0 && strcmp (argv[4], "0") != 0)
                    || (formula_type > 4 || formula_type < 0)))
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be an integer in [0;4].\n");
      else
        printf ("[ERROR] Formula_type should be an integer in [0;4].\n");

      return -1;
    }
  if (argc == 5 && formula_type == 0)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be an integer in [0;4], "
                "it can be equals to 0 iff File_name argument is empty.\n");
      else
        printf ("[ERROR] Formula_type should be an integer in [0;4], "
                "it can be equals to 0 iff File_name argument is empty.\n");
      return -1;
    }

  char *file_name = NULL;
  if (argc == 6)
    {
      file_name = argv[5];
      if (formula_type != 0)
        {
          if (is_terminal)
            printf ("\x1b[31m[ERROR] \x1b[0mFormula_type should be equals to 0"
                    " if File_name argument isn't empty.\n");
          else
            printf ("[ERROR] Formula_type should be equals to 0"
                    " if File_name argument isn't empty.\n");

          return -1;
        }
    }

  double *A = (double*) malloc (matrix_size * matrix_size * sizeof (double));
  if (A == NULL)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for matrix A.\n");
      else
        printf ("[ERROR] Not enough memmory for matrix A.\n");

      return -2;
    }
  double *X = (double*) malloc (matrix_size * sizeof (double));
  if (X == NULL)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for vector X.\n");
      else
        printf ("[ERROR] Not enough memmory for vector X.\n");

      free (A);
      return -2;
    }
  double *B = (double*) malloc (matrix_size * sizeof (double));
  if (B == NULL)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for vector B.\n");
      else
        printf ("[ERROR] Not enough memmory for vector B.\n");

      free (A);
      free (X);
      return -2;
    }

  double *block_1 = (double*) malloc (2 * block_size * block_size * sizeof (double));
  if (block_1 == NULL)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for block_1.\n");
      else
        printf ("[ERROR] Not enough memmory for block_1.\n");

      free (A);
      free (X);
      free (B);
      return -2;
    }
  double *block_2 = (double*) malloc (2 * block_size * block_size * sizeof (double));
  if (block_2 == NULL)
    {
      if (is_terminal)
        printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory for block_2.\n");
      else
        printf ("[ERROR] Not enough memmory for block_2.\n");

      free (A);
      free (X);
      free (B);
      free (block_1);
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
              if (is_terminal)
                printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
              else
                printf ("[ERROR] Can't open %s\n", file_name);

              break;
            case CANNOT_READ_FILE:
              if (is_terminal)
                printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
              else
                printf ("[ERROR] Can't read %s\n", file_name);

              break;
            case INVALID_FILE:
              if (is_terminal)
                printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                        " (only part of the file is read)\n", file_name);
              else
                printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name);
              break;
            default:
              if (is_terminal)
                printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
              else
                printf ("[ERROR] Unknown error\n");
            }
          free (A);
          free (X);
          free (B);
          free (block_1);
          free (block_2);
          return -3;
        }
    }

  init_B (A, B, matrix_size);

  if (is_terminal)
    printf ("\x1b[32m[OUTPUT] \x1b[0mMatrix A:\n");
  else
    printf ("[OUTPUT] Matrix A:\n");
  print (A, matrix_size, matrix_size, print_size);

  if (is_terminal)
    printf ("\x1b[32m[OUTPUT] \x1b[0mVector B:\n");
  else
    printf ("[OUTPUT] Vector B:\n");
  print (B, matrix_size, 1, print_size);

  double elapsed = clock ();
  int ret = solve_optimized (matrix_size, A, B, X, block_size, block_1, block_2);
  elapsed  = (clock () - elapsed) / CLOCKS_PER_SEC;

  //  printf ("\x1b[32m[OUTPUT] \x1b[0mMatrix A:\n");
  //  print (A, matrix_size, matrix_size, print_size);

  if (ret == INCONSISTENT_SYSTEM)
    {
      if (is_terminal)
        {
          printf ("\x1b[31m[ERROR] \x1b[0mInconsistent system\n");
          printf ("\x1b[32m[OUTPUT] \x1b[0mTime: %.4lf\n", elapsed);
        }
      else
        {
          printf ("[ERROR] Inconsistent system\n");
          printf ("[OUTPUT] Time: %.4lf\n", elapsed);
        }
    }
  else
    {
      if (is_terminal)
        printf ("\n\x1b[32m[OUTPUT] \x1b[0mVector X:\n");
      else
        printf ("\n[OUTPUT] Vector X:\n");

      print (X, matrix_size, 1, print_size);
      if(is_terminal)
        printf ("\x1b[32m[OUTPUT] \x1b[0mSolving time: %.8lf\n", elapsed);
      else
        printf ("[OUTPUT] Solving time: %.8lf\n", elapsed);

      if (argc == 5)
        init_A (A, matrix_size, formula_type);
      else if (argc == 6)
        {
          ret = read (A, matrix_size, file_name);
          if (ret < 0)
            {
              switch (ret)
                {
                case CANNOT_OPEN_FILE:
                  if (is_terminal)
                    printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
                  else
                    printf ("[ERROR] Can't open %s\n", file_name);

                  break;
                case CANNOT_READ_FILE:
                  if (is_terminal)
                    printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
                  else
                    printf ("[ERROR] Can't read %s\n", file_name);

                  break;
                case INVALID_FILE:
                  if (is_terminal)
                    printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s (only part of the file is read)\n", file_name);
                  else
                    printf ("[ERROR] Invalid file %s (only part of the file is read)\n", file_name);
                  break;
                default:
                  if (is_terminal)
                    printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
                  else
                    printf ("[ERROR] Unknown error\n");
                }
              free (A);
              free (X);
              free (B);
              free (block_1);
              free (block_2);
              return -3;
            }
        }
      init_B (A, B, matrix_size);

      double time  = clock ();
      double residual = discrepancy_rate_norm_1 (A, X, B, matrix_size);
      time  = (clock () - time) / CLOCKS_PER_SEC;

      if (is_terminal)
        {
          printf ("\x1b[32m[OUTPUT] \x1b[0m||Discrepancy rate||_1 = %10.3e\n", residual);
          printf ("\x1b[32m[OUTPUT] \x1b[0mDiscrepancy rate's calculating time: %.2lf\n", time);
          printf ("\x1b[32m[OUTPUT] \x1b[0m||Error rate||_1 = %10.3e\n", error_rate_norm_1 (X, matrix_size));
        }
      else
        {
          printf ("[OUTPUT] ||Discrepancy rate||_1 = %10.3e\n", residual);
          printf ("[OUTPUT] Discrepancy rate's calculating time: %.2lf\n", time);
          printf ("[OUTPUT] ||Error rate||_1 = %10.3e\n", error_rate_norm_1 (X, matrix_size));
        }

      printf ("%s : residual = %e elapsed = %.2f for s = %d n = %d m = %d\n",
              argv[0], residual, elapsed, formula_type, matrix_size, block_size);
    }

  free (A);
  free (X);
  free (B);
  free (block_1);
  free (block_2);
  return 0;
}
