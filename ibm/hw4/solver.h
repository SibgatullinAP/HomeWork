#ifndef MSR_H
#define MSR_H

#include "data_bus.h"

void reduce_sum (int p, int * a, int n);

class solver_unit
{
  public:
    int N = 0;
    int LEN = 0;
    std::function<double(double, double)> m_func = {};
    domain m_rectangle = {};
    int m_itter = 0;

  public:
    void get_begin_end (int p, int n, int k, int &begin, int &end);
    int get_off_diag_num (int nx, int ny, int l);
    int get_off_diag_index (int nx, int ny, int l, int *J, double *a_diag, double *a);

    int allocate (double *A, double *b, int *I, int nx, int ny);

    double dot_product (int n, double *x, double *y, int p, int k, double * buf);
    void matr_to_vector_multiply (double *A, int *I, int n, double *x, double *y, int p, int k);
    void vector_multiply (int n, double *x, double *y, double t, int p, int k);

    void jacobi_preconditioner (double *A, int n, double *y, double *x, int p, int k);
    double rhs_integrals (int nx, int ny, int l);
    void calculate_rhs (double *b, int nx, int ny, int p, int k);
    void calculate_matrix (double *A, int *I, int nx, int ny, int p, int k);
    void normalization (double *A, double *b, int nx, int ny, int p, int k);

    int get_len (int nx, int ny);
    void ij_to_l (int nx, int ny, int i, int j, int &l);
    void l_to_ij (int nx, int ny, int &i, int &j, int l);

    int solver_itteration (double *A, int *I, int n, double *b, double *x, double *r, double *u, double * v,
                                                 double eps, int max_it, int p, int k, double *buf);
    int solver (double *A, int *I, int n, double *b, double *x, double *r, double *u,
                                                      double *v, double eps, int max_it, int p, int k, double * buf);
};

class kernel_data: public solver_unit
{
  public:
    int m_thread_quantity = 0;
    int m_k = 0;
    int m_nx = 0;
    int m_ny = 0;
    double m_eps = 0.0;
    data_bus *m_common_data = nullptr;
  public:
    void set_arg (int thread_quantity, int k, int nx, int ny, double eps, data_bus *common_data)
    {
      m_thread_quantity = thread_quantity;
      m_k = k;
      m_nx = nx;
      m_ny = ny;
      m_eps = eps;
      m_common_data = common_data;
    }
};


#endif // MSR_H
