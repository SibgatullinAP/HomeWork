#include <stdio.h>

int trace (int *matr)
{
	int answer = 0;
	for (int i = 0; i < 5; ++i)
		answer += matr[i * 5 + i];

	return answer;
}

int main (void)
{
	int matr[25];
	for (int i = 0; i < 25; ++i)
		scanf ("%d", matr + i);

	int answer = trace (matr);
	printf("%d\n", answer);

	return 0;
}