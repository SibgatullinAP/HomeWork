#include "dataBase.h"

int main(int argc, char *argv[])
{

    if(argc != 2)
    {
        printf("Error: Incorrect input values\n Usage: ./%s input_file.txt\n", argv[0]);
        return -1;
    }

    const char *inFileName = argv[1];
    FILE* inputFile = fopen(inFileName, "r");
    if(inputFile == nullptr)
    {
	printf("Error: Can not open %s\n", inFileName);
	return -1;
    }

    List<Record> dataBase;
    double time = clock();
    int ret = dataBase.read(inputFile);
    time = (clock() - time) / CLOCKS_PER_SEC;
    //printf("Reading time = %0.6lf\n", time);
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
    //dataBase.print();

    time = clock();
    run<Record>(dataBase);
    time = (clock() - time) / CLOCKS_PER_SEC;

    //dataBase.print();
    printf("Operation time = %0.3lf\n", time);

    return 0;
}