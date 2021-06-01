#include "solver.h"
#include "thread_func.h"

int solver_unit::get_len (int nx, int ny)
{
  LEN = 6 * (nx - 1) * (ny - 1) + 4 * (2 * (nx - 1) + 2 * (ny - 1)) + 3 * 2 + 2 * 2;
  return LEN;
}

void solver_unit::ij_to_l (int nx, int ny, int i, int j, int &l)
{
  (void)ny;
  l = i + j * (nx + 1);
}

void solver_unit::l_to_ij (int nx, int ny, int &i, int &j, int l)
{
  (void)ny;
  j = l / (nx + 1);
  i = l - j * (nx + 1);
}

int solver_unit::get_off_diag_index (int nx, int ny, int l, int *J, double *a_diag, double *a)
{
  int i = 0, j = 0;
  l_to_ij (nx, ny, i, j, l);
  if (i > 0 && i < nx && j > 0 && j < ny)
    {
      *a_diag = 6.0 / 12.0;

      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j - 1, J [1]);
      ij_to_l (nx, ny, i - 1, j - 1, J [2]);
      ij_to_l (nx, ny, i - 1, j + 0, J [3]);
      ij_to_l (nx, ny, i + 0, j + 1, J [4]);
      ij_to_l (nx, ny, i + 1, j + 1, J [5]);
      for (int w = 0; w < 6; w ++)
        a [w] = 1.0 / 12.0;
      return 6;
    }
  if (i == 0 && j > 0 && j < ny)
    {
      *a_diag = 3.0 / 12.0;
      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j - 1, J [1]);
      ij_to_l (nx, ny, i + 0, j + 1, J [2]);
      ij_to_l (nx, ny, i + 1, j + 1, J [3]);
      a [0] = 1.0 / 12.0;
      a [1] = 1.0 / 24.0;
      a [2] = 1.0 / 24.0;
      a [3] = 1.0 / 12.0;
      return 4;
    }
  if (i == nx && j > 0 && j < ny)
    {
      *a_diag = 3.0 / 12.0;
      ij_to_l (nx, ny, i + 0, j - 1, J [0]);
      ij_to_l (nx, ny, i - 1, j - 1, J [1]);
      ij_to_l (nx, ny, i - 1, j + 0, J [2]);
      ij_to_l (nx, ny, i + 0, j + 1, J [3]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 12.0;
      a [2] = 1.0 / 12.0;
      a [3] = 1.0 / 24.0;
      return 4;
    }
  if (i > 0 && i < nx && j == 0)
    {
      *a_diag = 3.0 / 12.0;
      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i - 1, j + 0, J [1]);
      ij_to_l (nx, ny, i + 0, j + 1, J [2]);
      ij_to_l (nx, ny, i + 1, j + 1, J [3]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 24.0;
      a [2] = 1.0 / 12.0;
      a [3] = 1.0 / 12.0;
      return 4;
    }
  if (i > 0 && i < nx && j == ny)
    {
      *a_diag = 3.0 / 12.0;
      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j - 1, J [1]);
      ij_to_l (nx, ny, i - 1, j - 1, J [2]);
      ij_to_l (nx, ny, i - 1, j + 0, J [3]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 12.0;
      a [2] = 1.0 / 12.0;
      a [3] = 1.0 / 24.0;
      return 4;
    }
  if (i == 0 && j == 0)
    {
      *a_diag = 2.0 / 12.0;
      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j + 1, J [1]);
      ij_to_l (nx, ny, i + 1, j + 1, J [2]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 24.0;
      a [2] = 1.0 / 12.0;
      return 3;
    }
  if (i == nx && j == ny)
    {
      *a_diag = 2.0 / 12.0;
      ij_to_l (nx, ny, i + 0, j - 1, J [0]);
      ij_to_l (nx, ny, i - 1, j - 1, J [1]);
      ij_to_l (nx, ny, i - 1, j + 0, J [2]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 12.0;
      a [2] = 1.0 / 24.0;
      return 3;
    }
  if (i == 0 && j == ny)
    {
      *a_diag = 1.0 / 12.0;
      ij_to_l (nx, ny, i + 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j - 1, J [1]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 24.0;
      return 2;
    }
  if (i == nx && j == 0)
    {
      *a_diag = 1.0 / 12.0;
      ij_to_l (nx, ny, i - 1, j + 0, J [0]);
      ij_to_l (nx, ny, i + 0, j + 1, J [1]);
      a [0] = 1.0 / 24.0;
      a [1] = 1.0 / 24.0;
      return 2;
    }
  return -1;
}

int solver_unit::allocate (double *A, double *b, int *I, int nx, int ny)
{
  (void)b;
  int i = 0, l = 0, s = 0;
  N = (nx + 1) * (ny + 1); // diag
  int nz = get_len (nx, ny);

  if (!A)
    return -1;
  if (!I)
    {
      delete [] A;
      return -2;
    }
  I [0] = N + 1;
  for (i = 1; i <= N; i ++)
    {
      l = get_off_diag_num (nx, ny, i - 1);
      I [i] = l + I [i - 1];
      s += l;
    }
  return 0;
}

void solver_unit::calculate_matrix (double *A, int *I, int nx, int ny, int p, int k)
{
  int N = (nx + 1) * (ny + 1), sum = 0;
  int begin = 0, end = 0, i = 0;
  get_begin_end (p, N, k, begin, end);

  for (i = begin; i < end; i ++)
    {
     sum += get_off_diag_index (nx, ny, i, I + I [i], A + i, A + I [i]);
    }

  A [N] = 0.0;

  reduce_sum (p, &sum, 1);
}

int solver_unit::get_off_diag_num (int nx, int ny, int l)
{
  int i = 0, j = 0;
  l_to_ij (nx, ny, i, j, l);
  if (i > 0 && i < nx && j > 0 && j < ny) return 6;
  if ((i == 0 || i == nx) && (j > 0 && j < ny)) return 4;
  if ((i > 0 && i < nx) && (j == 0 || j == ny)) return 4;
  if ((i == 0 && j == 0) || (i == nx && j == ny)) return 3;
  if ((i == 0 && j == ny) || (i == nx && j == 0)) return 2;
  return -1;
}

void solver_unit::matr_to_vector_multiply (double *A, int *I, int n, double *x, double *y, int p, int k)
{
  int i = 0, j = 0, J = 0;
  int begin = 0, end = 0, l = 0;
  double s = 0.0;
  get_begin_end (p, n, k, begin, end);

  for (i = begin; i < end; i ++)
    {
      s = A [i] * x [i];
      l = I [i + 1] - I [i];
      J = I [i];
      for (j = 0; j < l; j ++)
        s += A [J + j] * x [I [J + j]];
      y [i] = s;
    }
  reduce_sum (p, 0, 1);
}

void solver_unit::jacobi_preconditioner (double *A, int n, double *y, double *x, int p, int k)
{
  int begin = 0, end = 0, i = 0;
  get_begin_end (p, n, k, begin, end);

  for (i = begin; i < end; i ++)
    x [i] = y [i] / A [i];
  reduce_sum (p, 0, 1);
}

double solver_unit::dot_product (int n, double *x, double *y, int p, int k, double * buf)
{
  int begin = 0, end = 0, i = 0;
  double s = 0.0;

  get_begin_end (p, n, k, begin, end);

  for (i = begin; i < end; i ++)
    s += x [i] * y [i];

  buf [k] = s;
  reduce_sum (p, 0, 1);
  s = 0.0;

  for (i = 0; i < p; i ++)
    s += buf [i];

  reduce_sum (p, 0, 1);
  return s;
}

void solver_unit::vector_multiply (int n, double *x, double *y, double t, int p, int k)
{
  int begin = 0, end = 0, i = 0;
  get_begin_end (p, n, k, begin, end);

  for (i = begin; i < end; i ++)
    x [i] -= t * y [i];
  reduce_sum (p, 0, 1);
}

int solver_unit::solver_itteration (double *A, int *I, int n, double *b, double *x, double *r, double *u, double * v,
                                             double eps, int max_it, int p, int k, double *buf)
{
  int it = 0;
  double C1 = 0.0, C2 = 0.0, tau = 0.0;
  double b_norm2 = dot_product (n, b, b, p, k, buf);
  double prec = eps * eps * b_norm2;
  matr_to_vector_multiply (A, I, n, x, r, p, k);
  vector_multiply (n, r, b, 1.0, p, k);

  for (it = 0; it < max_it; it ++)
    {
      jacobi_preconditioner(A, n, r, v, p, k);
      matr_to_vector_multiply(A, I, n, v, u, p, k);
      C1 = dot_product (n, u, r, p, k, buf);
      C2 = dot_product (n, u, u, p, k, buf);
      if (C1 < prec || C2 < prec)
        break;
      tau = C1 / C2;
      vector_multiply (n, x, v, tau, p, k);
      vector_multiply (n, r, u, tau, p, k);
      reduce_sum (p, 0, 1);
    }

  reduce_sum (p, 0, 1);

  if (it >= max_it)
    return -1;

  reduce_sum (p, 0, 1);
  return it;
}

int solver_unit::solver (double *A, int *I, int n, double *b, double *x, double *r, double *u,
                                                  double *v, double eps, int max_it, int p, int k, double * buf)
{
  int step = 50, ret = 0, it = 0;
  for (it = 0; it < max_it; it += step)
    {
      ret += solver_itteration (A, I, n, b, x, r, u, v, eps, step, p, k, buf);
      reduce_sum (p, 0, 1);
      if (ret >= 0)
        break;
    }
  m_itter = ret;
  reduce_sum (p, 0, 1);
  if (it >= max_it)
    return -1;
  return 0;
}

void solver_unit::get_begin_end (int p, int n, int k, int &begin, int &end)
{
  if (n % p == 0)
    {
      begin = k * (n / p);
      end = (k + 1) * (n / p);
    }
  else
    {
      if (k < n % p)
        {
          begin = k * (n / p) + k;
          end = (k + 1) * (n / p) + k + 1;
        }
      else
        {
          begin = n % p + k * (n / p);
          end = n % p + (k + 1)* (n / p);
        }
    }
}

double solver_unit::rhs_integrals (int nx, int ny, int l)
{
  int i = 0, j = 0;
  l_to_ij(nx, ny, i, j, l);
  double hx = (m_rectangle.get_d ().m_x - m_rectangle.get_a ().m_x) / nx, hy = (m_rectangle.get_a ().m_y - m_rectangle.get_d ().m_y) / ny;
  double x0 = m_rectangle.get_a ().m_x + i * hx, y0 = m_rectangle.get_d ().m_y + j * hy;

  double l1 = 0.0, l2 = 0.0, l3 = 0.0, l4 = 0.0;

  if (i > 0 && i < nx && j > 0 && j < ny)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 + hx / 2, y0) + m_func (x0 + hx / 2, y0 + hy / 2) + m_func (x0, y0 + hy / 2) +
           m_func (x0 - hx / 2, y0) + m_func (x0 - hx / 2, y0 - hy / 2) + m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 + hx, y0 + hy / 2) +  m_func (x0 + hx / 2, y0 + hy) + m_func (x0 - hx / 2, y0 + hy / 2) +
           m_func (x0 - hx, y0 - hy / 2) + m_func (x0 - hx / 2, y0 - hy) + m_func (x0 + hx / 2, y0 - hy / 2);
      l4 = m_func (x0 + hx, y0) + m_func (x0 + hx, y0 + hy) + m_func (x0, y0 + hy) +
           m_func (x0 - hx, y0) + m_func (x0 - hx, y0 - hy) + m_func (x0, y0 - hy);

      return  (36 * l1 + 20 * l2 + 4 * l3 + 2 * l4) / 192;
    }
  if (i == 0 && j > 0 && j < ny)
    {
      l1 = m_func (x0, y0);
      l2 = 2 * m_func (x0 + hx / 2, y0) + 2 * m_func (x0 + hx / 2, y0 + hy / 2) + m_func (x0, y0 + hy / 2) +
           m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 + hx, y0 + hy / 2) + m_func (x0 + hx / 2, y0 + hy) + m_func (x0 + hx / 2, y0 - hy / 2);
      l4 = 2 * m_func (x0 + hx, y0) + 2 * m_func (x0 + hx, y0 + hy) + m_func (x0, y0 + hy) + m_func (x0, y0 - hy);

      return  (18 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i == nx && j > 0 && j < ny)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0, y0 + hy / 2) + 2 * m_func (x0 - hx / 2, y0) + 2 * m_func (x0 - hx / 2, y0 - hy / 2) +
           m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 - hx / 2, y0 + hy / 2) + m_func (x0 - hx, y0 - hy / 2) + m_func (x0 - hx / 2, y0 - hy);
      l4 = m_func (x0, y0 + hy) + 2 * m_func (x0 - hx, y0) + 2 * m_func (x0 - hx, y0 - hy) + m_func (x0, y0 - hy);

      return  (18 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i > 0 && i < nx && j == 0)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 + hx / 2, y0) + 2 * m_func (x0 + hx / 2, y0 + hy / 2) + 2 * m_func (x0, y0 + hy / 2) +
           m_func (x0 - hx / 2, y0);
      l3 = m_func (x0 + hx, y0 + hy / 2) + m_func (x0 + hx / 2, y0 + hy) + m_func (x0 - hx / 2, y0 + hy / 2);
      l4 = m_func (x0 + hx, y0) + 2 * m_func (x0 + hx, y0 + hy) + 2 * m_func (x0, y0 + hy) + m_func (x0 - hx, y0);

      return  (18 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i > 0 && i < nx && j == ny)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 + hx / 2, y0) + m_func (x0 - hx / 2, y0) + 2 * m_func (x0 - hx / 2, y0 - hy / 2) +
           2 * m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 - hx, y0 - hy / 2) + m_func (x0 - hx / 2, y0 - hy) + m_func (x0 + hx / 2, y0 - hy / 2);
      l4 = m_func (x0 - hx, y0) + 2 * m_func (x0 - hx, y0 - hy) + 2 * m_func (x0, y0 - hy) + m_func (x0 + hx, y0);

      return  (18 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i == 0 && j == 0)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 + hx / 2, y0) + 2 * m_func (x0 + hx / 2, y0 + hy / 2) + m_func (x0, y0 + hy / 2);
      l3 = m_func (x0 + hx, y0 + hy / 2) + m_func (x0 + hx / 2, y0 + hy);
      l4 = m_func (x0 + hx, y0) + 2 * m_func (x0 + hx, y0 + hy) + m_func (x0, y0 + hy);

      return  (12 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i == nx && j == ny)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 - hx / 2, y0) + 2 * m_func (x0 - hx / 2, y0 - hy / 2) + m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 - hx, y0 - hy / 2) + m_func (x0 - hx / 2, y0 - hy);
      l4 = m_func (x0 - hx, y0) + 2 * m_func (x0 - hx, y0 - hy) + m_func (x0, y0 - hy);

      return  (12 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i == 0 && j == ny)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0 + hx / 2, y0) + m_func (x0, y0 - hy / 2);
      l3 = m_func (x0 + hx / 2, y0 - hy / 2);
      l4 = m_func (x0 + hx, y0) + m_func (x0, y0 - hy);

      return  (6 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  if (i == nx && j == 0)
    {
      l1 = m_func (x0, y0);
      l2 = m_func (x0, y0 + hy / 2) + m_func (x0 - hx / 2, y0);
      l3 = m_func (x0 - hx / 2, y0 + hy / 2);
      l4 = m_func (x0, y0 + hy) + m_func (x0 - hx, y0);

      return  (6 * l1 + 10 * l2 + 4 * l3 + 1 * l4) / 192;
    }
  return -1;
}

