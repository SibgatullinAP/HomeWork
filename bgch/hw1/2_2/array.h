#ifndef ARRAY_H
#define ARRAY_H
#include "constants.h"

int read (const char *file_name, double *arr, int size);
void randomize (double *arr, int array_size);
int shift (double *arr, int size, double x);
void print (double *arr, int size);

#endif //ARRAY_H
