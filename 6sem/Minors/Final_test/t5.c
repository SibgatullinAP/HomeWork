#include <stdio.h>

void print_rare_symbol(char str[])
{
	char alphabet[256] = {0};
	for (int i = 0; str[i]; ++i)
		alphabet[str[i]] += 1;

	int min_char_amount = 0;
	int min_char_ind = 0;

	for (int i = 'a'; i <= 'z'; ++i)
	{
		if (alphabet[i] > 0)
		{
			min_char_ind = i;
			min_char_amount = alphabet[i];

			break;
		}
	}

	for (int i = 'a'; i <= 'z'; ++i)
	{
		if (alphabet[i] < min_char_amount && alphabet[i] > 0)
		{
			min_char_ind = i;
			min_char_amount = alphabet[i];
		}
	}

	for (int i = 'a'; i <= 'z'; ++i)
	{
		if (alphabet[i] == min_char_amount)
		{
			min_char_ind = i;
			min_char_amount = alphabet[i];

			break;
		}
	}

	printf("%c %d\n", min_char_ind, min_char_amount);
}

int main (void)
{
	char str[2000];
	scanf("%[^\n]", str);

	print_rare_symbol(str);
	return 0;
}