#pragma once

#include <stddef.h>

struct Chunk
{
    void Init(size_t block_size, unsigned char blocks);

    void* Allocate(size_t block_size);

    void Deallocate(void* p, size_t block_size);

    void Release();

    unsigned char* data;
    unsigned char first_available_block;
    unsigned char num_available_blocks;
};