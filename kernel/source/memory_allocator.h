#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#define MEMORY_ALLOCATOR_ADDRESS 0x003C0000
#define FREE_BLOCKS_CAPACITY 4096
#define MEMORY_BLOCK_SIZE 0x1000
#define MEMORY_BLOCK_MASK (MEMORY_BLOCK_SIZE - 1)

enum COALESCE_CASE
{
	COALESCE_PREV,
	COALESCE_NEXT,
	COALESCE_ADJECENT,
	COALESCE_NONE,
};

typedef struct
{
	unsigned int address;
	unsigned int size;
} FreeBlock;

typedef struct
{
	int free_block_count;
	int max_free_block_count;
	int free_failure_count;
	int free_failure_size;
	FreeBlock free_blocks[FREE_BLOCKS_CAPACITY];
} MemoryAllocator;

void initialize_memory_allocator(MemoryAllocator *memory_allocator);
unsigned int available_memory_size(MemoryAllocator *memory_allocator);
unsigned int allocate_memory(unsigned int size, MemoryAllocator *memory_allocator);
int free_memory(unsigned int address, unsigned int size, MemoryAllocator *memory_allocator);
unsigned int allocate_memory_block(unsigned int size, MemoryAllocator *memory_allocator);
int free_memory_block(unsigned int address, unsigned int size, MemoryAllocator *memory_allocator);

#endif