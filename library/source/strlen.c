#include <string.h>

size_t strlen(const char *string)
{
	size_t i;
	for (i = 0; string[i] != '\0'; i++) {}
	return i;
}
