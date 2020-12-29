#ifndef TASK_H
#define TASK_H

#include "constants.h"


void get_column_buff (double *matr, int  m, int n, int l, int r, double *add_mem);
double find_min (double *matr, int m, int n, int j_);

int change_col (double *matr, int m, int n, double *add_mem, double *min, int l, int r);
int change_columns (double *matr, int m, int n, double *add_mem, double *min, int l, int r);

int check (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min);
int check_tailed (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min);
int check_tailed_left (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min);
int check_tailed_right (double *left, double *center, double *right, int m, int n, double *buff_1, double *buff_2, double min);

#endif
