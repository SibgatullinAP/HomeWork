#include <stdio.h>

int main (void)
{
	int arr[10] = {0};

	for (int i = 0; i < 10; i++)
		scanf ("%d", arr + i);

	int tmp = arr[9];
	for (int i = 9; i > 0; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[0] = tmp;

	for (int i = 0; i < 10; i++)
		printf ("%d ", arr[i]);

	printf ("\n");
	return 0;
}	