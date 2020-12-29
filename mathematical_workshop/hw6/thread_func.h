#ifndef THREAD_FUNC_H
#define THREAD_FUNC_H

#include "constants.h"
#include "task.h"

void *thread_func (void *);

double f (int i, int j);
void print_matrix (double *matr, int m, int n);
int read_matrix (double *matr, int m, int n, const char *file_name);
void init_matrix (double *matr, int m, int n);

#endif
