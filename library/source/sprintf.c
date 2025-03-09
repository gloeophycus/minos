#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int sprintf(char *buffer, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	vsprintf(buffer, string, ap);
	va_end(ap);

	return strlen(buffer);
}
