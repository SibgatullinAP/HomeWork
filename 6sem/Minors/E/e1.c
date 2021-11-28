#include <stdio.h>

int main (void)
{
	int arr[5] = {0};

	for (int i = 0; i < 5; i++)
		scanf ("%d", arr + i);

	float average = 0;
	for (int i = 0; i < 5; i++)
		average += arr[i];

	average /= 5;

	printf("%.3f\n", average);
	return 0;
}	