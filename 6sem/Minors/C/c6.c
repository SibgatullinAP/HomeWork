#include <stdio.h>

unsigned long int geom_sum_to_n (int n)
{
	unsigned long int pow_2 = 1;
	for (int i = 0; i < n - 1; i++)
		pow_2 *= 2;

	return (pow_2);
}

int main (void)
{
	int n = 0;
	scanf ("%d", &n);

	printf("%lu\n", geom_sum_to_n (n));
	return 0;
}