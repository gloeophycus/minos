#include <ctype.h>
#include <stdbool.h>

int isprint(int character)
{
	if (character >= 32 && character <= 126)
	{
		return true;
	}
	return false;
}
