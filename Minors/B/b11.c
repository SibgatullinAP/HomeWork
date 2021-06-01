#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int digits_counter = 0;
	int tmp = number;
	while (tmp)
	{
		digits_counter ++;
		tmp /= 10;
	}

	int answer = 0;

	for (int i = digits_counter - 1; i >= 0; i--)
	{
		int pow_10 = 1;
		for (int j = 0; j < i; j++)
			pow_10 *= 10;

		answer += (number % 10) * pow_10;
		number /= 10;
	}

	printf("%d\n", answer);

	return 0;
}