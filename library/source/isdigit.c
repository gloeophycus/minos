#include <ctype.h>
#include <stdbool.h>

int isdigit(int character)
{
	if (character >= '0' && character <= '9')
	{
		return true;
	}
	return false;
}
