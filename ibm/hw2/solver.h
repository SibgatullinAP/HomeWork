#ifndef SOLVER_H
#define SOLVER_H

class arguments;

int solve_mpi (arguments args, double *matrix, double *x, double *rhs, double *block_column, double *block_1, double *block_2);
void gaussian_elimination_mpi (arguments args, double *matrix, double *rhs,
                               double *x, double *block_1, double *block_2, double *block_column);
void invert_block (double *block, int matrix_size, double *block_attached);

int diagonalize_block (double *A, int matrix_size, int block_size, double *T, double eps);
void zeroing_block (double *A, double *B, int matrix_size, int m_block_size, int n_block_size, double *T, double eps);

void traverse_vector (double *A, int matrix_size, int block_reminder, double *T);
void traverse_vector_zeroing (double *A, double *B, int matrix_size, int m_block_size, double *T);

void traverse_block_zeroing (double *A, double *B, int matrix_size, int m_block_size, int n_block_size,
                             double *T, int shift);
void traverse_block (double *A, int m_matrix_size, int n_matrix_size, double *T);

int solve_optimized (int matrix_size, double *A, double *B, double *X,
                     int block_size, double *block_1, double *block_2);
#endif // SOLVER_H
