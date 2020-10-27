#include "addons.h"

#include <stdio.h>

bool compareMore(ListNode* a, ListNode* b)
{
	return (bool) (*a > *b);
}

bool compareLess(ListNode* a, ListNode* b)
{
	return (bool) (*a < *b);
}

int read_list(const char* name, List & a)
{
	FILE * fp;
    if(!(fp = fopen(name, "r")))
    {
    	return ERROR_CANNOT_OPEN_INPUT_FILE;	
    } 
    int ret = a.read(fp);
	fclose(fp);
    return ret;
}

bool checkSort(List* a, bool (*comp)(ListNode*, ListNode*))
{
    ListNode *tmp = a -> get_head();
    ListNode *curr = tmp;
    if(tmp == nullptr)
    {
    	return true;
    }
    while(tmp -> get_next())
    {
    	curr = tmp -> get_next();
    	if(comp(tmp,curr))
    	{
    		tmp = nullptr;
    		curr = nullptr;
    		printf("List is unsorted :(\n");
    		return false;
    	}
    	tmp = curr;
    }

    tmp = nullptr;
    curr = nullptr;
    printf("List is sorted :)!\n");
    return true;
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