void solver_unit::calculate_rhs (double *b, int nx, int ny, int p, int k)
{
  int begin = 0, end = 0, N = (nx + 1) * (ny + 1), i = 0;
  get_begin_end(p, N, k, begin, end);
  for (i = begin; i < end; i ++)
    {
      b [i] = rhs_integrals (nx, ny, i);
    }
  reduce_sum (p, 0, 1);
}

void solver_unit::normalization (double *A, double *b, int nx, int ny, int p, int k)
{
  int i = 0;
  (void)p, (void)k;
  double hx = (m_rectangle.get_d ().m_x - m_rectangle.get_a ().m_x) / nx, hy = (m_rectangle.get_a ().m_y - m_rectangle.get_d ().m_y) / ny;
  A [N] = 0.0;
  for (i = 0; i < N + LEN + 1; i ++)
    A [i] = A [i] * hx * hy;
  for (i = 0; i < N; i ++)
    b [i] = b [i] * hx * hy;

}

void reduce_sum (int p, int * a, int n)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
  static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;
  static int t_in = 0;
  static int t_out = 0;
  static int * p_a = 0;
  int i = 0;
  if (p <= 1)
    return;
  pthread_mutex_lock (&m);
  if (!p_a)
    {
      p_a = a;
    }
  else
    {
      for (i = 0; i < n; i ++)
        p_a [i] += a[i];
    }
  t_in ++;
  if (t_in >= p)
    {
      t_out = 0;
      pthread_cond_broadcast (&c_in);
    }
  else
    {
      while (t_in < p)
        {
          pthread_cond_wait (& c_in, &m);
        }
    }
  if (p_a != a)
    {
      for (i = 0; i < n; i ++)
        a [i] = p_a [i];
    }
  t_out ++;
  if (t_out >= p)
    {
      t_in = 0;
      p_a = 0;
      pthread_cond_broadcast (&c_out);
    }
  else
    {
      while (t_out < p)
        {
          pthread_cond_wait (&c_out, &m);
        }
    }
  pthread_mutex_unlock (&m);
}
