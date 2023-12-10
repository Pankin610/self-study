#include "SmallObjAllocator.H"

SmallObjAllocator::SmallObjAllocator(unsigned char chunk_size)
    : _chunk_size(chunk_size)
{}

void* SmallObjAllocator::Allocate(size_t size)
{
    if (_allocators.empty() || _allocators[_last_alloc].block_size() != size)
    {
        _last_alloc = _find_alloc(size);
    }
    return _allocators[_last_alloc].Allocate();
}

void SmallObjAllocator::Deallocate(void* data, size_t size)
{
    if (_allocators.empty() || _allocators[_last_dealloc].block_size() != size)
    {
        _last_dealloc = _find_alloc(size);
    }
    _allocators[_last_dealloc].Deallocate(data);
}

void SmallObjAllocator::_add_allocator(size_t obj_size)
{
    _allocators.emplace_back(obj_size, _chunk_size);

    size_t ind = _allocators.size() - 1;
    while(ind > 0 && _allocators[ind].block_size() < _allocators[ind - 1].block_size())
    {
        std::swap(_allocators[ind], _allocators[ind - 1]);
        ind--;
    }
}

size_t SmallObjAllocator::_find_alloc(size_t obj_size)
{
    if (_allocators.empty() || obj_size < _allocators[0].block_size() || obj_size > _allocators.back().block_size())
    {
        _add_allocator(obj_size);
    }

    size_t l = 0;
    size_t r = _allocators.size() - 1;
    while(l != r)
    {
        size_t mid = (l + r) / 2;
        if (_allocators[mid].block_size() < obj_size)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

