#include <stdio.h>

int main (void)
{
	int arr[12] = {0};

	for (int i = 0; i < 12; i++)
		scanf ("%d", arr + i);

	float average = 0;
	for (int i = 0; i < 12; i++)
		average += arr[i];

	average /= 12;

	printf("%.2f\n", average);
	return 0;
}	