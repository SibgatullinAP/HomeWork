#include <stdio.h>

int sum_ (int number)
{
	if (number == 0)
		return 0;

	return number + sum_(number - 1);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	printf ("%d\n", sum_ (number));
	return 0;
}