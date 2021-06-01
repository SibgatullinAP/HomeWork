#include <stdio.h>

int main (void)
{
	int arr[10] = {0};

	for (int i = 0; i < 10; i++)
		scanf ("%d", arr + i);

	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += arr[i] > 0 ? arr[i] : 0;
	}

	printf("%d\n", sum);
	return 0;
}	