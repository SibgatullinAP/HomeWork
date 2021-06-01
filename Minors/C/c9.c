#include <stdio.h>

unsigned long int factorial (int n)
{
	if (n == 1)
		return 1;

	return n * factorial(n - 1);
}

int main (void)
{
	int n = 0;
	scanf ("%d", &n);

	printf("%lu\n", factorial(n));
	return 0;
}