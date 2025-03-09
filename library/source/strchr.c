#include <string.h>

char* strchr(const char *string, int character)
{
	size_t i;
	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == character)
		{
			return (char*)&string[i];
		}
	}
	return character == '\0' ? (char*)&string[i] : NULL;
}