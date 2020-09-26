#include "constants.h"

int read (const char *file_name, double *arr, int size);
void print (double *arr, int size);
void merge_sort (double *arr_1, double *arr_2, int size);
void merge (const double *arr_1, int size_1,
            const double *arr_2, int size_2, double *result);
void check (double *arr, int size);

