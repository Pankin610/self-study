#pragma once
#include <vector>

#include "FixedAllocator.H"

class SmallObjAllocator
{
public:
    SmallObjAllocator(unsigned char chunk_size);

    void* Allocate(size_t size);
    void Deallocate(void* data, size_t size);

protected:
    void _add_allocator(size_t obj_size);

    size_t _find_alloc(size_t obj_size);

    std::vector<FixedAllocator> _allocators;
    unsigned char _chunk_size;
    size_t _last_alloc = 0;
    size_t _last_dealloc = 0;
};