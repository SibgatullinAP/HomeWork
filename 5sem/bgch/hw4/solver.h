#include "constants.h"

double solve_1 (double *matrix_A, double *X0, double *X, int matrix_size, int m_th);
void solve_2 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double tau);
void solve_3 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R);
void solve_4 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R);
void solve_5 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R);
void solve_6 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R);
void solve_7 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R, double tau);
void solve_8 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R, double tau);
void solve_9 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R, double tau);
void solve_10 (double *matrix_A, double *X0, double *X, double *B, int matrix_size, int m_th, double *R, double tau);

void matrix_to_vector_product (double *matrix, double *vector, double *answer, int matrix_size);
int gauss_elimination_LD (double *matrix, double *vector, double *answer, int matrix_size);
int gauss_elimination_RD (double *matrix, double *vector, double *answer, int matrix_size);
int tau_3 (double *A, double *B, int matrix_size, double *answer);
int tau_4 (double *A, double *B, int matrix_size, double *answer);
int tau_5 (double *A, double *B, double *D, int matrix_size, double *answer);
int tau_6 (double *A, double *B, double *D, int matrix_size, double *answer);

int read (double *A, int matrix_size_m, int matrix_size_n, char *file_name);
void print (double *A, int matrix_size_m, int matrix_size_n, int print_size);

double formula(int matrix_size, int i, int j);
void init_A (double *A, int matrix_size);
void init_B (double *A, double *B, int matrix_size);
void init_X0 (double *X_0, int matrix_size);

double error_rate_norm_1 (double *X, int matrix_size);
double discrepancy_rate_norm_1 (double *A, double *X, double *B, int matrix_size);
