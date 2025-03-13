#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>

enum EFLAGS
{
	ALIGNMENT_CHECK = 1 << 18,
};

enum CR0
{
	NOW_WRITE_THROUGH = 1 << 29,
	CACHE_DISABLE = 1 << 30,
};

unsigned int test_memory(unsigned int start, unsigned int end);

#endif