#include "matrix.h"
#include "arguments.h"
#include "constants.h"


void printf_to_main_process (const char *format, ...)
{
  int my_rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  va_list args;
  va_start (args, format);

  if (my_rank == 0)
    vprintf (format, args);

  va_end (args);
}


int read_matrix_mpi (const arguments &args, double *matrix, double *add_mem)
{
  FILE *file = nullptr;
  int ret = OK;
  int my_rank = args.get_rank ();

  if (my_rank == 0)
    {
      file = fopen (args.get_file_name (), "r");
      if (file == nullptr)
        ret = CANNOT_OPEN_FILE;
    }

  MPI_Bcast (&ret, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);
  if (ret != OK)
    return ret;

  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int dev = args.get_dev ();
  int rem = args.get_rem ();
  int comm_size = args.get_comm_size ();

  double *matrix_loc_j = nullptr;
  int shift_k = 0;
  int k = 0;

  for (k = 0; k < dev && ret == OK; k++)
    {
      if (my_rank == 0)
        {
          for (int i = 0; i < block_size; i++)
            {
              for (int j = 0; j < matrix_size; j++)
                {
                  if (fscanf (file, "%lf", add_mem + i * matrix_size + j) != 1)
                    ret = CANNOT_READ_FILE;
                }
            }
        }

      MPI_Bcast (&ret, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (matrix_loc_j + i_loc * loc_matrix_width,
                            add_mem + j_glob * block_size + i_loc * matrix_size, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Recv (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Send (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD);
            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (matrix_loc_j + i_loc * loc_matrix_width,
                            add_mem + j_glob * block_size + i_loc * matrix_size, sizeof (double) * rem);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Recv (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Send (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD);
            }
        }
    }
  if (args.get_rem () != 0 && ret == OK)
    {
      if (my_rank == 0)
        {
          for (int i = 0; i < rem; i++)
            {
              for (int j = 0; j < matrix_size; j++)
                {
                  if (fscanf (file, "%lf", add_mem + i * matrix_size + j) != 1)
                    ret = CANNOT_READ_FILE;
                }
            }
        }

      MPI_Bcast (&ret, 1, MPI_INT, MAIN_PID, MPI_COMM_WORLD);

      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (matrix_loc_j + i_loc * loc_matrix_width,
                            add_mem + j_glob * block_size + i_loc * matrix_size, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Recv (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Send (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD);
            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (matrix_loc_j + i_loc * loc_matrix_width,
                            add_mem + j_glob * block_size + i_loc * matrix_size, sizeof (double) * rem);

                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Recv (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Send (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD);
            }
        }
    }
  return ret;
}

void print_matrix_mpi (const arguments &args, double *matrix, double *add_mem)
{
  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int dev = args.get_dev ();
  int rem = args.get_rem ();
  int comm_size = args.get_comm_size ();

  double *matrix_loc_j = nullptr;
  int shift_k = 0;
  int k = 0;
  int k_glob = 0;

  for (k = 0, k_glob = 0; k < dev && k_glob < args.get_print_size (); k++)
    {
      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * rem);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

      k_glob += block_size;
      int n_print_size = (k < (args.get_print_size () / block_size) ? block_size : args.get_print_size () % block_size);

      if (my_rank == MAIN_PID)
        print (add_mem, block_size, matrix_size, n_print_size, args.get_print_size ());
    }
  if (args.get_rem () != 0 && k_glob < args.get_print_size ())
    {
      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * rem);
                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);

                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

      k_glob += block_size;
      int n_print_size = (k < (args.get_print_size () / block_size) ? block_size : args.get_print_size () % block_size);

      if (my_rank == MAIN_PID)
        print (add_mem, rem, matrix_size, n_print_size, args.get_print_size ());
    }
}

