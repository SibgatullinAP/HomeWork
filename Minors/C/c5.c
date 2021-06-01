#include <stdio.h>

int sum_to_n (int n)
{
	return (n * (n + 1)) / 2;
}

int main (void)
{
	int n = 0;
	scanf ("%d", &n);

	printf("%d\n", sum_to_n (n));
	return 0;
}