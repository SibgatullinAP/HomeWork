#include <stdio.h>

int main (void)
{
	int counter = 0;
	int curr_number = 0;

	while (scanf ("%d", &curr_number) == 1 && curr_number)
		counter++;

	printf("%d\n", counter);
	return 0;
}