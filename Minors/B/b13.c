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

	int even_number = 0;
	int odd_number = 0;
	for (int i = 1; i < 10; i += 2)
		odd_number += digits[i];

	for (int i = 0; i < 10; i += 2)
		even_number += digits[i];

	printf("%d %d\n", even_number, odd_number);
	return 0;
}