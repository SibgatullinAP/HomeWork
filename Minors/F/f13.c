#include <stdio.h>

int count (int a, int b, int *arr)
{
	int counter = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (arr[i] >= a && arr[i] <= b)
			counter ++;
	}

	return counter;
}

int main (void)
{
	int a, b;
	scanf("%d %d", &a, &b);

	int arr[10];
	for (int i = 0; i < 10; ++i)
		scanf ("%d", arr + i);

	int answer = count (a, b, arr);
	printf("%d\n", answer);

	return 0;
}