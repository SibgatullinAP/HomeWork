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
	int i;
	for (i = 0; i < print_limit; i ++)
		printf("\t[%d] = %.4f\n", i, arr[i]);
}

void merge_sort (double *arr_1, double *arr_2, int size)
{
	double *pr_temp = NULL;
	double *arr_1_temp = arr_1;
	int tail_len = 0, i = 0;
	for (int seg_len = 1; seg_len < size; seg_len <<= 1)
		{
			for (i = 0; (i + 2 * seg_len) <= size; i += (seg_len * 2))
				merge (arr_1 + i, seg_len, arr_1 + seg_len + i, seg_len, arr_2 + i);

			merge (arr_1 + i, size - i - tail_len,
			       arr_1 + size - tail_len, tail_len, arr_2+i);
			tail_len = size - i;

			pr_temp = arr_1;
			arr_1 = arr_2;
			arr_2 = pr_temp;
		}
	if (arr_1_temp != arr_1)
		{
			for (int k = 0; k < size; k++)
				arr_2[k] = arr_1[k];
		}
}

void merge (const double *arr_1, int size_1,
            const double *arr_2, int size_2, double *result)
{
	int i = 0, j = 0, k = 0;
	while ((i < size_1) && (j < size_2))
		{
			if (arr_1[i] < arr_2[j])
				{
					result[k] = arr_1[i];
					i++;
					k++;
				}
			else
				{
					result[k] = arr_2[j];
					j++;
					k++;
				}
		}

	while (i < size_1)
		{
			result[k] = arr_1[i];
			i++;
			k++;
		}

	while (j < size_2)
		{
			result[k] = arr_2[j];
			j++;
			k++;
		}
}

void check (double *arr, int size)
{
	for (int i = 0; i < size - 1; i++)
		{
			if (arr[i] > arr[i+1])
				{
					printf("\x1b[31m[UNSORTED]\x1b[0m\n");
					return;
				}
		}
	printf("\x1b[32m[SORTED]\x1b[0m\n");
}
