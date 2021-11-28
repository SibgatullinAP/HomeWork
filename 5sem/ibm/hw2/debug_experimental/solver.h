#include "constants.h"

int read (double *A, int matrix_size, char *file_name);
void print (double *A, int matrix_size_m, int matrix_size_n, int print_size);

double formula(int formula_type, int matrix_size, int i, int j);
void init_A (double *A, int matrix_size, int formula_type);
void init_B (double *A, double *B, int matrix_size);

double error_rate_norm_1 (double *X, int matrix_size);
double discrepancy_rate_norm_1 (double *A, double *X, double *B, int matrix_size);
double discrepancy_rate_norm_1_blocking (double *A, double *X, double *B, int matrix_size,
                                         double *block_1, double *block_2, int block_size);
double norm_1_blocking (double A, int matrix_size, double *block_1, double *block_2, int block_size);

int solve (int matrix_size, double *A, double *B, double *X,
           int block_size, double *block_1, double *block_2, double *block_3);

void get_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev);
void set_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev);

void get_block_vector (double *B, double *Block,int block_size,
                       int i_, int dev, int rem_of_dev);
void set_block_vector (double *B, double *Block,int block_size,
                       int i_, int dev, int rem_of_dev);

int diagonalize_block (double *A, int matrix_size, int block_size, double *T, double eps);
void zeroing_block (double *A, double *B, int matrix_size, int m_block_size, int n_block_size, double *T, double eps);

void traverse_vector (double *A, int matrix_size, int block_reminder, double *T);
void traverse_vector_zeroing (double *A, double *B, int matrix_size, int m_block_size, double *T);

void traverse_block_zeroing (double *A, double *B, int matrix_size, int m_block_size, int n_block_size,
                             double *T, int shift);
void traverse_block (double *A, int m_matrix_size, int n_matrix_size, double *T);

int solve_optimized (int matrix_size, double *A, double *B, double *X,
                     int block_size, double *block_1, double *block_2);
