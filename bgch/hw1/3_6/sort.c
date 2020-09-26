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

void quick_sort (double *arr, int size)
{
	int position;
	double base_element;

	if (size < 2)
		return ;

	while (size > 2)
		{
			base_element = arr[size / 2];
			position = array_redbuilding (arr, size, base_element);
			if (position < size - position)
				{
					quick_sort (arr, position);
					arr += position;
					size -= position;
				}
			else
				{
					quick_sort (arr + position, size - position);
					size = position;
				}
		}
	if (size == 2 && arr[size - 2] > arr[size - 1])
		swap (arr, size - 2, size - 1);
	return ;
}


int array_redbuilding (double *arr, int size, double x)
{
	int left = 0;
	int right = size - 1;
	while (left <= right)
		{
			while (arr[left] < x)
				left++;
			while (arr[right] > x)
				right--;
			if (left <= right)
				{
					swap (arr, left, right);
					right--;
					left++;
				}
		}

	return left;
}

void swap (double *a, int i, int j)
{
	double buff = a[j];
	a[j] = a[i];
	a[i] = buff;
}
