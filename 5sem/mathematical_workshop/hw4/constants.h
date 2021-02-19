#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <algorithm>
#include <new>

#include <pthread.h>

#define MAX_PRINT 20
#define CAN_NOT_OPEN -1
#define CAN_NOT_READ -2

struct Interface
{
  pthread_barrier_t *barrier;

  double *array;
  double add_mem[6];
  int n;

  int thread_quantity;
  int curr_thread;

  int answer;
  double time;
};

double get_time ();
double get_cpu_time ();

#endif
