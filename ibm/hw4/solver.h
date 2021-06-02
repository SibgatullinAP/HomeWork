#ifndef MSR_H
#define MSR_H

#include "data_bus.h"
#include "thread_func.h"

class solver_data
{
public:
  int m_thread_number = 0;
  int m_thread_id = 0;
  int m_nx = 0;
  int m_ny = 0;
  double m_eps = 0.0;
  data_bus *m_common_data = nullptr;
public:
  void set_arg (int thread_quantity, int k, int nx, int ny, double eps, data_bus *common_data)
  {
    m_thread_number = thread_quantity;
    m_thread_id = k;
    m_nx = nx;
    m_ny = ny;
    m_eps = eps;
    m_common_data = common_data;
  }
};

class solver_unit: public solver_data
{
public:
  int m_N = 0;
  int m_LEN = 0;
  std::function<double(double, double)> m_func = {};
  domain m_rectangle = {};
  int m_itter = 0;

public:
  void get_begin_end (int n, int &begin, int &end);
  int get_off_diag_num (int nx, int ny, int l);
  int get_off_diag_index (int nx, int ny, int l, int *J, double *a_diag, double *a);

  void allocate ();
  void reset_memmory ();

  double dot_product (int n, double *x, double *y, double *buff);
  void matr_to_vector_multiply (double *A, int *I, int n, double *x, double *y);
  void vector_multiply (int n, double *x, double *y, double t);

  void jacobi_preconditioner (double *A, int n, double *y, double *x);
  double rhs_integrals (int nx, int ny, int l);
  void calculate_rhs ();
  void calculate_matrix ();
  void normalization ();

  int get_len (int nx, int ny);
  void ij_to_l (int nx, int ny, int i, int j, int &l);
  void l_to_ij (int nx, int ny, int &i, int &j, int l);

  int solver_itteration (int max_it);
  int solver (int max_it);
};

#endif // MSR_H
