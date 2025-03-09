#include <ctype.h>
#include <stdbool.h>

int isalnum(int character)
{
	if (isalpha(character) || isdigit(character))
	{
		return true;
	}
	return false;
}
