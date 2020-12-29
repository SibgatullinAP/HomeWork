#ifndef THREAD_FUNC_H
#define THREAD_FUNC_H

#include "constants.h"
#include "task.h"

void *thread_func (void *);

double f (int i);
void print_array (double *array, int n);
int read_array (double *array, int n, const char *file_name);
void init_array (double *array, int n);

#endif
