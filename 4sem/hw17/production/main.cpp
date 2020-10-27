#include "dataBase.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
	printf("Error: Incorrect input values\nUsage: %s input_file.txt Hash_Size Port_of_connection\n", argv[0]);
        return -1;
    }

    int PORT = atoi(argv[3]);
    int hashSize = atoi(argv[2]);
    if(hashSize <= 0 || PORT <= 0)
    {
	printf("Error: Incorrect input values\nHash_Size and Port_of_connection must be Integer > 0\n");
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
    ret = server(students, PORT);
    if(ret < 0)
    {
	switch (ret)
	{
	    case ERROR_SERVER_CANNOT_PRINT:
		printf ("|SERVER| Can't print to socket\n");
		break;
	    case ERROR_SERVER_CANNOT_CREATE_SOCKET:
		printf ("|SERVER| Can't create socket\n");
		break;
	    case ERROR_SERVER_CANNOT_BIND_SOCKET:
		printf ("|SERVER| Can't bind socket\n");
		break;
	    case ERROR_SERVER_CANNOT_LISTEN_QUEUE:
		printf ("|SERVER| Can't listen queue\n");
		break;
	    case ERROR_SERVER_CANNOT_SELECT_SOCKET:
		printf ("|SERVER| Can't select socket\n");
		break;
	    case ERROR_SERVER_WASNOT_ACCEPTED:
		printf ("|SERVER| Can't accept\n");
		break;
	    case ERROR_SERVER_CANNOT_READ_INCORRECT_SIZE:
		printf ("|SERVER| Can't read correct size\n");
		break;
	    case ERROR_SERVER_CANNOT_READ:
		printf ("|SERVER| Can't read\n");
		break;
	    case ERROR_SERVER_CLIPPED:
		printf ("|SERVER| Package was clipped\n");
		break;
	    case NOT_ERROR_SERVER_EMPTY_REQUEST:
		printf ("|SERVER| No message\n");
		break;
	    default: printf ("|SERVER| Unknown error %d\n", ret);
	}
    }
    timeExecution = (clock() - timeExecution) / CLOCKS_PER_SEC;

    printf("Operation time : %0.5lf\n", timeExecution);

    return 0;
}
