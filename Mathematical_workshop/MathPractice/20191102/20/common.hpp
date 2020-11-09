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
  // имя файла для текущего потока
  const char * file;
  // массивы длины p в первом из которых находится первый элемент
  // соответствующих файлов, во втором последние
  double * shm1, * shm2;
  // количества элементов в соответствующих файлах.
  // это нужно, что бы знать, какой элемент действительно предыдущий/следующий
  int * file_size;
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
