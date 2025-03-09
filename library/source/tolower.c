#include <ctype.h>

int tolower(int character)
{
	if (isupper(character))
	{
		return character + 'a' - 'A';
	}
	return character;
}
