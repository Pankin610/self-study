#pragma once

#include "Chunk.H"
#include <vector>

class FixedAllocator
{
public:
    FixedAllocator(size_t block_size, unsigned char num_blocks = 255);

    void* Allocate();

    void Deallocate(void* data);

    size_t block_size() { return _block_size; }

    ~FixedAllocator();

protected:
    bool _belongs_to_chunk(void* data, const Chunk& chunk);

    void _add_chunk();

    size_t _find_alloc_chunk();
    size_t _find_dealloc_chunk(void* data);

    size_t _block_size;
    unsigned char _num_blocks;
    std::vector<Chunk> _chunks;

    size_t _last_alloc_chunk = 0;
    size_t _last_dealloc_chunk = 0;
};
