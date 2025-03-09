#include <string.h>

void* memchr(const void *string, int character, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (((unsigned char*)string)[i] == (unsigned char)character)
		{
			return (void*)(string + i);
		}
	}
	return NULL;
}
