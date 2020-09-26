#include "sequences.h"

int main (int argc, char *argv[])
{
	if (argc != 3)
		{
			printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
			        "%s File_name_1 File_name_2\n", argv[0]);
			return -1;
		}

	char *file_name_1 = argv[1];
	char *file_name_2 = argv[2];

	double time = clock ();
	int ret = check (file_name_1, file_name_2);
	time = (clock () - time) / CLOCKS_PER_SEC;

	if (ret < 0)
		{
			switch (ret)
				{
				case CANNOT_OPEN_FILE_1:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_1);
					break;
				case CANNOT_OPEN_FILE_2:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_2);
					break;
				case CANNOT_READ_FILE_1:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_1);
					break;
				case CANNOT_READ_FILE_2:
					printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_2);
					break;
				case INVALID_FILE_1:
					printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
					        " (only part of the file is read)\n", file_name_1);
					break;
				case INVALID_FILE_2:
					printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
					        " (only part of the file is read)\n", file_name_2);
					break;
				case EMPTY_FILE_1:
					printf ("\x1b[31m[ERROR] \x1b[0mEmpty file %s\n", file_name_1);
					break;
				case EMPTY_FILE_2:
					printf ("\x1b[31m[ERROR] \x1b[0mEmpty file %s\n", file_name_2);
					break;
				default:
					printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
				}
			return -3;
		}

	printf ("\x1b[32m[OUTPUT] \x1b[0mAnswer = %d\n", ret);
	printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

	return 0;
}
