#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static char* to_upper_case(char *string)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		string[i] = toupper((unsigned char)string[i]);
	}
	return string;
}

static char* convert_number(char conversion, char *buffer, va_list ap)
{
	switch (conversion)
	{
	case 'd':
	case 'i':
		return itoa(va_arg(ap, int), buffer, 10);
	case 'u':
		return utoa(va_arg(ap, unsigned int), buffer, 10);
	case 'p':
	case 'x':
		return utoa(va_arg(ap, unsigned int), buffer, 16);
	case 'X':
		return to_upper_case(utoa(va_arg(ap, unsigned int), buffer, 16));
	}
	return "";
}

int vsprintf(char *buffer, const char *string, va_list ap)
{
	int index = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == '%')
		{
			char *argument;
			char number_buffer[10 + 1 + 1];
			switch (string[++i])
			{
			case 'c':
				argument = (char[]){ va_arg(ap, int), '\0' };
				break;
			case 's':
				argument = va_arg(ap, char*);
				break;
			case '%':
				argument = "%";
				break;
			default:
				argument = convert_number(string[i], number_buffer, ap);
				break;
			}

			int length = strlen(argument);
			memcpy(buffer + index, argument, length);
			index += length;
			continue;
		}
		buffer[index++] = string[i];
	}
	buffer[index] = '\0';
	return index;
}