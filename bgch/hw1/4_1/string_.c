#include "string_.h"

int strcspn_ (const char *string_1, const char *string_2)
{
	int buff[256] = {0};
	for (int i = 0; i < string_2[i]; i++)
		buff[(unsigned int) string_2[i]] = 1;

	int i;
	for (i = 0; i < string_1[i]; i ++)
		{
			if (buff[(unsigned int) string_1[i]] == 1)
				return i;
		}

	return i;
}
