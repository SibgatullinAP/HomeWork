#include <stdio.h>

int main (void)
{
	int month = 0;
	if (scanf ("%d", &month) != 1 || month < 1 || month > 12)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	if (month == 12 || month < 3)
		printf("winter\n");
	else if (month >= 3 && month <= 5)
		printf("spring\n");
	else if (month > 5 && month < 9)
		printf("summer\n");
	else if (month >= 9 && month <= 11)
		printf("autumn\n");

	return 0;
}