void init_matrix_mpi (arguments args, double *matrix)
{
  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int dev = args.get_dev ();
  int rem = args.get_rem ();
  int comm_size = args.get_comm_size ();

  int k = 0;
  for (k = 0; k < dev; k++)
    {
      if (k % comm_size == my_rank)
        {
          for (int i = 0; i < matrix_size; i++)
            {
              for (int j = 0; j < block_size; j++)
                {
                  matrix[i * loc_matrix_width + k / comm_size * block_size + j]
                      = formula (args.get_formula_type (), matrix_size, i, k * block_size + j);
                }
            }
        }
    }
  if (rem != 0)
    {
      if (k % comm_size == my_rank)
        {
          for (int i = 0; i < matrix_size; i++)
            {
              for (int j = 0; j < rem; j++)
                {
                  matrix[i * loc_matrix_width + k / comm_size * block_size + j]
                      = formula (args.get_formula_type (), matrix_size, i, k * block_size + j);
                }
            }
        }
    }
}

void init_vector_by_formula (arguments args, double *rhs)
{
  for (int i = 0; i < args.get_matrix_size (); i++)
    {
      double sum = 0;
      for (int j = 0; j < args.get_matrix_size (); j += 2)
        sum += formula (args.get_formula_type (), args.get_matrix_size (), i, j);

      rhs[i] = sum;
    }
}

