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

	int sum = 0;
	for (int i = 0; i < 10; i++)
		sum += i * digits[i];

	if (sum == 10)
		printf("YES\n");
	else
		printf ("NO\n");

	return 0;
}