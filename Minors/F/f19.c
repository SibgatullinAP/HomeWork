#include <stdio.h>

int aver_diag (int *matr)
{
	int answer = 0;
	for (int i = 0; i < 5; ++i)
		answer += matr[i * 5 + i];

	return answer / 5;
}

int count_greather_than_aver (int *matr)
{
	int counter = 0;
	int aver = aver_diag (matr);
	for (int i = 0; i < 25; ++i)
		counter += (matr[i] > 0 && matr[i] > aver);

	return counter;
}

int main (void)
{
	int matr[25];
	for (int i = 0; i < 25; ++i)
		scanf ("%d", matr + i);

	int answer = count_greather_than_aver (matr);
	printf("%d\n", answer);

	return 0;
}