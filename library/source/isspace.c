#include <ctype.h>
#include <stdbool.h>

int isspace(int character)
{
	if ((character >= 9 && character <= 13) || character == 32)
	{
		return true;
	}
	return false;
}
