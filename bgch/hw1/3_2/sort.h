#include "constants.h"

int read (const char *file_name, double *arr, int size);
void merge (const double *arr1, int size_1,
            const double *arr2, int size_2, double *result);
void print (double *arr, int size);
