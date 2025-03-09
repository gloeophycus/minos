#include <stdbool.h>
#include <stdlib.h>

static int convert(unsigned int number, char *buffer, int radix)
{
	int i = 0;
	do {
		int remainder = number % radix;
		buffer[i++] = remainder < 10 ? remainder + '0' : remainder - 10 + 'a';
		number /= radix;
	} while (number > 0);
	return i;
}

static void swap(int length, char *buffer)
{
	for (int i = 0; i < length / 2; i++)
	{
		char temp = buffer[i];
		buffer[i] = buffer[length - i - 1];
		buffer[length - i - 1] = temp;
	}
}

char* itoa(int number, char *buffer, int radix)
{
	bool is_negative = false;
	if (number < 0)
	{
		is_negative = true;
		number *= -1;
	}

	int length = convert((unsigned int)number, buffer, radix);
	if (is_negative)
	{
		buffer[length++] = '-';
	}
	buffer[length] = '\0';
	swap(length, buffer);
	return buffer;
}

char* utoa(unsigned int number, char *buffer, int radix)
{
	int length = convert(number, buffer, radix);
	buffer[length] = '\0';
	swap(length, buffer);
	return buffer;
}