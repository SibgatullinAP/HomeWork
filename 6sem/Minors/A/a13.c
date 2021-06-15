#include <stdio.h>

int main(void)
{
	int a = 0;

	if (scanf ("%d", &a) != 1)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	int product = 1;
	while (a > 0)
	{
		product *= a % 10;
		a /= 10;
	}

	printf("%d\n", product);


	return 0;
}