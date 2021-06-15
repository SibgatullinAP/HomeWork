#include <stdio.h>

void analyze_digits (char *number)
{	
	int alphabet[256] = {0};
	for (int i = 0; number[i] && number[i] != '.'; ++i)
		alphabet[number[i]] += 1;

	for (int i = '0'; i <= '9'; ++i)
	{
		if (alphabet[i])
			printf("%c %d\n", i, alphabet[i]);
	}
}


int main (void)
{
	char number[2000];
	scanf ("%[^\n]", number);

	analyze_digits (number);
	return 0;
}