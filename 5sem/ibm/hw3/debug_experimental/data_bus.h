#ifndef DATA_BUS_H
#define DATA_BUS_H

#include "pthread.h"

class data_bus
{
public:
  int thread_quantity = 0;
  int thread_id = 0;
  int matrix_size = 0;
  int block_size = 0;
  int print_size = 0;

  int formula_type = 0;
  const char *file_name = 0;

  double* A = nullptr;
  double* B = nullptr;
  double* X = nullptr;
  double* block_1 = nullptr;
  double* block_2 = nullptr;

  double time_thread = 0;
  double time_total = 0;
  double residual = -1;

  pthread_barrier_t *barrier = nullptr;
  int *status = nullptr;

public:
  data_bus () = default;
  ~data_bus () = default;
};


#endif // DATA_BUS_H
