#include "solver.h"

double solve_1 (double *matrix_A, double *X, double *X_0, int matrix_size, int m_th)
{
  int i;
  for (i = 0; i <= m_th; i++)
    {
      matrix_to_vector_product (matrix_A, X_0, X, matrix_size);

      double *temp = X_0;
      X_0 = X;
      X = temp;
    }

  double dot_prod_numerator = 0;
  double dot_prod_denumerator = 0;
  for (i = 0; i < matrix_size; i++)
    {
      double temp = X[i];
      dot_prod_numerator += X_0[i] * temp;
      dot_prod_denumerator += temp * temp;
    }

  if (m_th % 2 == 0)
    for (i = 0; i < matrix_size; i++)
      X_0[i] = X[i];

  if (fabs (dot_prod_denumerator) < EPS)
    {
      printf ("Dot product denumerator is < EPS!\n");
      printf ("%lf\n", dot_prod_denumerator);
      return 0;
    }

  return dot_prod_numerator / dot_prod_denumerator;
}


void solve_2 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double tau)
{
  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, X0, X, matrix_size);
      for (int j = 0; j < matrix_size; j++)
        {
          double xj = X[j];
          xj -= B[j];
          X0[j] -= tau * xj;
        }
    }
  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}


void solve_3 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R)
{
  matrix_to_vector_product(matrix_A, X0, R, matrix_size);
  for (int j = 0; j < matrix_size; j++)
    R[j] -= B[j];

  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, R, X, matrix_size);
      double tau = 0;
      if (tau_3 (R, X, matrix_size, &tau) < 0 || fabs (tau) < EPS)
        {
          printf ("Dot product denumerator is < EPS!\n");
          return;
        }

      for (int j = 0; j < matrix_size; j ++)
        {
          X0[j] -= tau * R[j];
          R[j] -= tau * X[j];
        }
    }

  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}

void solve_4 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R)
{
  matrix_to_vector_product(matrix_A, X0, R, matrix_size);
  for (int j = 0; j < matrix_size; j++)
    R[j] -= B[j];

  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, R, X, matrix_size);
      double tau = 0;
      if (tau_4 (R, X, matrix_size, &tau) < 0 || fabs (tau) < EPS)
        {
          printf ("Dot product denumerator is < EPS!\n");
          return;
        }

      for (int j = 0; j < matrix_size; j ++)
        {
          X0[j] -= tau * R[j];
          R[j] -= tau * X[j];
        }
    }

  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}


void solve_5 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R)
{
  matrix_to_vector_product(matrix_A, X0, R, matrix_size);
  for (int j = 0; j < matrix_size; j++)
    R[j] -= B[j];

  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, R, X, matrix_size);
      double tau = 0;
      if (tau_5 (R, X, matrix_A, matrix_size, &tau) < 0 || fabs (tau) < EPS)
        {
          printf ("Dot product denumerator is < EPS!\n");
          return;
        }

      for (int j = 0; j < matrix_size; j ++)
        {
          X0[j] -= tau * R[j];
          R[j] -= tau * X[j];
        }
    }

  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}

void solve_6 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R)
{
  matrix_to_vector_product(matrix_A, X0, R, matrix_size);
  for (int j = 0; j < matrix_size; j++)
    R[j] -= B[j];

  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, R, X, matrix_size);
      double tau = 0;
      if (tau_6 (R, X, matrix_A, matrix_size, &tau) < 0 || fabs (tau) < EPS)
        {
          printf ("Dot product denumerator is < EPS!\n");
          return;
        }

      for (int j = 0; j < matrix_size; j ++)
        {
          X0[j] -= tau * R[j];
          R[j] -= tau * X[j];
        }
    }

  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}


void solve_7 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R, double tau)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double tmp = matrix_A[i * matrix_size + i];
      if (fabs (tmp) < EPS)
        {
          printf ("D is singular matrix!\n");
          return;
        }

      R[i] = 1.0 / tmp;
    }

  for (int itter = 0; itter < m_th; itter++)
    {
      matrix_to_vector_product(matrix_A, X0, X, matrix_size);
      for (int j = 0; j < matrix_size; j++)
        {
          double xj = X[j];
          xj -= B[j];
          X0[j] -= tau * xj * R[j];
        }
    }

  for (int j = 0; j < matrix_size; j++)
    X[j] = X0[j];
}


