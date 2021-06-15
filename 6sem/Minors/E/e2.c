#include <stdio.h>

int main (void)
{
	int arr[5] = {0};

	for (int i = 0; i < 5; i++)
		scanf ("%d", arr + i);

	int min = arr[0];
	for (int i = 0; i < 5; i++)
		min = arr[i] < min ? arr[i] : min;

	printf("%d\n", min);
	return 0;
}	