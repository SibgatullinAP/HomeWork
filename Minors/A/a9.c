#include <stdio.h>

int main(void)
{
	int input_arr[5] = {0};

	if (scanf ("%d %d %d %d %d", input_arr + 0, input_arr + 1, input_arr + 2,
								input_arr + 3, input_arr + 4) != 5)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	int max = input_arr[0];
	for (int i = 0; i < 5; i++)
		max = (input_arr[i] > max ? input_arr[i] : max);

	printf ("%d\n", max);

	return 0;
}