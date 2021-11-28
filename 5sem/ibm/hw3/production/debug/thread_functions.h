#ifndef THREAD_FUNCTIONS_H
#define THREAD_FUNCTIONS_H

#include "pthread.h"

void *thread_func (void *data_bus);

void thread_memmory_catching_by_initialization (const int thread_id, const int thread_quantity, int *status,
                                                pthread_barrier_t *barrier, const int matrix_size, const int block_size,
                                                double *matrix, double *x, double *rhs);

void thread_init (const int thread_id, const int thread_quantity, int *status, pthread_barrier_t *barrier,
                  const int matrix_size, const int block_size, double *matrix, double *rhs,
                  const char *file_name, const int formula_type);

void thread_print (const int thread_id, pthread_barrier_t *barrier, const int matrix_size, int print_size,
                   double *matrix, double *rhs, double *x);

void thread_time (int thread_id, double time_thread, double time_total, pthread_barrier_t *barrier);
void thread_residual (const int thread_id, pthread_barrier_t *barrier,
                      const int matrix_size, double *matrix, double *rhs, double *x, double *residual);

void thread_solve (const int thread_id, const int thread_quantity, int *status, pthread_barrier_t *barrier,
                   const int matrix_size, const int block_size, double *matrix, double *x, double *rhs);

double get_cpu_time ();
double get_full_time ();

#endif // THREAD_FUNCTIONS_H
