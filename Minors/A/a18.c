#include <stdio.h>

int main (void)
{
	
	int a = 0;
	int b = 0;
	if (scanf ("%d %d", &a, &b) != 2)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	if (a > b)
		printf("Above\n");
	else if (a < b)
		printf("Less\n");
	else
		printf("Equal\n");

	return 0;
}