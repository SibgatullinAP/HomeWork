#include "constants.h"

int read (double *A, int matrix_size, char *file_name);
void print (double *A, int matrix_size_m, int matrix_size_n, int print_size);

double formula(int formula_type, int matrix_size, int i, int j);
void init_matrix (double *A, int matrix_size, int formula_type);

double residual_1 (double *A, double *X, int matrix_size);
double residual_2 (double *A, double *X, int matrix_size);
double calc_norm (double *A, int matrix_size);

int find_eigenvalues (double *matrix, double *eigenvalues_array, double *add_mem, int matrix_size, double precision,
                      double norm, double *t_1, double *t_2, int f_type);
void matrix_to_almost_triangular (double *matrix, int matrix_size, double norm);

void QR_decomposition (double *matrix, int matrix_size, double *add_mem, int cur_itter, double norm);
void RQ_production (double *matrix, int matrix_size, double *add_mem, int cur_itter);

double shift_get (double *matrix, int matrix_size, int cur_itter, int f_type);
void shift_make (double *matrix, int matrix_size, int cur_itter, double shift);

