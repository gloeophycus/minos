#include <ctype.h>
#include <stdbool.h>

int isupper(int character)
{
	if (character >= 'A' && character <= 'Z')
	{
		return true;
	}
	return false;
}
