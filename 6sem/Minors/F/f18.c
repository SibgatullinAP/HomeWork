#include <stdio.h>

int maxsum (int *matr)
{
	int sum = 0;
	int max = 0;

	int answer = 0;
	for (int i = 0; i < 10; ++i)
	{
		max = matr[i * 10];
		for (int j = 0; j < 10; ++j)
			max = matr[i * 10 + j] > max ? matr[i * 10 + j] : max;

		answer += max;
	}

	return answer;
}

int main (void)
{
	int matr[100];
	for (int i = 0; i < 100; ++i)
		scanf ("%d", matr + i);

	int answer = maxsum (matr);
	printf("%d\n", answer);

	return 0;
}