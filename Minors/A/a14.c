#include <stdio.h>

int main(void)
{
	int a = 0;

	if (scanf ("%d", &a) != 1)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	int max = a % 10;
	while (a > 0)
	{
		max = ((a % 10) > max ? a % 10 : max);
		a /= 10;
	}

	printf("%d\n", max);


	return 0;
}