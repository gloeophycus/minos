#include "memory_allocator.h"

void initialize_memory_allocator(MemoryAllocator *memory_allocator)
{
	memory_allocator->free_block_count = 0;
	memory_allocator->max_free_block_count = 0;
	memory_allocator->free_failure_count = 0;
	memory_allocator->free_failure_size = 0;
}

unsigned int available_memory_size(MemoryAllocator *memory_allocator)
{
	unsigned int total = 0;
	for (int i = 0; i < memory_allocator->free_block_count; i++)
	{
		total += memory_allocator->free_blocks[i].size;
	}
	return total;
}

static int search_blocks(unsigned int address, int free_block_count, FreeBlock *free_blocks)
{
	int i;
	for (i = 0; i < free_block_count; i++)
	{
		if (address < free_blocks[i].address)
		{
			break;
		}
	}
	return i;
}

static void delete_free_block(int index, MemoryAllocator *memory_allocator)
{
	for (int i = index; i < memory_allocator->free_block_count - 1; i++)
	{
		memory_allocator->free_blocks[i] = memory_allocator->free_blocks[i + 1];
	}
	memory_allocator->free_block_count--;
}

static void coalesce_prev_block(unsigned int size, FreeBlock *free_block)
{
	free_block->size += size;
}

static void coalesce_next_block(unsigned int address, unsigned int size, FreeBlock *free_block)
{
	free_block->address = address;
	free_block->size += size;
}

static void coalesce_adjacent_blocks(unsigned int size, int index, MemoryAllocator *memory_allocator)
{
	coalesce_prev_block(size, &memory_allocator->free_blocks[index - 1]);
	memory_allocator->free_blocks[index - 1].size += memory_allocator->free_blocks[index].size;
	delete_free_block(index, memory_allocator);
}

static void insert_free_block(unsigned int address, unsigned int size, int index, MemoryAllocator *memory_allocator)
{
	for (int i = memory_allocator->free_block_count; i > index; i--)
	{
		memory_allocator->free_blocks[i] = memory_allocator->free_blocks[i - 1];
	}

	memory_allocator->free_block_count++;
	memory_allocator->max_free_block_count = memory_allocator->max_free_block_count < memory_allocator->free_block_count ? memory_allocator->free_block_count : memory_allocator->max_free_block_count;
	memory_allocator->free_blocks[index].address = address;
	memory_allocator->free_blocks[index].size = size;
}

static int determine_coalesce_case(unsigned int address, unsigned int size, int index, int free_block_count, FreeBlock *free_blocks)
{
	if (index > 0 && (free_blocks[index - 1].address + free_blocks[index - 1].size == address))
	{
		if (index < free_block_count && (address + size == free_blocks[index].address))
		{
			return COALESCE_ADJECENT;
		}
		return COALESCE_PREV;
	}
	else if (index < free_block_count && (address + size == free_blocks[index].address))
	{
		return COALESCE_NEXT;
	}
	return COALESCE_NONE;
}

unsigned int allocate_memory(unsigned int size, MemoryAllocator *memory_allocator)
{
	unsigned int address = 0;
	for (int i = 0; i < memory_allocator->free_block_count; i++)
	{
		if (size <= memory_allocator->free_blocks[i].size)
		{
			address = memory_allocator->free_blocks[i].address;
			memory_allocator->free_blocks[i].address += size;
			memory_allocator->free_blocks[i].size -= size;
			if (memory_allocator->free_blocks[i].size == 0)
			{
				delete_free_block(i, memory_allocator);
			}
		}
	}
	return address;
}

int free_memory(unsigned int address, unsigned int size, MemoryAllocator *memory_allocator)
{
	int index = search_blocks(address, memory_allocator->free_block_count, memory_allocator->free_blocks);
	switch (determine_coalesce_case(address, size, index, memory_allocator->free_block_count, memory_allocator->free_blocks))
	{
	case COALESCE_ADJECENT:
		coalesce_adjacent_blocks(size, index, memory_allocator);
		return 0;
	case COALESCE_PREV:
		coalesce_prev_block(size, &memory_allocator->free_blocks[index - 1]);
		return 0;
	case COALESCE_NEXT:
		coalesce_next_block(address, size, &memory_allocator->free_blocks[index]);
		return 0;
	case COALESCE_NONE:
		if (memory_allocator->free_block_count < FREE_BLOCKS_CAPACITY)
		{
			insert_free_block(address, size, index, memory_allocator);
			return 0;
		}
		/* fall-through */
	default:
		memory_allocator->free_failure_count++;
		memory_allocator->free_failure_size += size;
		return -1;
	}
}

unsigned int allocate_memory_block(unsigned int size, MemoryAllocator *memory_allocator)
{
	size = (size + MEMORY_BLOCK_MASK) & ~MEMORY_BLOCK_MASK;
	unsigned int address = allocate_memory(size, memory_allocator);
	return address;
}

int free_memory_block(unsigned int address, unsigned int size, MemoryAllocator *memory_allocator)
{
	size = (size + MEMORY_BLOCK_MASK) & ~MEMORY_BLOCK_MASK;
	int status = free_memory(address, size, memory_allocator);
	return status;
}