#ifndef THREAD_FUNC_H
#define THREAD_FUNC_H

#include "common.h"
#include "solver.h"

void *thread_func (void *ptr);
void reduce_sum (int p, int * a, int n);

#endif // THREAD_FUNC_H
