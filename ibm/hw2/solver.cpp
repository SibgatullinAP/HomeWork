#include "solver.h"
#include "constants.h"
#include "matrix.h"
#include "arguments.h"

int solve_mpi (arguments args, double *matrix, double *x, double *rhs, double *block_column, double *block_1, double *block_2)
{
  int block_quantity_dev = args.get_dev ();
  int block_quantity_reminder = args.get_rem ();

  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int comm_size = args.get_comm_size ();

  int dev_n = loc_matrix_width / block_size;
  int rem_n = loc_matrix_width % block_size;
  int dev_m = args.get_dev ();
  int rem_m = args.get_rem ();

  int block_size_squared = block_size * block_size;
  int block_quantity = block_quantity_dev + (block_quantity_reminder > 0);

  using std::unique_ptr;
  using std::nothrow;

  unique_ptr<double []> block_4_owner (new(nothrow) double[block_size_squared]);
  unique_ptr<double []> block_5_owner (new(nothrow) double[block_size_squared]);

  memset (block_column, 0, sizeof (double) * matrix_size * block_size);

  double *block_3 = block_1 + block_size_squared;
  double *block_4 = block_4_owner.get();
  double *block_5 = block_5_owner.get();

  double norm = norm_mpi (args, matrix, block_column);
  double eps = norm * EPS;

  if (args.get_formula_type () == 4)
    eps = 1e-18;

  bool is_my_column = false;
  int ret = OK;

  int i_glob = 0;

  int j_glob = 0;
  int j_loc = 0;

  int k_glob = 0;
  int k_loc = 0;

  for (j_glob = 0; j_glob < dev_m; j_glob++)
    {
      is_my_column = (my_rank == args.get_column_owner (j_glob));
      j_loc = j_glob / comm_size;

      if (is_my_column)
        for (int i_glob = j_glob; i_glob < block_quantity; i_glob++)
          get_block (matrix, matrix_size, loc_matrix_width, block_column + i_glob * block_size_squared,
                     block_size, i_glob, j_loc, dev_m, rem_m, dev_n, rem_n);

      MPI_Bcast (block_column, matrix_size * block_size, MPI_DOUBLE, j_glob % comm_size, MPI_COMM_WORLD);

      if (block_size != 1)
        {
          get_block_from_buff (block_column, matrix_size, block_3, block_size, j_glob, j_glob, dev_m, rem_m);
          ret = diagonalize_block(block_3, block_size, block_size, block_2, eps);
          MPI_Bcast (&ret, 1, MPI_INT, j_glob % comm_size, MPI_COMM_WORLD);
          if (ret != OK)
            return ret;

          set_block_to_buff (block_column, matrix_size, block_3, block_size, j_glob, j_glob, dev_m, rem_m);

          for (k_glob = j_glob + 1; k_glob < dev_m; k_glob++)
            {
              if (my_rank == args.get_column_owner (k_glob))
                {
                  k_loc = k_glob / comm_size;
                  get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                  traverse_block (block_1, block_size, block_size, block_2);
                  set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                }
            }
          if (rem_m != 0 && (my_rank == args.get_column_owner (k_glob)))
            {
              k_loc = k_glob / comm_size;
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              traverse_block (block_1, block_size, rem_m, block_2);
              set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
            }

          get_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
          traverse_vector (block_1, block_size, block_size, block_2);
          set_block_vector (rhs, block_1, block_size, j_glob, block_quantity_dev, block_quantity_reminder);
        }

      for (i_glob = j_glob + 1; i_glob < dev_m; i_glob++)
        {
          get_block_from_buff (block_column, matrix_size, block_4, block_size, j_glob, j_glob, dev_m, rem_m);
          get_block_from_buff (block_column, matrix_size, block_5, block_size, i_glob, j_glob, dev_m, rem_m);

          zeroing_block (block_4, block_5, block_size, block_size, block_size, block_2, eps);

          set_block_to_buff (block_column, matrix_size, block_4, block_size, j_glob, j_glob, dev_m, rem_m);
          set_block_to_buff (block_column, matrix_size, block_5, block_size, i_glob, j_glob, dev_m, rem_m);

          for (k_glob = j_glob + 1; k_glob < dev_m; k_glob++)
            {
              if (my_rank == args.get_column_owner (k_glob))
                {
                  k_loc = k_glob / comm_size;

                  get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                  get_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);

                  traverse_block_zeroing (block_1, block_3, block_size, block_size, block_size, block_2, block_size_squared);

                  set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                  set_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                }
            }
          if (rem_m != 0 && (my_rank == args.get_column_owner (k_glob)))
            {
              k_loc = k_glob / comm_size;

              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              get_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);

              traverse_block_zeroing (block_1, block_3, block_size, block_size, rem_m, block_2, block_size_squared);

              set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              set_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
            }

          get_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
          get_block_vector (rhs, block_3, block_size, i_glob, dev_m, rem_m);

          traverse_vector_zeroing (block_1, block_3, block_size, block_size, block_2);

          set_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
          set_block_vector (rhs, block_3, block_size, i_glob, dev_m, rem_m);
        }
      if (block_quantity_reminder != 0)
        {
          get_block_from_buff (block_column, matrix_size, block_4, block_size, j_glob, j_glob, dev_m, rem_m);
          get_block_from_buff (block_column, matrix_size, block_5, block_size, i_glob, j_glob, dev_m, rem_m);

          zeroing_block (block_4, block_5, block_size, rem_m, block_size, block_2, eps);

          set_block_to_buff (block_column, matrix_size, block_4, block_size, j_glob, j_glob, dev_m, rem_m);
          set_block_to_buff (block_column, matrix_size, block_5, block_size, i_glob, j_glob, dev_m, rem_m);

          for (k_glob = j_glob + 1; k_glob < dev_m; k_glob++)
            {
              if (my_rank == args.get_column_owner (k_glob))
                {
                  k_loc = k_glob / comm_size;

                  get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                  get_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);

                  traverse_block_zeroing (block_1, block_3, block_size, block_quantity_reminder, block_size, block_2, block_size_squared);

                  set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                  set_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
                }
            }
          if (rem_m != 0 && (my_rank == args.get_column_owner (k_glob)))
            {
              k_loc = k_glob / comm_size;

              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              get_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);

              traverse_block_zeroing (block_1, block_3, block_size, rem_m, rem_m, block_2, block_size_squared);

              set_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, j_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              set_block (matrix, matrix_size, loc_matrix_width, block_3, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
            }

          get_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
          get_block_vector (rhs, block_3, block_size, i_glob, dev_m, rem_m);

          traverse_vector_zeroing (block_1, block_3, block_size, rem_m, block_2);

          set_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
          set_block_vector (rhs, block_3, block_size, i_glob, dev_m, rem_m);
        }

      if (is_my_column)
        for (int i_glob = j_glob; i_glob < block_quantity; i_glob++)
          set_block (matrix, matrix_size, loc_matrix_width, block_column + i_glob * block_size_squared,
                     block_size, i_glob, j_loc, dev_m, rem_m, dev_n, rem_n);

      if ((block_size == 1) && is_my_column && (fabs (matrix[j_loc + j_glob * loc_matrix_width]) < eps))
        ret = INCONSISTENT_BLOCK;

      MPI_Bcast (&ret, 1, MPI_INT, j_glob % comm_size, MPI_COMM_WORLD);
      if (ret != OK)
        return ret;
    }

  if (rem_m != 0)
    {
      is_my_column = (my_rank == args.get_column_owner (j_glob));
      j_loc = j_glob / comm_size;

      if (is_my_column)
        get_block (matrix, matrix_size, loc_matrix_width, block_column,
                   block_size, j_glob, j_loc, dev_m, rem_m, dev_n, rem_n);

      MPI_Bcast (block_column, block_size * block_size, MPI_DOUBLE, j_glob % comm_size, MPI_COMM_WORLD);

      get_block_from_buff (block_column, matrix_size, block_3, block_size, 0, 0, dev_m, rem_m);
      ret = diagonalize_block(block_3, block_size, rem_m, block_2, eps);
      MPI_Bcast (&ret, 1, MPI_INT, j_glob % comm_size, MPI_COMM_WORLD);
      if (ret != OK)
        return ret;

      set_block_to_buff (block_column, matrix_size, block_3, block_size, 0, 0, dev_m, rem_m);
      if (is_my_column)
        set_block (matrix, matrix_size, loc_matrix_width, block_column,
                   block_size, j_glob, j_loc, dev_m, rem_m, dev_n, rem_n);

      get_block_vector (rhs, block_1, block_size, j_glob, dev_m, rem_m);
      traverse_vector (block_1, block_size, rem_m, block_2);
      set_block_vector (rhs, block_1, block_size, j_glob, block_quantity_dev, block_quantity_reminder);
    }

  MPI_Barrier (MPI_COMM_WORLD);
  gaussian_elimination_mpi (args, matrix, rhs, x, block_4, block_5, block_column);

  return 0;
}

