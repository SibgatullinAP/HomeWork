#include <stdio.h>

int main(void)
{
	int a = 0;
	int b = 0;
	int c = 0;

	if (scanf ("%d %d %d", &a, &b, &c) != 3)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	printf ("%d\n",(a > b ? (a > c ? a : c) : (b > c ? b : c)));

	return 0;
}