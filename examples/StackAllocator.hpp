#pragma once


// https://gist.github.com/dwilliamson/c1842a98b1e7cfd8c9724756c1ccec77#file-stackallocator-h

#define MEMORY_API

#include <cstdint>

// -----------------------------------------------------------------------------------------------------------------
// Stack allocator that can only be allocated from and reset.
// Memory grows linearly in chunks of the block size to reduce virtual memory fragmentation.
// Also removes need to copy existing data to newly allocated blocks.
// Any allocations that span a block edge require allocation of a new block where they get placed at
// the front.
// -----------------------------------------------------------------------------------------------------------------

struct memStackAllocatorBlock;

class memAllocator
{
public:
	virtual void* malloc(size_t size) = 0;
	virtual void free(void* ptr) = 0;
	virtual void* realloc(void* ptr, size_t size) = 0;
};


struct MEMORY_API memStackAllocator : public memAllocator
{
	memStackAllocator(uint32_t block_size);
	~memStackAllocator();

	// Optional allocator interface
	// Use global functions to guarantee faster calls
	void* malloc(size_t size) override;
	void free(void* ptr) override;
	void* realloc(void* ptr, size_t size) override;

	// Size data stored to allow further blocks to be allocated
	const uint32_t block_size;

	// Currently allocated position and limit to its allocation
	uint8_t* data_alloc = nullptr;
	uint8_t* data_end = nullptr;

	// Keeps track of the total number bytes allocated
	uint32_t allocated_bytes = 0;

	// Linked list of on-demand allocated blocks
	memStackAllocatorBlock* first_block = nullptr;
	memStackAllocatorBlock* last_block = nullptr;

	// Next free block to allocate from (if any)
	memStackAllocatorBlock* next_alloc_block = nullptr;
};


MEMORY_API void* malloc(memStackAllocator& allocator, uint32_t size);
MEMORY_API void reset(memStackAllocator& allocator);


// New/delete operators for stack allocator
inline void* operator new (size_t size, memStackAllocator& allocator)
{
	return malloc(allocator, static_cast<uint32_t>(size));
}
inline void operator delete(void* ptr, memStackAllocator& allocator)
{
	// Not supported
	//assert(false);
}
