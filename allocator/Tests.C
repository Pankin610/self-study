#include "SmallObjAllocator.H"
#include <random>

class TestSmallObjAllocator : public SmallObjAllocator
{
public:
    using SmallObjAllocator::SmallObjAllocator;
    const std::vector<FixedAllocator>& get_allocators() const { return _allocators; }
};

int main()
{
    FixedAllocator fixed_allocator(64, 100);
    void* data = fixed_allocator.Allocate();
    fixed_allocator.Deallocate(data);


    TestSmallObjAllocator allocator(100);
    data = allocator.Allocate(64);
    allocator.Deallocate(data, 64);

    assert(allocator.get_allocators().size() == 1);

    // Just a segfault check
    std::vector<void*> alloc_objs;
    std::mt19937 rng(610);
    for (size_t iter = 0; iter < 10000; iter++)
    {
        if (rng() % 2 || alloc_objs.empty())
        {
            alloc_objs.push_back(allocator.Allocate(64));
        }
        else
        {
            size_t ind = rng() % alloc_objs.size();
            allocator.Deallocate(alloc_objs[ind], 64);
            std::swap(alloc_objs[ind], alloc_objs.back());
            alloc_objs.pop_back();
        }
    }

    while(!alloc_objs.empty())
    {
        allocator.Deallocate(alloc_objs.back(), 64);
        alloc_objs.pop_back();
    }

    return 0;
}