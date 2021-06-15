#ifndef MATRIX_H
#define MATRIX_H

class arguments;

#include "pthread.h"

void printf_to_main_process (const char *format, ...);

int read_matrix_mpi (const arguments &args, double *matrix, double *add_mem);
void print_matrix_mpi (const arguments &args, double *matrix, double *add_mem);

void init_matrix_mpi (arguments args, double *matrix);
void init_vector_mpi (arguments args, double *matrix, double *rhs, double *add_mem);
void init_vector_by_formula (arguments args, double *rhs);

double residual_mpi (arguments args, double *matrix, double *rhs, double *x, double *block_column, double *block_1);
double norm_mpi (arguments args, double *matrix, double *block_column);

void multiply_matr_to_vec (int m_matrix_size, int n_matrix_size, int shift, double *matr, double *vec, double *ans);
void subtract_vec_from_vec (double *a, double *b, double *ans, int matrix_size);

void get_block (double *A, int m_matrix_size, int n_matrix_size, double *Block,
                int block_size, int i_, int j_, int dev_m, int rem_m, int dev_n, int rem_n);
void set_block (double *A, int m_matrix_size, int n_matrix_size, double *Block,
                int block_size, int i_, int j_, int dev_m, int rem_m, int dev_n, int rem_n);

void get_block_from_buff (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev);
void set_block_to_buff (double *A, int matrix_size, double *Block, int block_size,
                int i_, int j_, int dev, int rem_of_dev);

void get_block_vector (double *B, double *Block,int block_size, int i_, int dev, int rem_of_dev);
void set_block_vector (double *B, double *Block,int block_size, int i_, int dev, int rem_of_dev);











void thread_init_matrix_by_formula (const int thread_id, const int thread_quantity, pthread_barrier_t *barrier,
                                    const int matrix_size, const int block_size, double *matrix, const int formula_type);
void thread_read_matrix (const int thread_id, int *status, pthread_barrier_t *barrier,
                         const int matrix_size, double *matrix, const char *file_name);
void thread_init_vector (const int thread_id, pthread_barrier_t *barrier, const int matrix_size, double *matrix, double *vector);

void print (const double *matrix, int matrix_size_m, int matrix_size_n, int print_size_m, int print_size_n);
double formula(int formula_type, int matrix_size, int i, int j);
int error_hadler (int error_code, const char *object_name);

#endif // MATRIX_H
