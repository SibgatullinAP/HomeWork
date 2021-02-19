#ifndef TASK_H
#define TASK_H

#include "constants.h"

void get_line (double *array, int n, int l, int r, double *add_mem);
int avg (double *array, double *average, int n, int l, int r, double *add_mem);
int change_line (double *array, int n, int l, int r, double *add_mem);

#endif
