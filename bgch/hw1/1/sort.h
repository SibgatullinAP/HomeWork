#include "constants.h"

int read (const char *file_name, double *arr, int size);
void print (double *arr, int size);
void check (double *arr, int size);
void swap (double *a, int i, int j);

int binary_search (const double *arr, int size, double x);

void merge (const double *arr1, int size_1,
            const double *arr2, int size_2, double *result);

int array_redbuilding (double *arr, int size, double x);

void binary_sort (double *arr, int size);

void merge_sort (double *arr_1, double *arr_2, int size);

void quick_sort (double *arr, int size);

void heap_sort (double *arr, int size);
void create_heap (double *arr, int size);
void rebuild_heap (double *arr, int depth);
