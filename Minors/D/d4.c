#include <stdio.h>

void print_num(int num)
{
	if (num == 0)
		return;

	print_num (num / 10);
	printf ("%d ", num % 10);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	print_num (number);
	printf("\n");
	return 0;
}