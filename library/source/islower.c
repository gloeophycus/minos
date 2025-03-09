#include <ctype.h>
#include <stdbool.h>

int islower(int character)
{
	if (character >= 'a' && character <= 'z')
	{
		return true;
	}
	return false;
}
