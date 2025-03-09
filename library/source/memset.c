#include <string.h>

void* memset(void *string, int character, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		((unsigned char*)string)[i] = (unsigned char)character;
	}
	return string;
}
