#include "solver.h"
int read (double *A, int matrix_size, char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < matrix_size; i++)
    {
      for (int j = 0; j < matrix_size; j++)
        {
          if (fscanf (file, "%lf", A + i * matrix_size + j) != 1)
            {
              fclose (file);
              return CANNOT_READ_FILE;
            }
        }
    }

  fclose (file);
  return 0;
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
      return fabs(i - j);
    case 4:
      return 1. / (i + j - 1);
    default:
      return 1;
    }
}

void init_A (double *A, int matrix_size, int formula_type)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = A + i * matrix_size;
      for (int j = 0; j < matrix_size; j++)
        Ai[j] = formula(formula_type, matrix_size, i, j);
    }
}

void init_B (double *A, double *B, int matrix_size)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = A + i * matrix_size;
      double sum = 0;
      for (int j = 0; j < matrix_size; j += 2)
        sum += Ai[j];

      B[i] = sum;
    }
}

void print (double *A, int matrix_size_m, int matrix_size_n, int print_size)
{
  int m = (matrix_size_m > print_size ? print_size : matrix_size_m);
  int n = (matrix_size_n > print_size ? print_size : matrix_size_n);

  for (int i = 0; i < m; i++)
    {
      double *Ai = A + i * matrix_size_n;
      for (int j = 0; j < n; j++)
        printf (" %10.3e", Ai[j]);

      printf ("\n");
    }
}

double error_rate_norm_1 (double *X, int matrix_size)
{
  double sum = 0;
  for (int i = 0; i < matrix_size; i++)
    sum += fabs (X[i] - (i + 1) % 2);

  return sum;
}

double discrepancy_rate_norm_1 (double *A, double *X, double *B, int matrix_size)
{
  double AX_B_norm = 0; // || ||_1 норма вектора AX-B
  double B_norm = 0;
  double Bi = 0;
  double AX_i = 0; //i-тая строчка вектора AX
  double *Ai = A;

  for (int i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      AX_i = 0;

      for (int j = 0; j < matrix_size; j++)
        AX_i += Ai[j] * X[j];

      Bi = B[i];

      B_norm += fabs (Bi);
      AX_B_norm += fabs (AX_i - Bi);
    }
  return AX_B_norm / B_norm;
}

//Неблочный вариант
int solve (int matrix_size, double *A, double *B, double *X,
           int block_size, double *block_1, double *block_2, double *block_3)
{
  (void) block_1;
  (void) block_2;
  (void) block_3;
  (void) block_size;

  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  int i, j, k;

  double eps = EPS;
  double norm = 0;
  for (i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      temp = 0;
      for (j = 0; j < matrix_size; j++)
        temp += fabs (Ai[j]);

      norm = ((norm > temp) ? norm : temp);
    }

  eps *= norm;
  
  for (k = 0; k < matrix_size - 1; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k] * Ak[k];

      for (i = k + 1; i < matrix_size; i++)
        {
          Ai = A + i * matrix_size;

          temp += Ai[k] * Ai[k];
          root = sqrt (temp);

          if (root < eps)
            continue;


          cos_ = Ak[k] / root;
          sin_ = - Ai[k] / root;

          Ak[k] = root;
          for (j = k + 1; j < matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Ai[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Ai[j] = buff_1 * sin_ + buff_2 * cos_;
            }

          buff_1 = B[k];
          buff_2 = B[i];

          B[k] = buff_1 * cos_ - buff_2 * sin_;
          B[i] = buff_1 * sin_ + buff_2 * cos_;

          Ai[k] = 0;
        }

      if (Ak[k] < eps )
        return INCONSISTENT_SYSTEM;

    }

  if (fabs (A[matrix_size * matrix_size - 1]) < eps)
    return INCONSISTENT_SYSTEM;


  for (k = matrix_size - 1; k >= 0; k--)
    {
      Ak = A + k;
      temp = Ak[k * matrix_size];
      B[k] /= temp;
      for (j = 0; j < k; j++)
        {
          temp = Ak[j * matrix_size];
          B[j] -= B[k] * temp;
        }
    }

  memcpy (X, B, matrix_size * sizeof (double));
  return 0;
}

inline void get_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_)
{
  int dev = matrix_size / block_size;
  int rem_of_dev = matrix_size % block_size;
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Block_i[j] = Ai[j];

      Ai += matrix_size;
      Block_i += block_n_size;
    }
}


inline void set_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_)
{
  int dev = matrix_size / block_size;
  int rem_of_dev = matrix_size % block_size;
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Ai[j] = Block_i[j];

      Ai += matrix_size;
      Block_i += block_n_size;
    }
}

