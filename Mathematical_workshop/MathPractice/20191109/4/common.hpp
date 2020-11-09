#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <algorithm>
#include <new>

#define        SUCESS 0
#define ERROR_PTHREAD 1

#define ALGO_STEP 10000

struct Argument
{
  size_t * a;
  int n, p, g;
  int * r;
  double cpu_time;
  pthread_barrier_t * b;
};

double
get_time ();
double
get_cpu_time ();

#endif /* COMMON_HPP */
