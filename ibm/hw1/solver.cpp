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
      return (double) (i == j ? 2 : (abs (i - j) == 1 ? -1 : 0));
    case 3:
      return (double) ((i == j) && i < matrix_size) ? 1 : ((j == matrix_size) ? i : ((i == matrix_size) ? j : 0));
    case 4:
      return 1. / (i + j - 1);
    default:
      return 1;
    }
}

void init_matrix (double *A, int matrix_size, int formula_type)
{
  for (int i = 0; i < matrix_size; i++)
    {
      double *Ai = A + i * matrix_size;
      for (int j = 0; j < matrix_size; j++)
        Ai[j] = formula(formula_type, matrix_size, i, j);
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

double calc_norm (double *A, int matrix_size)
{
  double *Ai = nullptr;
  double temp = 0;

  double norm = 0;
  for (int i = 0; i < matrix_size; i++)
    {
      Ai = A + i * matrix_size;
      temp = 0;
      for (int j = 0; j < matrix_size; j++)
        temp += fabs (Ai[j]);

      norm = ((norm > temp) ? norm : temp);
    }

  return norm;
}

double residual_1 (double *A, double *X, int matrix_size)
{
  double ans = 0;
  for (int i = 0; i < matrix_size; i++)
    {
      ans += A[i + i * matrix_size];
      ans -= X[i];
    }

  return fabs (ans);
}

double residual_2 (double *A, double *X, int matrix_size)
{
  double matr_len = 0;
  double eigenvector_len = 0;
  for (int i = 0; i < matrix_size; i++)
    {
      double matrix_len_temp = 0;
      for (int j = 0; j < matrix_size; j++)
        matrix_len_temp += A[j + i * matrix_size] * A[i + j * matrix_size];

      eigenvector_len += X[i] * X[i];
      matr_len += (matrix_len_temp);
    }

  return fabs (sqrt (matr_len) - sqrt (eigenvector_len));
}

int find_eigenvalues (double *matrix, double *eigenvalues_array, double *add_mem, int matrix_size, double precision,
                      double norm, double *t_1, double *t_2, int f_type)
{  
  int itterations = 0;
  double shift = 0;
  double eps = norm * precision;
  int max_itterations = 5 * matrix_size;

  *t_1 = clock ();
  matrix_to_almost_triangular (matrix, matrix_size, norm);
  *t_1 = (clock () - *t_1) / CLOCKS_PER_SEC;

  *t_2 = clock ();
  for (int k = matrix_size; k > 2; k--)
    {
      int escape_condition_index = (k - 1) * matrix_size + k - 2;
      for ( ; fabs (matrix[escape_condition_index]) >= eps && itterations < max_itterations; itterations++)
        {
          shift = shift_get (matrix, matrix_size, k, f_type);
          shift_make (matrix, matrix_size, k, shift);

          QR_decomposition (matrix, matrix_size, add_mem, k, norm);
          RQ_production (matrix, matrix_size, add_mem, k);

          shift_make (matrix, matrix_size, k, -shift);
        }
    }
  *t_2 = (clock () - *t_2) / CLOCKS_PER_SEC;

  if (matrix_size > 1)
    {
      double b = matrix[0] + matrix[matrix_size + 1];
      double c = matrix[0] * matrix[matrix_size + 1] - matrix[1] * matrix[matrix_size];
      double discriminant = sqrt(b * b - 4.0 * c);

      matrix[0] = 0.5 * (b + discriminant);
      matrix[matrix_size + 1] = 0.5 * (b - discriminant);

      itterations ++;
    }

  for (int i = 0; i < matrix_size; i++)
    eigenvalues_array[i] = matrix[i * matrix_size + i];

  return itterations;
}

void matrix_to_almost_triangular (double *matrix, int matrix_size, double norm)
{
  double root, temp;
  double buff_1, buff_2, cos_, sin_;
  double *Ak, *Ai;
  int i, j, k;

  double eps = norm * EPS;

  for (k = 1; k < matrix_size - 1; ++k)
    {
      Ak = matrix + k * matrix_size;
      temp = Ak[k - 1] * Ak[k - 1];

      for (i = k + 1; i < matrix_size; i++)
        {
          Ai = matrix + i * matrix_size;
          if (fabs (Ai[k - 1]) < eps)
            {
              Ai[k - 1] = 0;
              continue;
            }
          temp += Ai[k - 1] * Ai[k - 1];
          root = sqrt (temp);
          if (root < eps)
            {
              Ai[k - 1] = 0;
              continue;
            }

          cos_ = Ak[k - 1] / root;
          sin_ = - Ai[k - 1] / root;

          Ak[k - 1] = root;
          Ai[k - 1] = 0;

          for (j = k ; j < matrix_size; j++)
            {
              buff_1 = Ak[j];
              buff_2 = Ai[j];

              Ak[j] = buff_1 * cos_ - buff_2 * sin_;
              Ai[j] = buff_1 * sin_ + buff_2 * cos_;
            }

          double *Ak_column = matrix + k;
          double *Ai_column = matrix + i;
          for (j = 0; j < matrix_size * matrix_size; j += matrix_size)
            {
              buff_1 = Ak_column[j];
              buff_2 = Ai_column[j];

              Ak_column[j] = buff_1 * cos_ - buff_2 * sin_;
              Ai_column[j] = buff_1 * sin_ + buff_2 * cos_;
            }
        }
    }

}

void QR_decomposition (double *matrix, int matrix_size, double *add_mem, int cur_itter, double norm)
{
  double root = 0;
  double *Ak, *Ak_under;

  double *cos_ = add_mem;
  double *sin_ = add_mem;

  double sin_cur = 0;
  double cos_cur = 0;

  double eps = norm * EPS;

  for (int k = 0; k < cur_itter - 1; k++)
    {
      Ak = matrix + k * matrix_size;
      Ak_under = matrix + (k + 1) * matrix_size;

      double x = Ak[k];
      double y = Ak_under[k];

      if (fabs (y) < eps)
        {
          cos_cur = (x > 0.0 ? 1.0 : -1.0);
          sin_cur = 0;

          cos_[k] = cos_cur;
          sin_[k + 1] = sin_cur;

          cos_ ++;
          sin_ ++;
        }
      else
        {
          root = sqrt (x * x + y * y);
          if (root < eps)
            {
              cos_cur = (x > 0.0 ? 1.0 : -1.0);
              sin_cur = 0;

              cos_[k] = cos_cur;
              sin_[k + 1] = sin_cur;

              cos_ ++;
              sin_ ++;

              continue;
            }
          else
            {
              cos_cur = x / root;
              sin_cur = -y / root;

              cos_[k] = cos_cur;
              sin_[k + 1] = sin_cur;
            }

          for (int j = k + 1; j < cur_itter; j++)
            {
              x = Ak[j];
              y = Ak_under[j];

              Ak[j] = x * cos_cur - y * sin_cur;
              Ak_under[j] = x * sin_cur + y * cos_cur;
            }

          cos_ ++;
          sin_ ++;

          Ak[k] = root;
          Ak_under[k] = 0;
        }
    }
}

void RQ_production (double *matrix, int matrix_size, double *add_mem, int cur_itter)
{
  double *Ak = nullptr;
  double *Ak_under = nullptr;

  double *cos_ = add_mem;
  double *sin_ = add_mem;

  double cos_cur = 0;
  double sin_cur = 0;

  double x = 0;
  double y = 0;

  for (int k = 0; k < cur_itter - 1; k++)
    {
      cos_cur = cos_[k];
      sin_cur = sin_[k + 1];

      if (fabs (sin_cur) < EPS)
        {
          cos_++;
          sin_++;

          continue;
        }

      Ak = matrix + k;
      Ak_under = matrix + k + 1;

      for (int j = 0; j < k + 2; j++)
        {
          int j_matr = j * matrix_size;

          x = Ak[j_matr];
          y = Ak_under[j_matr];

          Ak[j_matr] = x * cos_cur - y * sin_cur;
          Ak_under[j_matr] = x * sin_cur + y * cos_cur;
        }

      cos_++;
      sin_++;
    }
}

double shift_get (double *matrix, int matrix_size, int cur_itter, int f_type)
{
  if (f_type == 2)
    return matrix[(cur_itter - 1) * matrix_size + cur_itter - 1] + matrix[(cur_itter - 1) * matrix_size + cur_itter - 2];

  return matrix[(cur_itter - 1) * matrix_size + cur_itter - 1];
}

void shift_make (double *matrix, int matrix_size, int cur_itter, double shift)
{
  for (int i = 0; i < cur_itter; i++)
    matrix[i * matrix_size + i] -= shift;
}
