#ifndef IO_H
#define IO_H

#include "common.h"

void printf_to_main_process (const char *format, ...);

void print_arr (double *arr, int size);
int read_arr (double *arr, int size, const char *file_name);
void init_formula (double *arr, int size);

int error_hadler (int error_code, const char *object_name);

#endif //IO_H
