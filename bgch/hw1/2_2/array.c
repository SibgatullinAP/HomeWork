#include "array.h"

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

void randomize (double *arr, int array_size)
{
	srand (0);
	for (int i = 0; i < array_size; i++)
		{
			int denominator = rand() % 10000;
			denominator = (denominator != 0 ? denominator : 19 );
			arr[i] = (double) rand () / (double) denominator;
		}
}

void print (double *arr, int size)
{
	int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
	for (int i = 0; i < print_limit; i++)
		printf ("\t[%d] = %.4f\n", i, arr[i]);
}


int shift (double *arr, int size, double x)
{

	int shift = 0;
	for (int i = 0; i < size; i++)
		{
			if (arr[i] < x)
				shift++;
			else
				arr[i - shift] = arr[i];
		}
	return size - shift;
}


