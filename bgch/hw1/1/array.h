#ifndef ARRAY_H
#define ARRAY_H
#include "constants.h"

int read (const char *file_name, double *arr, int size);
void randomize (double *arr, int array_size);
void print (double *arr, int size);

int occurrences (double *arr, int array_size, char *file_name);

int shift (double *arr, int size, double x);

int greatest_common_devisor(int x, int y);
void shift_to_k (double *arr, int size, int shift);

#endif //ARRAY_H