void gaussian_elimination_mpi (arguments args, double *matrix, double *rhs,
                               double *x, double *block_1, double *block_2, double *block_column)
{

  int my_rank = args.get_rank ();
  int matrix_size = args.get_matrix_size ();
  int block_size = args.get_block_size ();
  int loc_matrix_width = args.get_matrix_width ();
  int comm_size = args.get_comm_size ();

  int dev_n = loc_matrix_width / block_size;
  int rem_n = loc_matrix_width % block_size;
  int dev_m = args.get_dev ();
  int rem_m = args.get_rem ();

  double *vec_1 = block_column;
  double *rhs_i = nullptr;

  int k_glob = 0;
  int k_loc = 0;

  int i_glob = 0;

  bool is_my_column = false;

  if (rem_m != 0)
    {
      k_glob = dev_m;
      rhs_i = rhs + block_size * k_glob;
      is_my_column = (my_rank == args.get_column_owner (k_glob));
      if (is_my_column)
        {
          k_loc = k_glob / comm_size;

          get_block (matrix, matrix_size, loc_matrix_width, block_2, block_size, k_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
          for (int i = 0; i < rem_m; i++)
            for (int j = 0; j < rem_m; j++)
              block_1[i * rem_m + j] = block_2[i * block_size + j];

          invert_block (block_2, rem_m, block_1);
          memset (vec_1, 0, block_size * sizeof (double));
          multiply_matr_to_vec (rem_m, rem_m, rem_m, block_2, rhs_i, vec_1);
          memcpy (rhs_i, vec_1, rem_m * sizeof (double));

          for (i_glob = k_glob - 1; i_glob >= 0; i_glob--)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              memset (vec_1, 0, block_size * sizeof (double));
              multiply_matr_to_vec (block_size, rem_m, block_size, block_1, rhs_i, vec_1);
              subtract_vec_from_vec (rhs + i_glob * block_size,vec_1, rhs + i_glob * block_size, block_size);
            }
        }
    }

  MPI_Bcast (rhs, matrix_size, MPI_DOUBLE, k_glob % comm_size, MPI_COMM_WORLD);

  for (k_glob = dev_m - 1; k_glob >= 0; k_glob--)
    {
      rhs_i = rhs + block_size * k_glob;
      is_my_column = (my_rank == args.get_column_owner (k_glob));
      if (is_my_column)
        {
          k_loc = k_glob / comm_size;

          get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, k_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
          invert_block (block_2, block_size, block_1);

          memset (vec_1, 0, block_size * sizeof (double));
          multiply_matr_to_vec (block_size, block_size, block_size, block_2, rhs_i, vec_1);
          memcpy (rhs_i, vec_1, block_size * sizeof (double));

          for (i_glob = k_glob - 1; i_glob >= 0; i_glob--)
            {
              get_block (matrix, matrix_size, loc_matrix_width, block_1, block_size, i_glob, k_loc, dev_m, rem_m, dev_n, rem_n);
              memset (vec_1, 0, block_size * sizeof (double));
              multiply_matr_to_vec (block_size, block_size, block_size, block_1, rhs_i, vec_1);
              subtract_vec_from_vec (rhs + i_glob * block_size,vec_1, rhs + i_glob * block_size, block_size);
            }
        }

      MPI_Bcast (rhs, matrix_size, MPI_DOUBLE, k_glob % comm_size, MPI_COMM_WORLD);
    }

  if (my_rank == MAIN_PID)
    memcpy (x, rhs, matrix_size * sizeof (double));

  MPI_Bcast (x, matrix_size, MPI_DOUBLE, MAIN_PID, MPI_COMM_WORLD);
  return;
}

