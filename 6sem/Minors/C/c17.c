#include <stdio.h>

int pow_ (int base, int exp)
{
	int answer = 1;
	for (int i = 0; i < exp; i++)
		answer *= base;

	return answer;
}


int is_happy_number (int number)
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

	int product = 1;
	for (int i = 0; i < 10; i++)
		product *= pow_ (i, digits[i]);


	return product == sum;
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	if (is_happy_number (number))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}