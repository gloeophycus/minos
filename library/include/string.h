#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void* memchr(const void *string, int character, size_t n);
void* memrchr(const void *string, int character, size_t n);
int memcmp(const void *string_1, const void *string_2, size_t n);
void* memcpy(void *destination, const void *source, size_t n);
void* memmove(void *destination, const void *source, size_t n);
void* memset(void *string, int character, size_t n);
char* strchr(const char *string, int character);
size_t strlen(const char *string);
size_t strspn(const char *string_1, const char *string_2);

#endif