void invert_block (double *x, int n, double *a)
{
  int i;
  int j;
  int k;
  double tmp;

  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      x[i * n + j] = (double)(i == j);

  for (i = 0; i < n; ++i)
    {
      if (fabs(a[i * n + i]) < 1e-100)
        continue;

      tmp = 1.0 / a[i * n + i];
      for (j = i; j < n; ++j)
        a[i * n + j] *= tmp;

      for (j = 0; j < n; ++j)
        x[i * n + j] *= tmp;

      for (j = i + 1; j < n; ++j)
        {
          tmp = a[j * n + i];
          for (k = i; k < n; ++k)
            a[j * n + k] -= a[i * n + k] * tmp;

          for (k = 0; k < n; ++k)
            x[j * n + k] -= x[i * n + k] * tmp;
        }
    }

  for (k = 0; k < n; ++k)
    for (i = n - 1; i >= 0; --i)
      {
        tmp = x[i * n + k];
        for (j = i + 1; j < n; ++j)
          tmp -= a[i * n + j] * x[j * n + k];
        x[i * n + k] = tmp;
      }
}





int diagonalize_block (double *A, int matrix_size, int block_size, double *T, double eps)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  double Aik;
  int i, j, k;

  for (k = 0; k < block_size - 1; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k];
      temp *= temp;

      for (i = k + 1; i < block_size; i++)
        {
          Ai = A + i * matrix_size;
          Aik = Ai[k];

          temp += Aik * Aik;
          root = sqrt (temp);

          if (root < eps)
            {
              T[i + k * matrix_size] = 1;
              T[k + i * matrix_size] = 0;
            }
          else
            {
              cos_ = Ak[k] / root;
              sin_ = - Aik / root;

              T[i + k * matrix_size] = cos_;
              T[k + i * matrix_size] = sin_;

              Ak[k] = root;
              for (j = k + 1; j < block_size; j++)
                {
                  buff_1 = Ak[j];
                  buff_2 = Ai[j];

                  Ak[j] = buff_1 * cos_ - buff_2 * sin_;
                  Ai[j] = buff_1 * sin_ + buff_2 * cos_;
                }

              Ai[k] = 0;
            }
        }

      if (fabs(Ak[k]) < eps)
        return INCONSISTENT_BLOCK;
    }

  if (fabs (A[(block_size - 1) * matrix_size + (block_size -1 )]) < eps)
    return INCONSISTENT_BLOCK;

  return 0;
}


