#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <new>

#include <pthread.h>

#define        SUCESS 0
#define  CAN_NOT_OPEN 1
#define  CAN_NOT_READ 2
#define ERROR_PTHREAD 3

#define MAX_PRINT ((size_t) 30)

struct Argument
{
  double * a;
  size_t n, p, g;
  pthread_mutex_t * m;
  pthread_barrier_t * b;
  double * s;
  size_t * c;
  bool * is;
};

double
get_time ();
double
get_cpu_time ();

#endif /* COMMON_HPP */
