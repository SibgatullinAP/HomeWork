#include <stdio.h>

int main (void)
{
	int arr[12] = {0};

	for (int i = 0; i < 12; i++)
		scanf ("%d", arr + i);

	int *first = arr;
	int *second = arr + 4;
	int *third = arr + 8;

	int tmp = 0;
	for (int i = 0; i < 2; i++)
	{
		tmp = first[i];
		first[i] = first[3 - i];
		first[3 - i] = tmp;
	}

	for (int i = 0; i < 2; i++)
	{
		tmp = second[i];
		second[i] = second[3 - i];
		second[3 - i] = tmp;
	}

	for (int i = 0; i < 2; i++)
	{
		tmp = third[i];
		third[i] = third[3 - i];
		third[3 - i] = tmp;
	}

	for (int i = 0; i < 12; i++)
		printf ("%d ", arr[i]);

	printf ("\n");
	return 0;
}	