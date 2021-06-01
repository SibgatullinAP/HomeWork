#ifndef MATRIX_H
#define MATRIX_H


#include "pthread.h"

void thread_init_matrix_by_formula (const int thread_id, const int thread_quantity, pthread_barrier_t *barrier,
                                    const int matrix_size, const int block_size, double *matrix, const int formula_type);
void thread_read_matrix (const int thread_id, int *status, pthread_barrier_t *barrier,
                         const int matrix_size, double *matrix, const char *file_name);
void thread_init_vector (const int thread_id, pthread_barrier_t *barrier, const int matrix_size, double *matrix, double *vector);

int read (double *matrix, int matrix_size, const char *file_name);
void print (const double *matrix, int matrix_size_m, int matrix_size_n, int print_size);

double formula(int formula_type, int matrix_size, int i, int j);
void init_matrix (double *matrix, int matrix_size, int formula_type);
void init_rhs (double *matrix, double *rhs, int matrix_size);

int error_hadler (int error_code, const char *object_name);

#endif // MATRIX_H