inline int diagonalize_block (double *A, int matrix_size, double *T)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  int i, j, k;

  double eps = EPS;
  double norm = 0;
  for (i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      temp = 0;
      for (j = 0; j < matrix_size; j++)
        temp += fabs (Ai[j]);

      norm = ((norm > temp) ? norm : temp);
    }

  eps *= norm;

  for (k = 0; k < matrix_size - 1; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k] * Ak[k];
      T[k + k * matrix_size] = 0;

      for (i = k + 1; i < matrix_size; i++)
        {
          Ai = A + i * matrix_size;

          temp += Ai[k] * Ai[k];
          root = sqrt (temp);

          if (root < eps)
            {
              T[i + k * matrix_size] = 1;
              T[k + i * matrix_size] = 1;

              continue;
            }

          cos_ = Ak[k] / root;
          sin_ = - Ai[k] / root;

          T[i + k * matrix_size] = cos_;
          T[k + i * matrix_size] = sin_;

          Ak[k] = root;
          for (j = k + 1; j < matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Ai[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Ai[j] = buff_1 * sin_ + buff_2 * cos_;
            }

          Ai[k] = 0;
        }

      if (Ak[k] < eps )
        return INCONSISTENT_BLOCK;

    }

  if (fabs (A[matrix_size * matrix_size - 1]) < eps)
    return INCONSISTENT_BLOCK;

  T[matrix_size * matrix_size - 1] = 0;

  return 0;
}

inline void traverse_block (double *A, double *B, int matrix_size, double *T)
{
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Bi;
  int i, j, k;

  for (k = 0; k < matrix_size; k++)
    {
      Ak = A + k * matrix_size;

      for (i = k; i < matrix_size; i++)
        {
          Bi = B + i * matrix_size;

          cos_ = T[i + k * matrix_size];
          sin_ = T[k + i * matrix_size];

          for (j = k; j < matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Bi[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Bi[j] = buff_1 * sin_ + buff_2 * cos_;
            }
        }
    }
}

inline void zeroing_block (double *A, double *B, int matrix_size, double *T)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Bi;
  int i, j, k;
  double eps = 1e-16;

  for (k = 0; k < matrix_size; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k] * Ak[k];

      T[k + k * matrix_size] = 0;

      for (i = k; i < matrix_size; i++)
        {
          Bi = B + i * matrix_size;

          temp += Bi[k] * Bi[k];
          root = sqrt (temp);

          if (root < eps)
            {
              T[i + k * matrix_size] = 1;
              T[k + i * matrix_size] = 1;
              continue;
            }

          cos_ = Ak[k] / root;
          sin_ = - Bi[k] / root;

          T[i + k * matrix_size] = cos_;
          T[k + i * matrix_size] = sin_;

          Ak[k] = root;
          for (j = k; j < matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Bi[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Bi[j] = buff_1 * sin_ + buff_2 * cos_;
            }

          Bi[k] = 0;
        }
    }

  T[matrix_size * matrix_size - 1] = 0;

}

int solve_optimized (int matrix_size, double *A, double *B, double *X,
                     int block_size, double *block_1, double *block_2, double *block_3)
{
  int block_quantity = matrix_size / block_size;
  int i, j, k;

  for (i = 0; i < block_quantity; i++)
    {
      get_block(A, matrix_size, block_1, block_size, i, i);

      if(diagonalize_block(block_1, block_size, block_2) < 0)
        return INCONSISTENT_SYSTEM;

      set_block(A, matrix_size, block_1, block_size, i, i);

      for (j = i + 1; j < block_quantity; j++)
        {
          get_block (A, matrix_size, block_3, block_size, i, j);
          traverse_block (block_3, block_3, block_size, block_2);
          set_block(A, matrix_size, block_3, block_size, i, j);

        }


      for (j = i + 1; j < block_quantity; j++)
        {
          get_block (A, matrix_size, block_1, block_size, i, i);
          get_block (A, matrix_size, block_2, block_size, j, i);

          zeroing_block (block_1, block_2, block_size, block_3);

          set_block(A, matrix_size, block_1, block_size, i, i);
          set_block(A, matrix_size, block_2, block_size, j, i);


          for (k = i + 1; k < block_quantity; k++)
            {
              printf ("\n");
              print(block_3, block_size, block_size, 2);

              get_block (A, matrix_size, block_1, block_size, i, k);
              get_block (A, matrix_size, block_2, block_size, j, k);

              traverse_block (block_1, block_2, block_size, block_3);

              set_block(A, matrix_size, block_1, block_size, i, k);
              set_block(A, matrix_size, block_2, block_size, j, k);
            }
        }
    }

  double *Ak;
  double temp;

  for (k = matrix_size - 1; k >= 0; k--)
    {
      Ak = A + k;
      temp = Ak[k * matrix_size];
      B[k] /= temp;
      for (j = 0; j < k; j++)
        {
          temp = Ak[j * matrix_size];
          B[j] -= B[k] * temp;
        }
    }

  memcpy (X, B, matrix_size * sizeof (double));
  return 0;
}