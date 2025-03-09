#include <ctype.h>
#include <stdlib.h>

int atoi(const char *string)
{
	int i;
	for (i = 0; isspace(string[i]); i++) {}

	int sign = string[i] == '-' ? -1 : 1;
	if (string[i] == '-' || string[i] == '+')
	{
		i++;
	}

	int number = 0;
	for (; isdigit(string[i]); i++)
	{
		number *= 10;
		number += string[i] - '0';
	}
	return sign * number;
}
