#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int digits[10] = {0};

	while (number)
	{
		digits[number % 10] += 1;
		number /= 10;
	}

	

	printf("%d %d\n", even_number, odd_number);
	return 0;
}