void init_vector_mpi (arguments args, double *matrix, double *rhs, double *add_mem)
{
  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int dev = args.get_dev ();
  int rem = args.get_rem ();
  int comm_size = args.get_comm_size ();

  double *matrix_loc_j = nullptr;
  int shift_k = 0;
  int k = 0;

  for (k = 0; k < dev; k++)
    {
      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * rem);
                }
              else
                {
                  for (int i_loc = 0; i_loc < block_size; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < block_size; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

      if (my_rank == MAIN_PID)
        {
          for (int i = 0; i < block_size; i++)
            {
              double *Ai = add_mem + i * matrix_size;
              double sum = 0;
              for (int j = 0; j < matrix_size; j += 2)
                sum += Ai[j];

              rhs[i + k * block_size] = sum;
            }
        }
    }
  if (args.get_rem () != 0)
    {
      shift_k = k * loc_matrix_width * block_size;
      int column_owner = 0;
      int j_glob = 0;
      for (j_glob = 0; j_glob < dev; j_glob++)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * block_size);
                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, block_size,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, block_size,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
      if (rem != 0)
        {
          column_owner = args.get_column_owner (j_glob);
          int j_loc = j_glob / comm_size;

          matrix_loc_j = matrix + j_loc * block_size + shift_k;

          if (column_owner == my_rank)
            {
              if (column_owner == MAIN_PID)
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    memcpy (add_mem + j_glob * block_size + i_loc * matrix_size,
                            matrix_loc_j + i_loc * loc_matrix_width, sizeof (double) * rem);
                }
              else
                {
                  for (int i_loc = 0; i_loc < rem; i_loc++)
                    MPI_Send (matrix_loc_j + i_loc * loc_matrix_width, rem,
                              MPI_DOUBLE, MAIN_PID, 0, MPI_COMM_WORLD);
                }
            }
          else if (my_rank == MAIN_PID)
            {
              for (int i_loc = 0; i_loc < rem; i_loc++)
                MPI_Recv (add_mem + j_glob * block_size + i_loc * matrix_size, rem,
                          MPI_DOUBLE, column_owner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

      if (my_rank == MAIN_PID)
        {
          for (int i = 0; i < rem; i++)
            {
              double *Ai = add_mem + i * matrix_size;
              double sum = 0;
              for (int j = 0; j < matrix_size; j += 2)
                sum += Ai[j];

              rhs[i + k * block_size] = sum;
            }
        }
    }

  MPI_Bcast (rhs, matrix_size, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
}

double norm_mpi (arguments args, double *matrix, double *block_column)
{
  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int comm_size = args.get_comm_size ();

  double norm = 0;
  for (int j_loc = 0; j_loc < loc_matrix_width; j_loc++)
    {
      double temp = 0;
      double *Aj = matrix + j_loc;
      for (int i = 0; i < matrix_size; i++)
        temp += fabs (Aj[i * loc_matrix_width]);

      norm = (norm > temp ? norm : temp);
    }

  block_column[my_rank] = norm;
  MPI_Bcast (block_column + my_rank, 1, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
  if (my_rank == MAIN_PID)
    {
      for (int id = 0; id < comm_size; id++)
        norm = (norm > block_column[id] ? norm : block_column[id]);
    }

  MPI_Bcast (&norm, 1, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
  return norm;
}

double residual_mpi (arguments args, double *matrix, double *rhs, double *x, double *block_column, double *block_1)
{
  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int dev_n = loc_matrix_width / block_size;
  int rem_n = loc_matrix_width % block_size;
  int dev_m = args.get_dev ();
  int rem_m = args.get_rem ();
  int comm_size = args.get_comm_size ();

  int i_glob_bl;
  int j_glob_bl;
  int j_loc_bl;

  double norm = 0;

  memset (block_column, 0, matrix_size * block_size * sizeof (double));
  double *ans = block_column;

  std::unique_ptr<double[]> block_column_2_owner (new(std::nothrow) double[matrix_size]);
  double *block_column_2 = block_column_2_owner.get ();
  memset (block_column_2, 0, matrix_size * sizeof (double));

  for (i_glob_bl = 0; i_glob_bl < dev_m; i_glob_bl++)
    {
      for (j_glob_bl = 0; j_glob_bl < dev_m; j_glob_bl++)
        {
          j_loc_bl = j_glob_bl / comm_size;
          if (j_glob_bl % comm_size == my_rank)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size,
                         i_glob_bl, j_loc_bl, dev_m, rem_m, dev_n, rem_n);
              multiply_matr_to_vec (block_size, block_size, block_size, block_1,
                                    x + j_glob_bl * block_size, ans + i_glob_bl * block_size);
            }
        }
      if (rem_n != 0)
        {
          j_loc_bl = j_glob_bl / comm_size;
          if (j_glob_bl % comm_size == my_rank)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size,
                         i_glob_bl, j_loc_bl, dev_m, rem_m, dev_n, rem_n);
              multiply_matr_to_vec (block_size, rem_m, block_size, block_1,
                                    x + j_glob_bl * block_size, ans + i_glob_bl * block_size);
            }
        }
    }
  if (rem_m != 0)
    {
      for (j_glob_bl = 0; j_glob_bl < dev_m; j_glob_bl++)
        {
          j_loc_bl = j_glob_bl / comm_size;
          if (j_glob_bl % comm_size == my_rank)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size,
                         i_glob_bl, j_loc_bl, dev_m, rem_m, dev_n, rem_n);
              multiply_matr_to_vec (rem_m, block_size, block_size, block_1,
                                    x + j_glob_bl * block_size, ans + i_glob_bl * block_size);
            }
        }
      if (rem_n != 0)
        {
          j_loc_bl = j_glob_bl / comm_size;
          if (j_glob_bl % comm_size == my_rank)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size,
                         i_glob_bl, j_loc_bl, dev_m, rem_m, dev_n, rem_n);
              multiply_matr_to_vec (rem_m, rem_m, block_size, block_1,
                                    x + j_glob_bl * block_size, ans + i_glob_bl * block_size);
            }
        }
    }

  MPI_Reduce (block_column, block_column_2, matrix_size, MPI_DOUBLE, MPI_SUM, MAIN_PID, MPI_COMM_WORLD);

  if (my_rank == MAIN_PID)
    {
      double b_norm = 0;
      double AX_minus_B_norm = 0;
      for (int i = 0; i < matrix_size; i++)
        {
          b_norm += fabs (rhs[i]);
          block_column_2[i] -= rhs[i];
          AX_minus_B_norm += fabs (block_column_2[i]);
        }

      norm = AX_minus_B_norm / b_norm;
    }

  MPI_Bcast (&norm, 1, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
  return norm;
}

