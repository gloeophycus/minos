#include "assembly_functions.h"
#include "memory.h"

static bool check_cache(void)
{
	unsigned int eflags = read_eflags();
	eflags |= ALIGNMENT_CHECK;
	write_eflags(eflags);
	eflags = read_eflags();

	if ((eflags & ALIGNMENT_CHECK) != 0)
	{
		eflags &= ~ALIGNMENT_CHECK;
		write_eflags(eflags);
		return true;
	}
	return false;
}

static void disable_cache(void)
{
	unsigned int cr0 = read_cr0();
	cr0 |= (NOT_WRITE_THROUGH | CACHE_DISABLE);
	write_cr0(cr0);
}

static void enable_cache(void)
{
	unsigned int cr0 = read_cr0();
	cr0 &= ~(NOT_WRITE_THROUGH | CACHE_DISABLE);
	write_cr0(cr0);
}

static unsigned int test_memory_range(unsigned int start, unsigned int end)
{
	unsigned int i;
	const unsigned int pattern_1 = 0xAA55AA55;
	const unsigned int pattern_2 = ~pattern_1;
	for (i = start; i <= end; i += 0x1000)
	{
		volatile unsigned int *p = (unsigned int*)(i + 0x0FFC);
		unsigned int temp = *p;
		*p = pattern_1;
		*p ^= 0xFFFFFFFF;
		if (*p != pattern_2)
		{
			*p = temp;
			break;
		}

		*p ^= 0xFFFFFFFF;
		if (*p != pattern_1)
		{
			*p = temp;
			break;
		}

		*p = temp;
	}
	return i;
}

unsigned int test_memory(unsigned int start, unsigned int end)
{
	bool is_cache_supported = check_cache();
	if (is_cache_supported)
	{
		disable_cache();
	}

	unsigned int memory = test_memory_range(start, end);

	if (is_cache_supported)
	{
		enable_cache();
	}

	return memory;
}