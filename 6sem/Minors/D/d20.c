#include <stdio.h>

int recurs_power(int n, int p)
{
	if (p == 0)
		return 1;

	return n * recurs_power (n, p - 1);
}

int main (void)
{
	int base, exp;
	scanf ("%d %d", &base, &exp);

	printf("%d\n", recurs_power(base, exp));

	return 0;
}