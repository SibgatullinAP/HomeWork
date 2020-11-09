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

struct Argument
{
  // массив имен файлов; его длина = число потоков
  const char ** files;
  // массивы длины p с помощью которого потоки осуществят обмен данными
  double * shared_min, * shared_max;
  // массив статусов работы каждого из потоков
  int * status;
  // массив итогового ответа. имеет смысл если все статусы SUCESS
  int * result;
  // общее число потоков и номер текущего потока
  int p, g;
  // для осуществления точек синхронизации
  pthread_barrier_t * barrier;
};

#endif /* COMMON_HPP */
