#include "sort.h"

int read (const char *file_name, double *arr, int size)
{
	FILE *file = fopen (file_name, "r");
	if (file == NULL)
		return CANNOT_OPEN_FILE;

	for (int i = 0; i < size; i ++)
		{
			if (fscanf (file, "%lf", (arr + i)) != 1)
				{
					fclose (file);
					return CANNOT_READ_FILE;
				}
		}

	if (!feof (file))
		{
			fclose (file);
			return INVALID_FILE;
		}

	fclose (file);
	return 0;
}

void print (double *arr, int size)
{
	int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
	for (int i = 0; i < print_limit; i ++)
		printf ("\t[%d] = %.4f\n", i, arr[i]);
}

void binary_sort (double *arr, int size)
{
	for(int i = 1; i < size; i++)
		{
			int j = binary_search (arr, i, arr[i]);
			for (int k = i; k > j; k--)
				swap (arr, k, k - 1);
		}
}

int binary_search (const double *arr, int size, double x)
{
	int left = 0;
	int right = size - 1;
	int center;

	if (arr[left] > x)
		return 0;
	if (arr[right] < x)
		return size;

	while (left <= right)
		{
			center = (left + right) / 2;
			if (arr[center] <= x)
				left = center + 1;
			else
				right = center - 1;
		}

	return left;
}

void swap (double *a, int i, int j)
{
	double buff = a[j];
	a[j] = a[i];
	a[i] = buff;
}

void check (double *arr, int size)
{
	for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i+1])
				{
					printf ("\x1b[31m[UNSORTED]\x1b[0m\n");
					return;
				}
		}
	printf ("\x1b[32m[SORTED]\x1b[0m\n");
}
