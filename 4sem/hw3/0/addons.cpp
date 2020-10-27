#include "addons.h"

#include <stdio.h>

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


