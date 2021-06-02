#include "solver.h"
#include "thread_func.h"

int solver_unit::get_len (int nx, int ny)
{
  m_LEN = 6 * (nx - 1) * (ny - 1) + 4 * (2 * (nx - 1) + 2 * (ny - 1)) + 3 * 2 + 2 * 2;
  return m_LEN;
}

void solver_unit::ij_to_l (int nx, int ny, int i, int j, int &l)
{
  (void) ny;
  l = i + j * (nx + 1);
}

void solver_unit::l_to_ij (int nx, int ny, int &i, int &j, int l)
{
  (void) ny;
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


void solver_unit::reset_memmory ()
{
  int nx = m_nx;
  int ny = m_ny;

  for (int u = 0; u < (nx + 1) * (ny + 1); u ++)
    {
      m_common_data->answer[u] = 0.0;
      m_common_data->m_b[u] = 0.0;
      m_common_data->m_r[u] = 0.0;
      m_common_data->m_u[u] = 0.0;
      m_common_data->m_v[u] = 0.0;
    }
}

void solver_unit::allocate ()
{
  int nx = m_nx;
  int ny = m_ny;

  m_common_data->m_b = new double [(nx + 1) * (ny + 1)];
  m_common_data->answer = new double [(nx + 1) * (ny + 1)];
  m_common_data->m_r = new double [(nx + 1) * (ny + 1)];
  m_common_data->m_u = new double [(nx + 1) * (ny + 1)];
  m_common_data->m_v = new double [(nx + 1) * (ny + 1)];
  m_common_data->m_A = new double [(nx + 1) * (ny + 1) + 1 + get_len (nx, ny)];
  m_common_data->m_I = new int [(nx + 1) * (ny + 1) + 1 + get_len (nx, ny)];
  m_common_data->m_buff = new double [m_thread_number];

  m_N = (nx + 1) * (ny + 1);
  m_common_data->m_I [0] = m_N + 1;

  int l = 0;
  for (int i = 1; i <= m_N; i ++)
    {
      l = get_off_diag_num (nx, ny, i - 1);
      m_common_data->m_I [i] = l +  m_common_data->m_I [i - 1];
    }

  reset_memmory ();
}

void solver_unit::calculate_matrix ()
{
  int N = (m_nx + 1) * (m_ny + 1);
  int sum = 0;
  int begin = 0, end = 0, i = 0;
  get_begin_end (N, begin, end);

  for (i = begin; i < end; i ++)
    sum += get_off_diag_index (m_nx, m_ny, i, m_common_data->m_I + m_common_data->m_I [i], m_common_data->m_A + i, m_common_data->m_A + m_common_data->m_I [i]);

  m_common_data->m_A[N] = 0.0;
  reduce_sum (m_thread_number, &sum, 1);
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

void solver_unit::matr_to_vector_multiply (double *A, int *I, int n, double *x, double *y)
{
  int i = 0, j = 0, J = 0;
  int begin = 0, end = 0, l = 0;
  double s = 0.0;
  get_begin_end (n, begin, end);

  for (i = begin; i < end; i ++)
    {
      s = A[i] * x[i];
      l = I[i + 1] - I[i];
      J = I[i];
      for (j = 0; j < l; j ++)
        s += A[J + j] * x[I[J + j]];
      y[i] = s;
    }
  reduce_sum (m_thread_number, 0, 1);
}

void solver_unit::jacobi_preconditioner (double *A, int n, double *y, double *x)
{
  int begin = 0, end = 0, i = 0;
  get_begin_end (n, begin, end);

  for (i = begin; i < end; i ++)
    x[i] = y[i] / A[i];
  reduce_sum (m_thread_number, 0, 1);
}

double solver_unit::dot_product (int n, double *x, double *y, double *buff)
{
  int begin = 0, end = 0, i = 0;
  double s = 0.0;

  get_begin_end (n, begin, end);

  for (i = begin; i < end; i ++)
    s += x [i] * y [i];

  buff[m_thread_id] = s;
  reduce_sum (m_thread_number, 0, 1);
  s = 0.0;

  for (i = 0; i < m_thread_number; i ++)
    s += buff[i];

  reduce_sum (m_thread_number, 0, 1);
  return s;
}

void solver_unit::vector_multiply (int n, double *x, double *y, double t)
{
  int begin = 0, end = 0, i = 0;
  get_begin_end (n, begin, end);

  for (i = begin; i < end; i ++)
    x [i] -= t * y [i];
  reduce_sum (m_thread_number, 0, 1);
}

int solver_unit::solver_itteration (int max_it)
{
  int it = 0;
  double C1 = 0.0, C2 = 0.0, tau = 0.0;
  double b_norm2 = dot_product ((m_nx + 1) * (m_ny + 1), m_common_data->m_b, m_common_data->m_b, m_common_data->m_buff);
  double prec = m_eps * m_eps * b_norm2;
  matr_to_vector_multiply (m_common_data->m_A, m_common_data->m_I, (m_nx + 1) * (m_ny + 1), m_common_data->answer, m_common_data->m_r);
  vector_multiply ((m_nx + 1) * (m_ny + 1), m_common_data->m_r, m_common_data->m_b, 1.0);

  for (it = 0; it < max_it; it ++)
    {
      jacobi_preconditioner(m_common_data->m_A, (m_nx + 1) * (m_ny + 1), m_common_data->m_r, m_common_data->m_v);
      matr_to_vector_multiply(m_common_data->m_A, m_common_data->m_I, (m_nx + 1) * (m_ny + 1), m_common_data->m_v, m_common_data->m_u);
      C1 = dot_product ((m_nx + 1) * (m_ny + 1), m_common_data->m_u, m_common_data->m_r, m_common_data->m_buff);
      C2 = dot_product ((m_nx + 1) * (m_ny + 1), m_common_data->m_u, m_common_data->m_u, m_common_data->m_buff);

      if (C1 < prec || C2 < prec)
        break;
      tau = C1 / C2;

      vector_multiply ((m_nx + 1) * (m_ny + 1), m_common_data->answer, m_common_data->m_v, tau);
      vector_multiply ((m_nx + 1) * (m_ny + 1), m_common_data->m_r, m_common_data->m_u, tau);
      reduce_sum (m_thread_number, 0, 1);
    }

  reduce_sum (m_thread_number, 0, 1);

  if (it >= max_it)
    return -1;

  reduce_sum (m_thread_number, 0, 1);
  return it;
}

int solver_unit::solver (int max_it)
{
  int step = 50;
  int ret = 0;
  int it = 0;
  for (it = 0; it < max_it; it += step)
    {
      ret += solver_itteration (step);
      reduce_sum (m_thread_number, 0, 1);
      if (ret >= 0)
        break;
    }
  m_itter = ret;

  reduce_sum (m_thread_number, 0, 1);

  if (it >= max_it)
    return -1;

  return 0;
}

void solver_unit::get_begin_end (int n, int &begin, int &end)
{
  if (n % m_thread_number == 0)
    {
      begin = m_thread_id * (n / m_thread_number);
      end = (m_thread_id + 1) * (n / m_thread_number);
    }
  else
    {
      if (m_thread_id < n % m_thread_number)
        {
          begin = m_thread_id * (n / m_thread_number) + m_thread_id;
          end = (m_thread_id + 1) * (n / m_thread_number) + m_thread_id + 1;
        }
      else
        {
          begin = n % m_thread_number + m_thread_id * (n / m_thread_number);
          end = n % m_thread_number + (m_thread_id + 1)* (n / m_thread_number);
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

void solver_unit::calculate_rhs ()
{
  int begin = 0, end = 0;
  int N = (m_nx + 1) * (m_ny + 1);

  get_begin_end(N, begin, end);

  for (int i = begin; i < end; i ++)
    m_common_data->m_b [i] = rhs_integrals (m_nx, m_ny, i);


  reduce_sum (m_thread_number, 0, 1);
}

void solver_unit::normalization ()
{
  double hx = (m_rectangle.get_d ().m_x - m_rectangle.get_a ().m_x) / m_nx;
  double hy = (m_rectangle.get_a ().m_y - m_rectangle.get_d ().m_y) / m_ny;

  m_common_data->m_A[m_N] = 0.0;

  for (int i = 0; i < m_N + m_LEN + 1; i++)
    m_common_data->m_A[i] = m_common_data->m_A[i] * hx * hy;

  for (int i = 0; i < m_N; i++)
    m_common_data->m_b[i] = m_common_data->m_b[i] * hx * hy;

}
