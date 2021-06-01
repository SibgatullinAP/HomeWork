#include <stdio.h>

int main(void)
{
	int a = 0;

	if (scanf ("%d", &a) != 1)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	int sum = 0;
	while (a > 0)
	{
		sum += a % 10;
		a /= 10;
	}

	printf("%d\n", sum);


	return 0;
}