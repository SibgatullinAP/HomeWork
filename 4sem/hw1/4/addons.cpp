#include "addons.h"
#include "student.h"

#include <stdio.h>

int read_array(const char* name, Student* a, int arrayLen)
{
        int ret = 0;
	FILE * fp;
        if(!(fp = fopen(name, "r"))) return ERROR_CANNOT_OPEN_INPUT_FILE;

	for(int i = 0; i < arrayLen; i ++)
        {

            if((ret = a[i].read(fp)) < 0)
            {
                fclose(fp);
                return ret;
            }
		
	}
	fclose(fp);
	return 0;
}


void print_array(Student* a, int arrayLen)
{
	int m = ((arrayLen > MAX_PRINT) ? MAX_PRINT : arrayLen);

	for(int i = 0; i < m; i ++)
	{
		a[i].print();
	}

	printf("\n");
}
