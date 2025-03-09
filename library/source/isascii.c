#include <ctype.h>
#include <stdbool.h>

int isascii(int character)
{
	if (character >= 0 && character <= 127)
	{
		return true;
	}
	return false;
}
