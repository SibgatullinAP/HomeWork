#include "func.h"

int main(int argc, char *argv[])
{
    if((argc != 2) && (argc != 3))
    {
	printf("Error: Incorrect input values!\n"
	       "Please, use %s input_file_name.txt (output_file_name.txt)\n", argv[0]);
	return -1;
    }

    const char *inFileName = argv[1];
    const char *outFileName = nullptr;

    if(argc == 3)
    {
		outFileName = argv[2];
    }

    double time = clock();
    int ret = func(inFileName, outFileName);
    time = clock() - time;

    if(ret < 0)
    {
	switch (ret)
	{
	    case ERROR_CANNOT_OPEN_INPUT_FILE:
		printf("Error: Can not open %s\n", inFileName);
		break;
	    case ERROR_CANNOT_OPEN_OUTPUT_FILE:
		printf("Error: Can not open %s\n", outFileName);
		break;
	    case ERROR_CANNOT_READ_INPUT_FILE:
		printf("Error: Can not read from %s\n", inFileName);
		break;
	    case ERROR_CANNOT_WRITE_TO_OUTPUT_FILE:
		printf("Error: Can not write to %s\n", outFileName);
		break;
	    default:
		printf("Error: Unknown error, error_value = %d", ret);
		break;
	}
	return -2;
    }
    printf("\nDebug value = %d\nElapsed time = %lf.6\n", ret, time/CLOCKS_PER_SEC);

    return 0;
}