void traverse_block (double *A, int m_matrix_size, int n_matrix_size, double *T)
{
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  int i, j, k;

  for (k = 0; k < m_matrix_size - 1; k++)
    {
      Ak = A + k * m_matrix_size;

      for (i = k + 1; i < m_matrix_size; i++)
        {
          Ai = A + i * m_matrix_size;

          cos_ = T[i + k * m_matrix_size];
          sin_ = T[k + i * m_matrix_size];

          for (j = 0; j < n_matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Ai[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Ai[j] = buff_1 * sin_ + buff_2 * cos_;
            }
        }
    }
}

void traverse_vector (double *A, int matrix_size, int block_reminder, double *T)
{
  double buff_1, buff_2, cos_, sin_;
  long int i, k;

  for (k = 0; k < matrix_size - 1; k++)
    {
      for (i = k + 1; i < block_reminder; i++)
        {
          cos_ = T[i + k * matrix_size];
          sin_ = T[k + i * matrix_size];

          buff_1 = A[k * matrix_size];
          buff_2 = A[i * matrix_size];

          A[k * matrix_size] = buff_1 * cos_ - buff_2 * sin_;
          A[i * matrix_size] = buff_1 * sin_ + buff_2 * cos_;
        }
    }
}
void traverse_vector_zeroing (double *A, double *B, int matrix_size, int m_block_size, double *T)
{
  double buff_1, buff_2, cos_, sin_;
  int i, k;

  for (k = 0; k < matrix_size; k++)
    {
      for (i = 0; i < m_block_size; i++)
        {
          cos_ = T[i + k * matrix_size];
          sin_ = T[matrix_size * matrix_size + i + k * matrix_size];

          buff_1 = A[k * matrix_size];
          buff_2 = B[i * matrix_size];

          A[k * matrix_size] = buff_1 * cos_ - buff_2 * sin_;
          B[i * matrix_size] = buff_1 * sin_ + buff_2 * cos_;
        }
    }
}

void zeroing_block (double *A, double *B, int matrix_size, int m_block_size, int n_block_size, double *T, double eps)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Bi;
  double Bik;
  int i, j, k;
  int matrix_size_squared = matrix_size * matrix_size;

  for (k = 0; k < matrix_size; k++)
    {
      Ak = A + k * matrix_size;

      temp = Ak[k];
      temp *= temp;

      for (i = 0; i < m_block_size; i++)
        {
          Bi = B + i * matrix_size;
          Bik = Bi[k];

          temp += Bik * Bik;
          root = sqrt (temp);

          if (root > eps)
            {
              cos_ = Ak[k] / root;
              sin_ = -Bik / root;

              T[i + k * matrix_size] = cos_;
              T[matrix_size_squared  + i + k * matrix_size] = sin_;

              Ak[k] = root;

              for (j = k + 1 ; j < n_block_size; j++)
                {
                  buff_1 = Ak[j];
                  buff_2 = Bi[j];

                  Ak[j] = buff_1 * cos_ - buff_2 * sin_;
                  Bi[j] = buff_1 * sin_ + buff_2 * cos_;
                }

            }
          else
            {
              T[i + k * matrix_size] = 1;
              T[matrix_size_squared + i + k * matrix_size] = 0;
            }

          Bi[k] = 0;
        }
    }
}

void traverse_block_zeroing (double *A, double *B, int matrix_size, int m_block_size, int n_block_size,
                             double *T, int shift)
{
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Bi;
  int i, j, k;
  int k_matrix_size;

  double buff_1_1, buff_1_2;

  for (k = 0; k < matrix_size; k++)
    {
      Ak = A + k * matrix_size;
      k_matrix_size = k * matrix_size;

      for (i = 0; i < m_block_size; i++)
        {
          Bi = B + i * matrix_size;

          cos_ = T[i + k_matrix_size];
          sin_ = T[shift + i + k_matrix_size];

          for (j = 0; j < n_block_size - 1; j += 2)
            {
              buff_1 = Ak[j];
              buff_2 = Bi[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Bi[j] = buff_1 * sin_ + buff_2 * cos_;

              buff_1_1 = Ak[j + 1];
              buff_1_2 = Bi[j + 1];

              Ak[j + 1] = buff_1_1 * cos_ - buff_1_2 * sin_;
              Bi[j + 1] = buff_1_1 * sin_ + buff_1_2 * cos_;
            }

          for (; j < n_block_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Bi[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Bi[j] = buff_1 * sin_ + buff_2 * cos_;
            }
        }
    }
}
