#include <stdio.h>

int main(void)
{
	int a = 0;
	int b = 0;

	if (scanf ("%d %d", &a, &b) != 2)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	printf ("%d %d\n", (a > b ? b : a), (a > b ? a : b));

	return 0;
}