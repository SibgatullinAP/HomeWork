#include "func.h"

int func(const char *inFileName, const char *outFileName)
{
	char espace[ESCAPE_LEN] = {'\n', '\t',' '};
	int space[SPACE_LEN] = {0};
	for (int i = 0; i < ESCAPE_LEN; ++i)
	{
		space[int(espace[i])] = 1;
	}

	FILE *inFile, *outFile;
	char buff1[BUFF_LEN], buff2[BUFF_LEN];
	bool isDebugPrint = false;

	if ((inFile = fopen(inFileName, "r")) == nullptr)
	{
		return ERROR_CANNOT_OPEN_INPUT_FILE;
	}

	printf("Please, choose type of printing.\n"
			"1 - Debug(table) print\n"
			"2 - Normal print\n"
			"Your choise: ");
	int printType = 0;
	scanf("%d",&printType);
	if (printType == 1)
	{
		isDebugPrint = true;
	}
	else if (printType == 2)
	{
		isDebugPrint = false;
	}
	else
	{
		printf("Error: Incorrect input values!\n");
		fclose(inFile);
		return ERROR_INCORRECT_ENTERED_TYPE;
	}

	int commandCounter = 0;
	int correctCommandCounter = 0;
	if (outFileName == nullptr)
	{
		while(fgets(buff1, BUFF_LEN, inFile))
		{
			Command current;
			if (current.parse(buff1, space, buff2))
			{
				correctCommandCounter ++;
			}
			current.print(commandCounter, isDebugPrint);
			commandCounter++;
		}
		if (!feof(inFile))
		{
			fclose(inFile);
			return ERROR_CANNOT_READ_INPUT_FILE;
		}
	}
	else
	{
		if ((outFile = fopen(outFileName, "w")) == nullptr)
		{
			fclose(inFile);
			return ERROR_CANNOT_OPEN_OUTPUT_FILE;
		}

		while(fgets(buff1, BUFF_LEN, inFile))
		{
			Command current;
			if (current.parse(buff1, space, buff2))
			{
				correctCommandCounter ++;
			}
			current.print(commandCounter, isDebugPrint, outFile);
			commandCounter++;
			if(ferror(outFile))
			{
				fclose(inFile);
				fclose(outFile);
				return ERROR_CANNOT_WRITE_TO_OUTPUT_FILE;
			}
		}
		if (ferror(inFile))
		{
			fclose(inFile);
			fclose(outFile);
			return ERROR_CANNOT_READ_INPUT_FILE;
		}
		fclose(outFile);
	}
	fclose(inFile);
	return correctCommandCounter;
}
