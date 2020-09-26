#include "sort.h"

int main (int argc, char *argv[])
{
	if (argc != 5)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: %s Array_size_1 "
			        "Array_size_2 File_file_name_1 File_name_2\n", argv[0]);
			return -1;
		}
	int array_size_1 = atoi (argv[1]);
	int array_size_2 = atoi (argv[2]);
	if (array_size_1 == 0 || array_size_1 == 0)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mArray_size_(1,2)"
			        " should be positive integer\n");
			return -1;
		}

	double *arr_1 = (double*) malloc (array_size_1 * sizeof (double));
	if (arr_1 == NULL)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array_1\n");
			return -2;
		}
	double *arr_2 = (double*) malloc (array_size_1 * sizeof (double));
	if (arr_2 == NULL)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array_2\n");
			free(arr_1);
			return -2;
		}
	double *arr_result = (double*) malloc ((array_size_1 + array_size_2)
	                                       * sizeof (double));
	if (arr_result == NULL)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for result_array\n");
			free(arr_1);
			free(arr_2);
			return -2;
		}

	char *file_name_1 = argv[3];
	int ret = read (file_name_1, arr_1, array_size_1);
	if (ret < 0)
		{
			switch (ret)
				{
				case CANNOT_OPEN_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_1);
					break;
				case CANNOT_READ_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_1);
					break;
				case INVALID_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
					        " (only part of the file is read)\n", file_name_1);
					break;
				default:
					printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
				}

			free (arr_1);
			free (arr_2);
			free (arr_result);

			return -3;
		}

	char *file_name_2 = argv[4];
	ret = read (file_name_2, arr_2, array_size_2);
	if (ret < 0)
		{
			switch( ret)
				{
				case CANNOT_OPEN_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_2);
					break;
				case CANNOT_READ_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_2);
					break;
				case INVALID_FILE:
					printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
					        " (only part of the file is read)\n", file_name_2);
					break;
				default:
					printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
				}

			free (arr_1);
			free (arr_2);
			free (arr_result);

			return -3;
		}

	printf ("\x1b[32m[OUTPUT] \x1b[0mArray_1:\n");
	print (arr_1, array_size_1);

	printf ("\x1b[32m[OUTPUT] \x1b[0mArray_2:\n");
	print (arr_2, array_size_2);

	double time = clock ();
	merge (arr_1, array_size_1, arr_2, array_size_2, arr_result);
	time = (clock () - time) / CLOCKS_PER_SEC;

	printf ("\x1b[32m[OUTPUT] \x1b[0mArray_result:\n");
	print (arr_result, array_size_1 + array_size_2);
	printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

	free (arr_1);
	free (arr_2);
	free (arr_result);

	return 0;
}
