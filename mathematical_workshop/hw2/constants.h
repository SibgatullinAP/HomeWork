#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define CANNOT_OPEN_FILE -1
#define CANNOT_READ_FILE -2

class Data_Bus
{
public:
  const char **file_names = nullptr;
  double *avg = nullptr;
  int *status = nullptr;
  int *result = nullptr;
  int thread_quantity = 0;
  int curr_thread = 0;
  pthread_barrier_t *barrier = nullptr;
public:
  Data_Bus () = default;
  ~Data_Bus () = default;
};

#endif
