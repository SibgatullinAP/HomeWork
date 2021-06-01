#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int sum = 0;

	while (number)
	{
		sum += number % 10;
		number /= 10;
	}

	printf("%d\n", sum);


	return 0;
}