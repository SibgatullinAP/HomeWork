#include <stdio.h>

int main (void)
{
	int arr[10] = {0};

	for (int i = 0; i < 10; i++)
		scanf ("%d", arr + i);

	int *first_half = arr;
	int *second_half = arr + 5;

	int tmp = 0;
	for (int i = 0; i < 2; i++)
	{
		tmp = first_half[i];
		first_half[i] = first_half[4 - i];
		first_half[4 - i] = tmp;
	}

		for (int i = 0; i < 2; i++)
	{
		tmp = second_half[i];
		second_half[i] = second_half[4 - i];
		second_half[4 - i] = tmp;
	}

	for (int i = 0; i < 10; i++)
		printf ("%d ", arr[i]);

	printf ("\n");
	return 0;
}	