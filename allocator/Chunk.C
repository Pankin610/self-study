#include "Chunk.H"
#include <cassert>

void Chunk::Init(size_t block_size, unsigned char blocks)
{
    data = new unsigned char[block_size * blocks];
    first_available_block = 0;
    num_available_blocks = blocks;

    unsigned char* block_ptr = data;
    for (unsigned char block = 0; block + 1 < blocks; block++)
    {
        *block_ptr = block + 1;
        block_ptr += block_size;
    }
}

void* Chunk::Allocate(size_t block_size)
{
    assert(num_available_blocks > 0);
    void* allocated_block = data + first_available_block * block_size;
    first_available_block = *static_cast<unsigned char*>(allocated_block);
    num_available_blocks--;
    return allocated_block;
}

void Chunk::Deallocate(void* p, size_t block_size)
{
    assert(p);
    unsigned char* block = static_cast<unsigned char*>(p);
    assert(block >= data && (block - data) % block_size == 0);
    assert((block - data) / block_size < 256);
    *block = first_available_block;
    first_available_block = (block - data) / block_size;
    num_available_blocks++;
}

void Chunk::Release()
{
    delete[] data;
}