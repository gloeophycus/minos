#include <string.h>

void* memrchr(const void *string, int character, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (((unsigned char*)string)[n - i - 1] == (unsigned char)character)
		{
			return (void*)(string + n - i - 1);
		}
	}
	return NULL;
}
