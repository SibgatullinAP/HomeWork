#include "dataBase.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
	printf("Error: Incorrect input values\nUsage: %s input_file.txt Hash_Size\n", argv[0]);
        return -1;
    }

    int hashSize = atoi(argv[2]);
    if(hashSize <= 0)
    {
	printf("Error: Incorrect input values\nHash_Size must be > 0\n");
	return -1;
    }

    const char *inFileName = argv[1];
    FILE* inputFile = fopen(inFileName, "r");
    if(inputFile == nullptr)
    {
	printf("Error: Can't open %s\n", inFileName);
	return -1;
    }

    DataBase students (hashSize);

    double timeRead = clock();
    int ret = students.read(inputFile);
    timeRead = (clock() - timeRead) / CLOCKS_PER_SEC;

    if(ret < 0)
    {
	switch (ret)
	{
	    case ERROR_CANNOT_READ_INPUT_FILE:
	        printf("Error: Can not read from %s\n", inFileName);
	        break;
	    default:
	        printf("Error: Unknown error, error_value = %d", ret);
	        break;
	}
	fclose(inputFile);
	return -2;
    }
    fclose(inputFile);
    printf("Reading time : %0.5lf\n", timeRead);

    double timeExecution = clock();
    students.run();
    timeExecution = (clock() - timeExecution) / CLOCKS_PER_SEC;

    printf("Operation time : %0.5lf\n", timeExecution);

    return 0;
}
