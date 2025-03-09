#include <string.h>

void* memcpy(void *destination, const void *source, size_t n)
{
	if (destination == source)
	{
		return destination;
	}

	for (size_t i = 0; i < n; i++)
	{
		((unsigned char*)destination)[i] = ((unsigned char*)source)[i];
	}
	return destination;
}