void multiply_matr_to_vec (int m_matrix_size, int n_matrix_size, int shift, double *matr, double *vec, double *ans)
{
  for (int i = 0; i < m_matrix_size; i++)
    {
      double tmp = 0;
      for (int j = 0; j < n_matrix_size; j++)
        tmp += matr[i * shift + j] * vec[j];

      ans[i] += tmp;
    }
}

void subtract_vec_from_vec (double *a, double *b, double *ans, int matrix_size)
{
  for (int i = 0; i < matrix_size; i++)
    ans[i] = a[i] - b[i];
}

void get_block (double *A, int m_matrix_size, int n_matrix_size, double *Block,
                int block_size, int i_, int j_, int dev_m, int rem_m, int dev_n, int rem_n)
{
  (void) m_matrix_size;

  int block_m_size = (i_ < dev_m ? block_size : rem_m);
  int block_n_size = (j_ < dev_n ? block_size : rem_n);

  double *Block_i = Block;
  double *Ai = A + (i_ * n_matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Block_i[j] = Ai[j];

      Ai += n_matrix_size;
      Block_i += block_size;
    }
}


void set_block (double *A, int m_matrix_size, int n_matrix_size, double *Block,
                int block_size, int i_, int j_, int dev_m, int rem_m, int dev_n, int rem_n)
{
  (void) m_matrix_size;

  int block_m_size = (i_ < dev_m ? block_size : rem_m);
  int block_n_size = (j_ < dev_n ? block_size : rem_n);

  double *Block_i = Block;
  double *Ai = A + (i_ * n_matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Ai[j] = Block_i[j];

      Ai += n_matrix_size;
      Block_i += block_size;
    }
}

void get_block_from_buff (double *buff, int matrix_size, double *Block, int block_size,
                          int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  (void) matrix_size;

  double *Block_i = Block;
  double *Ai = buff +  i_ * block_size * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Block_i[j] = Ai[j];

      Ai += block_size;
      Block_i += block_size;
    }
}


void set_block_to_buff (double *buff, int matrix_size, double *Block, int block_size,
                        int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  (void) matrix_size;

  double *Block_i = Block;
  double *Ai = buff +  i_ * block_size * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Ai[j] = Block_i[j];

      Ai += block_size;
      Block_i += block_size;
    }
}

void get_block_vector (double *B, double *Block, int block_size, int i_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  double *Bi = B + i_ * block_size;

  for (int i = 0; i < block_m_size; i++)
    Block[block_size * i] = Bi[i];
}


void set_block_vector (double *B, double *Block,int block_size, int i_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  double *Bi = B + i_ * block_size;

  for (int i = 0; i < block_m_size; i++)
    Bi[i] = Block[block_size * i];
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

void print (const double *matrix, int matrix_size_m, int matrix_size_n, int print_size_m, int print_size_n)
{
  int m = (matrix_size_m > print_size_m ? print_size_m : matrix_size_m);
  int n = (matrix_size_n > print_size_n ? print_size_n : matrix_size_n);

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
      printf_to_main_process ("[ERROR] Can't open %s\n", object_name);
      break;
    case CANNOT_READ_FILE:
      printf_to_main_process ("[ERROR] Can't read %s\n", object_name);
      break;
    case INVALID_FILE:
      printf_to_main_process ("[ERROR] Invalid file %s (only part of the file is read)\n", object_name);
      break;
    case INCONSISTENT_SYSTEM:
      printf_to_main_process ("[ERROR] Inconsistent system\n");
      break;
    case INCONSISTENT_BLOCK:
      printf_to_main_process ("[ERROR] Inconsistent block\n");
      break;
    default:
      printf_to_main_process ("[ERROR] Unknown error\n");
    }

  return 0;
}
