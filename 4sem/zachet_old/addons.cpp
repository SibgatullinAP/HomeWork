#include "addons.h"
#include <stdio.h>

int read(const char* name, List & a)
{
    FILE * fp;
    if(!(fp = fopen(name, "r")))
    {
    	return ERROR_CANNOT_OPEN_INPUT_FILE;	
    } 
    fseek(fp,0,0);
    int ret = a.read(fp);
    fclose(fp);
    return ret;
}
