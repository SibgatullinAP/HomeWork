#include "addons.h"
#include "student.h"

#include <stdio.h>

int read_array(const char* name, Student* a, int arrayLen)
{
	FILE * fp;
	if(!(fp = fopen(name, "r"))) return -3;

	for(int i = 0; i < arrayLen; i ++)
	{
		if(a[i].read(fp) < 0)
		{
			fclose(fp);
			return -2;  
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