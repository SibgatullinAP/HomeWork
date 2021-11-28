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

	int sum = a + b + c;
	int product = a * b * c;
	printf ("%d+%d+%d=%d\n", a, b, c, sum);
	printf ("%d*%d*%d=%d\n", a, b, c, product);

	return 0;
}