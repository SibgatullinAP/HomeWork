#include "addons.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int read_tree(const char* name, Tree & a)
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
