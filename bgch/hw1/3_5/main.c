#include "sort.h"

int main (int argc, char *argv[])
{
	if (argc != 3)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mPlease, use:"
			        " %s Array_size File_name\n", argv[0]);
			return -1;
		}
	int array_size = atoi (argv[1]);
	if (array_size == 0)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mArray_size should be positive integer\n");
			return -1;
		}

	double *arr_1 = (double*) malloc (array_size * sizeof (double));
	if (arr_1 == NULL)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array_1\n");
			return -2;
		}
	double *arr_2 = (double* )malloc (array_size * sizeof (double));
	if (arr_2 == NULL)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array_2\n");
			free (arr_1);
			return -2;
		}

	char *name_file = argv[2];
	int ret = read (name_file, arr_1, array_size);
	if (ret < 0)
		{
			switch (ret)
				{
				case CANNOT_OPEN_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", name_file);
					break;
				case CANNOT_READ_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", name_file);
					break;
				case INVALID_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
					        " (only part of the file is read)\n", name_file);
					break;
				default:
					printf ("\x1b[31m[УERROR] \x1b[0mUnknown error\n");
				}

			free (arr_1);
			free (arr_2);

			return -3;
		}

	printf ("\x1b[32m[OUTPUT] \x1b[0mArray:\n");
	print (arr_1, array_size);

	double time = clock ();
	merge_sort (arr_1, arr_2, array_size);
	time = (clock () - time) / CLOCKS_PER_SEC;

	printf ("\x1b[32m[OUTPUT] \x1b[0mArray after sorting:\n");
	print (arr_1, array_size);

	check (arr_1, array_size);
	printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

	free (arr_1);
	free (arr_2);

	return 0;
}
