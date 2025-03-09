#include <string.h>

void* memmove(void *destination, const void *source, size_t n)
{
	if (destination > source)
	{
		for (size_t i = 0; i < n; i++)
		{
			((unsigned char*)destination)[n - i - 1] = ((unsigned char*)source)[n - i - 1];
		}
	}
	else
	{
		memcpy(destination, source, n);
	}
	return destination;
}
