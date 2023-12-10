#include "FixedAllocator.H"
#include <stdexcept>
#include <iostream>

FixedAllocator::FixedAllocator(size_t block_size, unsigned char num_blocks)
    : _block_size(block_size)
    , _num_blocks(num_blocks)
{
    _add_chunk();
}

void FixedAllocator::_add_chunk()
{
    _chunks.emplace_back();
    _chunks.back().Init(_block_size, _num_blocks);
}

void* FixedAllocator::Allocate()
{
    assert(!_chunks.empty());
    if (_chunks[_last_alloc_chunk].num_available_blocks == 0)
    {
        _last_alloc_chunk = _find_alloc_chunk();
    }
    assert(_chunks[_last_alloc_chunk].num_available_blocks > 0);
    return _chunks[_last_alloc_chunk].Allocate(_block_size);
}

size_t FixedAllocator::_find_alloc_chunk()
{
    for (size_t i = 0; i < _chunks.size(); i++)
    {
        if (_chunks[i].num_available_blocks > 0)
        {
            return i;
        }
    }
    _add_chunk();
    return _chunks.size() - 1;
}

bool FixedAllocator::_belongs_to_chunk(void* data, const Chunk& chunk)
{
    return data >= chunk.data && data < chunk.data + _num_blocks * _block_size;
}

void FixedAllocator::Deallocate(void* data)
{
    assert(data);
    if (!_belongs_to_chunk(data, _chunks[_last_dealloc_chunk]))
    {
        _last_dealloc_chunk = _find_dealloc_chunk(data);
    }
    _chunks[_last_dealloc_chunk].Deallocate(data, _block_size);

    if (_chunks.size() > 1 && _chunks[_last_dealloc_chunk].num_available_blocks == _num_blocks)
    {
        std::swap(_chunks.back(), _chunks[_last_dealloc_chunk]);
        _chunks.back().Release();
        _chunks.pop_back();
        _last_dealloc_chunk = 0;
        _last_alloc_chunk = 0;
    }
}

size_t FixedAllocator::_find_dealloc_chunk(void* data)
{
    for (size_t i = 0; i < _chunks.size(); i++)
    {
        if (_belongs_to_chunk(data, _chunks[i]))
        {
            return i;
        }
    }

    throw std::runtime_error("Unknown data dealloc.");
}

FixedAllocator::~FixedAllocator()
{
    for (size_t i = 0; i < _chunks.size(); i++)
    {
        _chunks[i].Release();
    }
}