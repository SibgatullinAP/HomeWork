#include <stdio.h>

int is_add (int number)
{
	int digits[10] = {0};

	while (number)
	{
		digits[number % 10] += 1;
		number /= 10;
	}

	int sum = 0;
	for (int i = 0; i < 10; i++)
		sum += i * digits[i];

	return (sum % 2 == 0);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	if (is_add (number))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}