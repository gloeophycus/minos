#include <string.h>

int memcmp(const void *string_1, const void *string_2, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (((unsigned char*)string_1)[i] != ((unsigned char*)string_2)[i])
		{
			return ((unsigned char*)string_1)[i] - ((unsigned char*)string_2)[i];
		}
	}
	return 0;
}