int tau_3 (double *A, double *B, int matrix_size, double *answer)
{
  double dot_prod_numerator = 0;
  double dot_prod_denumerator = 0;

  for (int j = 0; j < matrix_size; j++)
    {
      double tmp = A[j];
      dot_prod_numerator += tmp * tmp;
      dot_prod_denumerator += B[j] * tmp;
    }

  if (fabs (dot_prod_denumerator) < EPS)
    {
      *answer = 0;
      return -1;
    }

  *answer = dot_prod_numerator / dot_prod_denumerator;
  return 1;
}


int tau_4 (double *A, double *B, int matrix_size, double *answer)
{
  double dot_prod_numerator = 0;
  double dot_prod_denumerator = 0;

  for (int j = 0; j < matrix_size; j++)
    {
      double tmp = B[j];
      dot_prod_numerator += A[j] * tmp;
      dot_prod_denumerator += tmp * tmp;
    }

  if (fabs (dot_prod_denumerator) < EPS)
    {
      *answer = 0;
      return -1;
    }

  *answer = dot_prod_numerator / dot_prod_denumerator;
  return 1;
}


int tau_5 (double *A, double *B, double *D, int matrix_size, double *answer)
{
  double dot_prod_numerator = 0;
  double dot_prod_denumerator = 0;

  for (int j = 0; j < matrix_size; j++)
    {
      double tmp_D = D[j * matrix_size + j];
      if (fabs (tmp_D) < EPS)
        {
          printf ("D is singular matrix!\n");
          return -1;
        }

      double tmp = A[j];
      dot_prod_numerator += tmp * tmp / tmp_D;
      dot_prod_denumerator += B[j] * tmp / tmp_D;
    }

  if (fabs (dot_prod_denumerator) < EPS)
    {
      *answer = 0;
      return -1;
    }

  *answer = dot_prod_numerator / dot_prod_denumerator;
  return 1;
}


int tau_6 (double *A, double *B, double *D, int matrix_size, double *answer)
{
  double dot_prod_numerator = 0;
  double dot_prod_denumerator = 0;

  for (int j = 0; j < matrix_size; j++)
    {
      double tmp_D = D[j * matrix_size + j];
      if (fabs (tmp_D) < EPS)
        {
          printf ("D is singular matrix!\n");
          return -1;
        }

      double tmp = B[j];
      dot_prod_numerator += A[j] * tmp / tmp;
      dot_prod_denumerator += tmp * tmp / tmp;
    }

  if (fabs (dot_prod_denumerator) < EPS)
    {
      *answer = 0;
      return -1;
    }

  *answer = dot_prod_numerator / dot_prod_denumerator;
  return 1;
}

void matrix_to_vector_product (double *matrix, double *vector, double *answer, int matrix_size)
{
  double temp_sum = 0;
  for (int i = 0; i < matrix_size; i++)
    {
      temp_sum = 0;
      for (int j = 0; j < matrix_size; j++)
        temp_sum += matrix[i * matrix_size + j] * vector[j];

      answer[i] = temp_sum;
    }
}


int read (double *A, int matrix_size_m, int matrix_size_n, char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < matrix_size_m; i++)
    {
      double *Ai = A + i * matrix_size_n;
      for (int j = 0; j < matrix_size_n; j++)
        {
          if (fscanf (file, "%lf", Ai + j) != 1)
            {
              fclose (file);
              return CANNOT_READ_FILE;
            }
        }
    }

  fclose (file);
  return 0;
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


double formula(int matrix_size, int i, int j)
{
  i += 1;
  j += 1;

  return (double) matrix_size - (i > j ? i : j) + 1;
}

void init_A (double *A, int matrix_size)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = A + i * matrix_size;
      for (int j = 0; j < matrix_size; j++)
        Ai[j] = formula(matrix_size, i, j);
    }
}

void init_X0 (double *X_0, int matrix_size)
{
  for (int i = 0; i < matrix_size; i++)
    X_0[i] = 1;
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
  double AX_i = 0;
  double *Ai = A;

  for (int i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      AX_i = 0;

      for (int j = 0; j < matrix_size; j++)
        AX_i += Ai[j] * X[j];

      AX_B_norm += fabs (AX_i - B[i]);
    }
  return AX_B_norm;
}
