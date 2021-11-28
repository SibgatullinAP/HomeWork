#include "solver.h"
#include "constants.h"
#include "matrix.h"

extern int CRUTCH;

double error_rate_norm_1 (double *X, int matrix_size)
{
  double sum = 0;
  for (int i = 0; i < matrix_size; i++)
    sum += fabs (X[i] - (i + 1) % 2);

  return sum;
}

double discrepancy_rate_norm_1 (double *A, double *X, double *B, int matrix_size)
{
  double AX_B_norm = 0;
  double B_norm = 0;
  double Bi = 0;
  double AX_i = 0;
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

double norm_1 (double *matrix, int matrix_size)
{
  double norm = 0;
  double temp = 0;
  double *Ai = nullptr;
  for (int i = 0; i < matrix_size; i++)
    {
      Ai = matrix + i * matrix_size;
      temp = 0;
      for (int j = 0; j < matrix_size; j++)
        temp += fabs (Ai[j]);

      norm = ((norm > temp) ? norm : temp);
    }

  return norm;
}

double norm_1_blocking (double *A, int matrix_size, double *block_1, double *block_2, int block_size)
{
  int block_quantity_dev = matrix_size / block_size;
  int block_quantity_rem = matrix_size % block_size;
  int i,j,k;
  int i_, j_;

  double norm = 0;
  double temp = 0;
  double *block_i = NULL;

  memset (block_2, 0, block_size * block_size * sizeof (double));

  for ( i_ = 0; i_ < block_quantity_dev; i_++)
    {
      memset (block_2, 0, block_size * sizeof (double));
      for ( j_ = 0; j_ < block_quantity_dev; j_++)
        {
          get_block (A, matrix_size, block_1, block_size, i_, j_, block_quantity_dev, block_quantity_rem);
          for (i = 0; i < block_size; i++)
            {
              block_i = block_1 + block_size * i;
              temp = 0;
              for (j = 0; j < block_size; j++)
                temp += fabs(block_i[j]);

              block_2[i] += temp;
            }
        }
      if (block_quantity_rem != 0)
        {
          get_block (A, matrix_size, block_1, block_size, i_, j_, block_quantity_dev, block_quantity_rem);
          for (i = 0; i < block_size; i++)
            {
              block_i = block_1 + block_size * i;
              temp = 0;
              for (j = 0; j < block_quantity_rem; j++)
                temp += fabs(block_i[j]);

              block_2[i] += temp;
            }
        }

      for (k = 0; k < block_size; k++)
        norm = ((norm > block_2[k]) ? norm : block_2[k]);
    }
  if (block_quantity_rem != 0)
    {
      memset (block_2, 0, block_quantity_rem * sizeof (double));

      for ( j_ = 0; j_ < block_quantity_dev; j_++)
        {
          get_block (A, matrix_size, block_1, block_size, i_, j_, block_quantity_dev, block_quantity_rem);
          for (i = 0; i < block_quantity_rem; i++)
            {
              block_i = block_1 + block_size * i;
              temp = 0;
              for (j = 0; j < block_size; j++)
                temp += fabs(block_i[j]);

              block_2[i] += temp;
            }

        }
      if (block_quantity_rem != 0)
        {
          get_block (A, matrix_size, block_1, block_size, i_, j_, block_quantity_dev, block_quantity_rem);
          for (i = 0; i < block_quantity_rem; i++)
            {
              block_i = block_1 + block_size * i;
              temp = 0;
              for (j = 0; j < block_quantity_rem; j++)
                temp += fabs(block_i[j]);

              block_2[i] += temp;
            }
        }

      for (k = 0; k < block_quantity_rem; k++)
        norm = ((norm > block_2[k]) ? norm : block_2[k]);
    }

  return norm;
}

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

void get_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Block_i[j] = Ai[j];

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
      for (int j = 0; j < block_n_size; j++)
        Ai[j] = Block_i[j];

      Ai += matrix_size;
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

void get_block_rem (double *A, int matrix_size, double *Block, int block_size,
                    int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Block_i[j] = Ai[j];

      Ai += matrix_size;
      Block_i += block_size;
    }
}


void set_block_rem (double *A, int matrix_size, double *Block, int block_size,
                    int i_, int j_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  int block_n_size = (j_ < dev ? block_size : rem_of_dev);

  double *Block_i = Block;
  double *Ai = A + (i_ * matrix_size + j_) * block_size;

  for (int i = 0; i < block_m_size; i++)
    {
      for (int j = 0; j < block_n_size; j++)
        Ai[j] = Block_i[j];

      Ai += matrix_size;
      Block_i += block_size;
    }
}

void get_block_vector_rem (double *B, double *Block, int block_size,
                           int i_, int dev, int rem_of_dev)
{
  int block_m_size = (i_ < dev ? block_size : rem_of_dev);
  double *Bi = B + i_ * block_size;

  for (int i = 0; i < block_m_size; i++)
    Block[block_size * i] = Bi[i];
}


void set_block_vector_rem (double *B, double *Block,int block_size,
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

int solve_optimized (int matrix_size, double *A, double *B, double *X,
                     int block_size, double *block_1, double *block_2)
{

  int block_quantity_dev = matrix_size / block_size;
  int block_quantity_reminder = matrix_size % block_size;

  int i, j, k;
  int shift = block_size * block_size;

  double eps = EPS;
  double temp = 0;

  double *block_3 = block_1 + block_size * block_size;

  double norm = norm_1_blocking (A, matrix_size, block_1, block_2, block_size);

  if (CRUTCH == 4)
    eps = 1e-18;

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
          get_block (A, matrix_size, block_3, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_1, block_3, block_size, block_size, block_size, block_2, eps);

          set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          set_block(A, matrix_size, block_3, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          for (k = i + 1; k < block_quantity_dev; k++)
            {

              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_size, block_size, block_2, shift);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0)
            {
              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_size, block_quantity_reminder, block_2, shift);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          get_block_vector (B, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);

          traverse_vector_zeroing (block_1, block_3, block_size, block_size, block_2);

          set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          set_block_vector (B, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);
        }

      if (block_quantity_reminder != 0)
        {

          get_block (A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          get_block (A, matrix_size, block_3, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          zeroing_block (block_1, block_3, block_size, block_quantity_reminder, block_size, block_2, eps);

          set_block(A, matrix_size, block_1, block_size, i, i, block_quantity_dev, block_quantity_reminder);
          set_block(A, matrix_size, block_3, block_size, j, i, block_quantity_dev, block_quantity_reminder);

          for (k = i + 1; k < block_quantity_dev; k++)
            {

              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size, block_quantity_reminder, block_size, block_2, shift);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }
          if (block_quantity_reminder != 0)
            {
              get_block (A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              get_block (A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);

              traverse_block_zeroing (block_1, block_3, block_size,
                                      block_quantity_reminder, block_quantity_reminder, block_2, shift);

              set_block(A, matrix_size, block_1, block_size, i, k, block_quantity_dev, block_quantity_reminder);
              set_block(A, matrix_size, block_3, block_size, j, k, block_quantity_dev, block_quantity_reminder);
            }

          get_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          get_block_vector (B, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);

          traverse_vector_zeroing (block_1, block_3, block_size, block_quantity_reminder, block_2);

          set_block_vector (B, block_1, block_size, i, block_quantity_dev, block_quantity_reminder);
          set_block_vector (B, block_3, block_size, j, block_quantity_dev, block_quantity_reminder);
        }
      if (fabs (A[i + i * matrix_size]) <= eps)
        return INCONSISTENT_SYSTEM;
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
