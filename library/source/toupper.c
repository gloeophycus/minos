#include <ctype.h>

int toupper(int character)
{
	if (islower(character))
	{
		return character - ('a' - 'A');
	}
	return character;
}
