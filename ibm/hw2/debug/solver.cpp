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


  //  for (k = matrix_size - 1; k >= 0; k--)
  //    {
  //      Ak = A + k;
  //      temp = Ak[k * matrix_size];
  //      B[k] /= temp;
  //      for (j = 0; j < k; j++)
  //        {
  //          temp = Ak[j * matrix_size];
  //          B[j] -= B[k] * temp;
  //        }
  //    }

  memcpy (X, B, matrix_size * sizeof (double));
  return 0;
}

void get_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      memcpy (Block_i, Ai, block_n_size * sizeof (double));
      //            for (int j = 0; j < block_n_size; j++)
      //              Block_i[j] = Ai[j];
      Ai += matrix_size;
      Block_i += block_size;
    }
}


void set_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      memcpy (Ai, Block_i, block_n_size * sizeof (double));
      //            for (int j = 0; j < block_n_size; j++)
      //              Ai[j] = Block_i[j];
      Ai += matrix_size;
      Block_i += block_size;
    }
}

void get_block_vector (double *B, double *Block, int block_size,
                       int i_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  double *Bi = B + i_ * block_size;

  for (int i = 0; i < block_m_size; i++)
    Block[block_size * i] = Bi[i];
}


void set_block_vector (double *B, double *Block,int block_size,
                       int i_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  double *Bi = B + i_ * block_size;

  for (int i = 0; i < block_m_size; i++)
    Bi[i] = Block[block_size * i];
}

int diagonalize_block (double *A, int matrix_size, int block_size, double *T, double eps)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  double Aik;
  int i, j, k;

  memset (T, 0, matrix_size * matrix_size * sizeof (double));

  for (k = 0; k < block_size - 1; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k] * Ak[k];

      for (i = k + 1; i < block_size; i++)
        {
          Ai = A + i * matrix_size;
          Aik = Ai[k];

          temp += Aik * Aik;
          root = sqrt (temp);

          if (root < eps)
            {
              T[i + k * matrix_size] = 1;
              T[k + i * matrix_size] = 1;

              continue;
            }

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

      if (Ak[k] < eps)
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
  int i, k;

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
//          cos_ = T[k + i * matrix_size];
//          sin_ = T[matrix_size * matrix_size + k + i * matrix_size];
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

  memset (T, 0, 2 * matrix_size_squared * sizeof (double));

  for (k = 0; k < n_block_size; k++)
    {
      Ak = A + k * matrix_size;
      temp = Ak[k] * Ak[k];

      for (i = 0; i < m_block_size; i++)
        {
          Bi = B + i * matrix_size;
          Bik = Bi[k];

          temp += Bik * Bik;
          root = sqrt (temp);

          if (root < eps)
            {
              //              T[k + i * matrix_size] = 1;
              //              T[matrix_size_squared + k + i * matrix_size] = 1;
              T[i + k * matrix_size] = 1;
              T[matrix_size_squared + i + k * matrix_size] = 0;
              continue;
            }

          cos_ = Ak[k] / root;
          sin_ = - Bik / root;

          //          T[k + i * matrix_size] = cos_;
          //          T[matrix_size_squared  + k + i * matrix_size] = sin_;
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

          Bi[k] = 0;
        }
    }
}

void traverse_block_zeroing (double *A, double *B, int matrix_size, int m_block_size, int n_block_size, double *T)
{
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Bi;
  int i, j, k;
  int matrix_size_squared = matrix_size * matrix_size;
  int k_matrix_size = 0;

  for (k = 0; k < matrix_size; k++)
    {
      Ak = A + k * matrix_size;
      k_matrix_size = k * matrix_size;

      for (i = 0; i < m_block_size; i++)
        {
          Bi = B + i * matrix_size;

          //          cos_ = T[k + i * matrix_size];
          //          sin_ = T[matrix_size_squared + k + i * matrix_size];
          cos_ = T[i + k_matrix_size];
          sin_ = T[matrix_size_squared + i + k_matrix_size];

//          if ((cos_ == 1) && (sin_ == 0))
//            continue;

          for (j = 0; j < n_block_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Bi[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Bi[j] = buff_1 * sin_ + buff_2 * cos_;
            }
        }
    }
}

int solve_optimized (int matrix_size, double *A, double *B, double *X,
                     int block_size, double *block_1, double *block_2, double *block_3)
{

  int block_quantity_dev = matrix_size / block_size;
  int block_quantity_reminder = matrix_size % block_size;

  int i, j, k;

  double *Ai = NULL;
  double eps = EPS;
  double norm = 0;
  double temp = 0;
  for (i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      temp = 0;
      for (j = 0; j < matrix_size; j++)
        temp += fabs (Ai[j]);

      norm = ((norm > temp) ? norm : temp);
    }
  eps *= norm;

  for (i = 0; i < block_quantity_dev; i++)
    {
      if (block_size != 1)
        {
          get_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);

          if(diagonalize_block(block_1, block_size, block_size, block_2, eps) < 0)
            return INCONSISTENT_SYSTEM;

          set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);

          for (j = i + 1; j < block_quantity_dev; j++)
            {
              get_block (A, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
              traverse_block (block_1, block_size, block_size , block_2);
              set_block (A, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0)
            {
              get_block (A, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
              traverse_block (block_1, block_size, block_quantity_reminder, block_2);
              set_block (A, matrix_size, block_1, block_size, i, j, block_quantity_dev, block_quantity_reminder);
            }

          get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          traverse_vector (block_1, block_size, block_size, block_2);
          set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
        }

      for (j = i + 1; j < block_quantity_dev; j++)
        {
          get_block (A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          get_block (A, matrix_size, block_2, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_1, block_2, block_size, block_size, block_size, block_3, eps);

          set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          set_block(A, matrix_size, block_2, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          for (k = i + 1; k < block_quantity_dev; k++)
            {

              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_2, block_size, block_size, block_size, block_3);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0)
            {
              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_2, block_size, block_size, block_quantity_reminder, block_3);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          get_block_vector (B, block_2, block_size, j, block_quantity_dev, block_quantity_reminder);

          traverse_vector_zeroing (block_1, block_2, block_size, block_size, block_3);

          set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          set_block_vector (B, block_2, block_size, j, block_quantity_dev, block_quantity_reminder);
        }

      if (block_quantity_reminder != 0)
        {

          get_block (A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          get_block (A, matrix_size, block_2, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_1, block_2, block_size, block_quantity_reminder, block_size, block_3, eps);

          set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          set_block(A, matrix_size, block_2, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          for (k = i + 1; k < block_quantity_dev; k++)
            {

              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_2, block_size, block_quantity_reminder, block_size, block_3);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0)
            {
              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_2, block_size, block_quantity_reminder, block_quantity_reminder, block_3);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_2, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          get_block_vector (B, block_2, block_size, j, block_quantity_dev, block_quantity_reminder);

          traverse_vector_zeroing (block_1, block_2, block_size, block_quantity_reminder, block_3);

          set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          set_block_vector (B, block_2, block_size, j, block_quantity_dev, block_quantity_reminder);
        }
    }
  if (block_quantity_reminder != 0)
    {
      get_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);

      if(diagonalize_block(block_1, block_size, block_quantity_reminder, block_2, eps) < 0)
        return INCONSISTENT_SYSTEM;

      set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);

      get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
      traverse_vector (block_1, block_size, block_quantity_reminder, block_2);
      set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
    }

  double *Ak;
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