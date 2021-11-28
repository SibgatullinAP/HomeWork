#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <new>

#include <pthread.h>

#define        SUCESS 0
#define      BAD_ARGS 1
#define     BAD_ALLOC 2
#define  CAN_NOT_OPEN 3
#define  CAN_NOT_READ 4
#define ERROR_PTHREAD 5

#define MAX_PRINT ((size_t) 25)

struct Argument
{
  double * a;
  size_t n, m, p, g;
  pthread_mutex_t * m_;
  pthread_barrier_t * b_;
  double * workspace;
};

double
get_time ();
double
get_cpu_time ();

#endif /* COMMON_HPP */
