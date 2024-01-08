#include "StackAllocator.hpp"

#include <cstdlib>

struct MEMORY_API memStackAllocatorBlock
{
	memStackAllocatorBlock(uint32_t size)
		: data_start(nullptr)
		, data_end(nullptr)
		, next(nullptr)
	{
		// Allocate block memory
		data_start = (uint8_t*)::malloc(size);
		data_end = data_start + size;
	}

	~memStackAllocatorBlock()
	{
		if (data_start != nullptr)
			::free(data_start);
	}

	// Range of allocated data for this block
	uint8_t* data_start = nullptr;
	uint8_t* data_end = nullptr;

	// Intrusive link within block link list belonging to an allocator
	memStackAllocatorBlock* next = nullptr;
};


memStackAllocator::memStackAllocator(uint32_t block_size)
	: block_size(block_size)
{
}


memStackAllocator::~memStackAllocator()
{
	// Release all memory blocks
	while (first_block != nullptr)
	{
		memStackAllocatorBlock* next_block = first_block->next;
		delete first_block;
		first_block = next_block;
	}
}


void* memStackAllocator::malloc(size_t size)
{
	return ::malloc(*this, static_cast<uint32_t>(size));
}


void memStackAllocator::free(void*)
{
	// Can't do out-of-order frees from a stack allocator
	//assert(false);
}


void* memStackAllocator::realloc(void*, size_t)
{
	// Unsupported
	//assert(false);
	return nullptr;
}


MEMORY_API void* malloc(memStackAllocator& allocator, uint32_t size)
{
	// No more free space?
	if (allocator.data_alloc + size > allocator.data_end)
	{
		// Has a block already been allocated for reuse?
		if (allocator.next_alloc_block != nullptr)
		{
			// Set it up ready to pull allocations from
			allocator.data_alloc = allocator.next_alloc_block->data_start;
			allocator.data_end = allocator.next_alloc_block->data_end;

			// Move the next alloc block along the linked list
			allocator.next_alloc_block = allocator.next_alloc_block->next;
		}

		else
		{
			// Allocate blocks on-demand
			memStackAllocatorBlock* new_block = new memStackAllocatorBlock(allocator.block_size);
			allocator.data_alloc = new_block->data_start;
			allocator.data_end = new_block->data_end;

			// Add to linked list
			if (allocator.first_block == nullptr)
			{
				allocator.first_block = new_block;
				allocator.last_block = new_block;
			}
			else
			{
				allocator.last_block->next = new_block;
				allocator.last_block = new_block;
			}
		}
	}

	// Pull from the current block
	void* data = allocator.data_alloc;
	allocator.data_alloc += size;
	allocator.allocated_bytes += size;
	return data;
}


MEMORY_API void reset(memStackAllocator& allocator)
{
	// Point allocator at the first block, discarding the old allocation position and allowing
	// new allocations to reuse existing blocks
	if (allocator.first_block != nullptr)
	{
		allocator.data_alloc = allocator.first_block->data_start;
		allocator.data_end = allocator.first_block->data_end;
		allocator.next_alloc_block = allocator.first_block->next;
	}
}