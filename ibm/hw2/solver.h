#include "constants.h"

int read (double *A, int matrix_size, char *file_name);
double formula(int formula_type, int matrix_size, int i, int j);
void init_A (double *A, int matrix_size, int formula_type);
void init_B (double *A, double *B, int matrix_size);
void print (double *A, int matrix_size_m, int matrix_size_n, int print_size);
double error_rate_norm_1 (double *X, int matrix_size);
double discrepancy_rate_norm_1 (double *A, double *X, double *B, int matrix_size);
int solve (int matrix_size, double *A, double *B, double *X,
           int block_size, double *block_1, double *block_2, double *block_3);
void get_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_);
void set_block (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_);
int diagonalize_block (double *A, int matrix_size, double *T);
void traverse_block (double *A, double *B, int matrix_size, double *T);
void zeroing_block (double *A, double *B, int matrix_size, double *T);
int solve_optimized (int matrix_size, double *A, double *B, double *X,
           int block_size, double *block_1, double *block_2, double *block_3);
