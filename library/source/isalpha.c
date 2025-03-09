#include <ctype.h>
#include <stdbool.h>

int isalpha(int character)
{
	if (isupper(character) || islower(character))
	{
		return true;
	}
	return false;
}
