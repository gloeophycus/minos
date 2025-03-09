#include <string.h>

size_t strspn(const char *string_1, const char *string_2)
{
	size_t i;
	for (i = 0; string_1[i] != '\0'; i++)
	{
		if (strchr(string_2, string_1[i]) == NULL)
		{
			return i;
		}
	}
	return i;
}