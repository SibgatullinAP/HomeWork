#include "addons.h"
#include <stdio.h>

int read(const char* name, List <Student, Queue, Tree> &a, int size_list, int size_tree, int size_queue)
{
    FILE * fp;
    if(!(fp = fopen(name, "r")))
    {
    	return ERROR_CANNOT_OPEN_INPUT_FILE;	
    } 
    int ret = a.read(fp, size_list, size_tree, size_queue);
    fclose(fp);
    return ret;
}

int logo1(bool selector, const char* inputfile)
{
	if (selector == true)
	{

		FILE* fp = fopen(inputfile, "r");
		if(fp == nullptr)
		{
			return ERROR_CANNOT_OPEN_INPUT_FILE;
		}
		char buff[LOGOWIDTH];
		while(fgets(buff, LOGOWIDTH, fp))
		{
			printf("\x1b[33;1m%s\x1b[0m",buff);
		}
		printf("\n");
		if(!feof(fp))
		{
			fclose(fp);
			return ERROR_CANNOT_READ_INPUT_FILE;
		}
		fclose(fp);
		return 0;
	}
	return 0;
}

int logo2(bool selector, const char* inputfile)
{
	if (selector == true)
	{

		FILE* fp = fopen(inputfile, "r");
		if(fp == nullptr)
		{
			return ERROR_CANNOT_OPEN_INPUT_FILE;
		}
		char buff[LOGOWIDTH];
		while(fgets(buff, LOGOWIDTH, fp))
		{
			printf("\x1b[31;5;1m%s\x1b[0m",buff);
		}
		printf("\n");
		if(!feof(fp))
		{
			fclose(fp);
			return ERROR_CANNOT_READ_INPUT_FILE;
		}
		fclose(fp);
		return 0;
	}
	return 0;
}

void posix_death_signal(int signum)
{
    signal(signum, SIG_DFL);
    logo2(true);
    printf("Segmentation fault\n");
    exit(3);
}

void fall()
{
      int* p = nullptr;
      *p = 13;
}
